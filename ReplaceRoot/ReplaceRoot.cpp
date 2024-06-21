#include <string>
#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <cstdint>
#include <numeric>
#include <cstring>

auto res = [] () {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);
    return 0;
} ();

struct CharNode
{
    CharNode* nextTable[26];
    bool terminate { false };
    uint32_t hasNext { 0 };
    
    CharNode* get_next(char nc)
    {
        uint32_t mask = 1 << (nc - 'a');
        if(hasNext & mask)
            return nextTable[nc - 'a'];
        else
            return nullptr;
    }

    CharNode* set_next(char nc, CharNode* node)
    {
        uint32_t mask = 1 << (nc - 'a');
        hasNext |= mask;
        return nextTable[nc - 'a'] = node;
    }
};

class Solution {
public:
    std::string replaceWords(std::vector<std::string> const& dictionary, std::string const& sentence) 
    {
        CharNode root;
        int size = std::accumulate(dictionary.begin(), dictionary.end(), 0, [] (int s, std::string const& ref) { return s + ref.size(); });
        CharNode pool[size];
        size_t currAlloc = 0;
        
        for(auto& str : dictionary)
        {
            CharNode* current = &root;
            for(auto ch : str)
            {
                if(current->terminate)
                    break;
                else if(auto next = current->get_next(ch); next)
                    current = next;
                else
                    current = current->set_next(ch, &pool[currAlloc++]);
            }
            current->terminate = true;
        }

        std::string ret;
        ret.reserve(sentence.size() + 1);

        enum {
            CONSUME,
            TRIM,
            IGNORE
        } state { CONSUME };
        CharNode* current = &root;
        for(auto ch : sentence)
        {
            if(ch == ' ')
            {
                state = CONSUME;
                current = &root;
                ret.append(1, ch);
                continue;
            } 

            switch (state) 
            {
            case CONSUME:
                if(current->terminate)
                {
                    state = TRIM;
                    continue;
                }
                else if(auto next = current->get_next(ch); next)
                    current = next;
                else
                    state = IGNORE;
                break;
            case TRIM:
                continue;
            case IGNORE:
                break;
            }
            ret.append(1, ch);
        }

        return ret;
    }
};

typedef struct TreeNode {
    struct TreeNode* nextTable[26];
    uint32_t hasNext;
    bool terminate;
} TreeNode;

inline TreeNode* get_next(TreeNode* thiz, char nc)
{
    uint32_t mask = 1 << (nc - 'a');
    if(thiz->hasNext & mask)
        return thiz->nextTable[nc - 'a'];
    else
        return nullptr;
}

inline TreeNode* set_next(TreeNode* thiz, char nc, TreeNode* node)
{
    uint32_t mask = 1 << (nc - 'a');
    thiz->hasNext |= mask;
    node->terminate = false;
    node->hasNext = 0;
    return thiz->nextTable[nc - 'a'] = node;
}

char* replaceWords(char** dictionary, int dictionarySize, char* sentence) 
{
    TreeNode root;
    root.hasNext = 0;
    root.terminate = false;

    size_t size = 0;
    for(int i = 0; i < dictionarySize; i++)
    {
        char* current = dictionary[i];
        while(*current++ && size++);
    }

    TreeNode pool[size];
    size_t currAlloc = 0;

    for(int i = 0; i < dictionarySize; i++)
    {
        TreeNode* currentNode = &root;
        TreeNode* next = NULL;
        for(char* ch = dictionary[i]; *ch; ch++)
        {
            if(currentNode->terminate)
                break;
            else if((next = get_next(currentNode, *ch)))
                currentNode = next;
            else
                currentNode = set_next(currentNode, *ch, &pool[currAlloc++]);
        }
        currentNode->terminate = true;
    }

    size_t len = strlen(sentence);
    char* ret = (char*)malloc(len + 1);

    enum {
        CONSUME,
        TRIM,
        IGNORE
    } state = CONSUME;

    TreeNode* current = &root;
    TreeNode* next = NULL;
    size_t pos = 0;
    for(char* ch = sentence; *ch; ch++)
    {
        if(*ch == ' ')
        {
            state = CONSUME;
            current = &root;
            ret[pos++] = ' ';
            continue;
        }

        switch (state) 
        {
        case CONSUME:
            if(current->terminate)
            {
                state = TRIM;
                continue;
            }
            else if ((next = get_next(current, *ch))) 
                current = next;
            else
                state = IGNORE;
            break;
        case TRIM:
            continue;
        case IGNORE:
            break;
        }
        ret[pos++] = *ch;
    }
    ret[pos] = 0;
    return ret;
}

int main()
{
    std::cout << Solution().replaceWords({"cat","ba", "bat","rat"}, "the cattle was rattled by the battery") << std::endl;
}
#include <algorithm>
#include <cstddef>
#include <functional>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
class Solution {
public:

    bool palindrome(std::string const& s, size_t start, size_t end)
    {
        size_t len = end - start + 1;
        if(len % 2 != 0)
        {
            int i = start, j = end;
            while(i != j)
            {
                if(s[i] != s[j])
                    return false;
                i++; j--;
            }
        }
        else
        {
            int mid = (len / 2) + start;
            for(int i = start, j = end; i < mid; i++, j--)
            {
                if(s[i] != s[j])
                    return false;
            }
        }
        return true;
    }

    struct GraphNode
    {
        size_t idx;
        std::vector<std::reference_wrapper<GraphNode>> next;
    };

    void pathExplore(std::string const& s, GraphNode const& current, size_t terminatingIndex, std::deque<std::string>& substringQueue, std::vector<std::vector<std::string>>& res)
    {
        if(current.idx == terminatingIndex)
            res.emplace_back(substringQueue.begin(), substringQueue.end());
        else 
        {
            for(auto nextPartition : current.next)
            {
                GraphNode const& next = nextPartition.get();
                substringQueue.emplace_back(s.begin() + current.idx, s.begin() + next.idx);
                pathExplore(s, next, terminatingIndex, substringQueue, res);
                substringQueue.pop_back();
            }
        }
    }

    
    std::vector<std::vector<std::string>> partition(std::string const& s) 
    {
        std::vector<std::vector<std::string>> ret;

        std::vector<std::pair<size_t, size_t>> palindromes;

        for(int i = 0; i < s.size(); i++) 
            for(int j = i; j < s.size(); j++)
                if(palindrome(s, i, j))
                    palindromes.emplace_back(i, j);
            
        std::vector<GraphNode> substringGraphs;
        for(int i = 0; i < s.size() + 1; i++)
            substringGraphs.emplace_back(i);

        for(auto& substringPair: palindromes)
        {
            auto [first, last] = substringPair;
            substringGraphs[first].next.emplace_back(substringGraphs[last + 1]);
        }

        std::deque<std::string> substringQueue;
        pathExplore(s, substringGraphs[0], s.size(), substringQueue, ret);

        return ret;
    }
};

int main()
{
    {
        auto res { Solution().partition("aab") };
        std::ranges::for_each(res, [] (auto& x) {
            std::cout << "[";
            std::ranges::for_each(x, [first= true] (auto& y) mutable {
                if(!first)
                    std::cout << ", ";
                else first = false;
                std::cout << "\"" << y << "\"";
            });
            std::cout << "]" << std::endl;
        });
    }
}
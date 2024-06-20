#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <ranges>

class Solution {
public:
    std::vector<std::string> wordBreak(std::string const& s, std::vector<std::string> const& wordDict) 
    {
        // Find all possible substring
        std::vector<std::vector<std::pair<size_t, std::reference_wrapper<std::string const>>>> substringEdges;
        substringEdges.resize(s.size());

        std::ranges::for_each(wordDict, [&] (std::string const& word) {
            for(int i = 0; i < s.size(); i++)
                if(std::ranges::equal(word, s | std::views::drop(i) | std::views::take(word.size()), std::equal_to<char>{}))
                    substringEdges[i].emplace_back(i + word.size(), word);
        });

        // dfs again
        std::vector<std::string> ret;
        std::vector<std::reference_wrapper<std::string const>> sentence;
        auto dfs = [&] (auto& dfs, int idx) -> void {
            // Base case: end of string
            if(idx == s.size())
            {
                ret.emplace_back(std::accumulate(sentence.begin(), sentence.end(), std::string {}, [first = true] (std::string&& str, std::reference_wrapper<std::string const> ref) mutable {
                    if(first)
                        first = false;
                    else
                        str.append(" ");
                    str.append(ref);
                    return str;
                }));
            }
            else 
                for(auto [nextIdx, str] : substringEdges[idx]) 
                {
                    sentence.emplace_back(str);
                    dfs(dfs, nextIdx);
                    sentence.pop_back();
                }
        };

        dfs(dfs, 0);
        
        return ret;
    }
};

int main()
{
    {
        std::vector<std::string> wordDict {"cat","cats","and","sand","dog"};
        auto input = "catsanddog";

        std::cout << "Result: {" << std::endl;
        std::ranges::for_each(Solution().wordBreak(input, wordDict), [] (auto x) {
            std::cout << "\t" << x << std::endl;
        });
        std::cout << "}" << std::endl;
    }

    {
        std::vector<std::string> wordDict {"cat","cats","and","sand","dog"};
        auto input = "catsandog";

        std::cout << "Result: {" << std::endl;
        std::ranges::for_each(Solution().wordBreak(input, wordDict), [] (auto x) {
            std::cout << "\t" << x << std::endl;
        });
        std::cout << "}" << std::endl;
    }
}
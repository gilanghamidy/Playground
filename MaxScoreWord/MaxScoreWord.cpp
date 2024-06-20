#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <string>
#include <array>
#include <cstdint>

struct CharMatrix
{
    std::array<int8_t, 26> scores;

    CharMatrix() { std::ranges::fill(scores, 0); }

    CharMatrix(std::vector<int> const& score) { std::ranges::copy(score, scores.begin()); }

    CharMatrix(std::vector<char> const& letters) 
    {
        std::ranges::fill(scores, 0);
        std::ranges::for_each(letters, [&] (char c) { scores[c - 'a']++; });
    }

    CharMatrix operator-(CharMatrix const& that) const
    {
        CharMatrix ret;
        std::ranges::transform(scores, that.scores, ret.scores.begin(), std::minus<int8_t>{});
        return ret;
    }

    operator bool()
    {
        return std::ranges::find_if(scores, [] (int8_t a) { return a < 0; }) == scores.end();
    }
};

class Solution {
public:
    int maxScoreWords(std::vector<std::string> const& words, std::vector<char> const& letters, std::vector<int> const& score) {
        CharMatrix scoreMatrix (score);
        std::vector<std::pair<int, CharMatrix>> wordScores;

        std::ranges::transform(words, std::back_inserter(wordScores), [&] (std::string const& word) 
        {
            std::pair<int, CharMatrix> ret;
            ret.first = std::accumulate(word.begin(), word.end(), 0, [&] (int x, char y) { 
                ret.second.scores[y - 'a']++;
                return scoreMatrix.scores[y - 'a'] + x; 
            });
            return ret;
        });

        CharMatrix letterAvailable (letters);

        auto dfs = [&] (auto& dfs, int idx, CharMatrix const& remaining)
        {
            // Base case
            if(idx == wordScores.size())
                return 0;

            // Score without
            int score = dfs(dfs, idx + 1, remaining);

            auto afterTaking = remaining - wordScores[idx].second;
            if(afterTaking)
                score = std::max(score, dfs(dfs, idx + 1, afterTaking) + wordScores[idx].first);
            
            return score;
        };

        return dfs(dfs, 0, letterAvailable);
    }
};

int main()
{

    {
        std::vector<std::string> words = {"dog","cat","dad","good"}; 
        std::vector<char> letters = {'a','a','c','d','d','d','g','o','o'};
        std::vector<int> score = {1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0};

        std::cout << "Res: " << Solution().maxScoreWords(words, letters, score) << std::endl;
    }
}
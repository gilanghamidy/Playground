#include <vector>
#include <iostream>
#include <algorithm>
auto res = [] () {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);
    return 0;
} ();


class Solution {
public:
    int maxSatisfied(std::vector<int> const& customers, std::vector<int> const& grumpy, int minutes) {
        
        int cumulativeSum = 0;
        int cumulativeGrumpy = 0;
        int countdown = 0;
        
        std::vector<std::pair<int, int>> consecutiveSum;
        consecutiveSum.reserve(customers.size());
        
        for(int i = 0; i < customers.size(); i++)
        {
            if(minutes == 1)
                consecutiveSum.emplace_back(1, grumpy[i] ? customers[i] : 0);
            else
            {
                if(i >= minutes - 1)
                {
                    if(i - minutes >= 0)
                    {
                        cumulativeSum -= grumpy[i - minutes] ? customers[i - minutes] : 0;
                        cumulativeGrumpy -= grumpy[i - minutes];
                    }
                    
                    cumulativeSum += grumpy[i] ? customers[i] : 0;
                    cumulativeGrumpy += grumpy[i];
                    consecutiveSum.emplace_back(cumulativeGrumpy, cumulativeSum);
                }
                else
                {
                    cumulativeSum += grumpy[i] ? customers[i] : 0;
                    cumulativeGrumpy += grumpy[i];
                }
            }
        }

        int idxMaxStart = std::distance(consecutiveSum.begin(), std::ranges::max_element(consecutiveSum, [] (auto const& a, auto const& b) { return a.second < b.second || (a.second == b.second && a.first < b.first); }));
        int idxMaxEnd = idxMaxStart + minutes;

        int sum = 0;
        for(int i = 0; i < customers.size(); i++)
        {
            if(!grumpy[i] || (idxMaxStart <= i && i < idxMaxEnd))
            {
                sum += customers[i];
            }
        }
        
        return sum;
    }
};

int main()
{
    std::cout << Solution().maxSatisfied({1,0,1,2,1,1,7,5}, {0,1,0,1,0,1,0,1}, 3) << std::endl;
}
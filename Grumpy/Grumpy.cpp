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
        int sum = 0;
        std::pair<int, int> maxElement { 0, 0 };
        
        for(int i = 0; i < customers.size(); i++)
        {
            if(minutes == 1 && grumpy[i])
                maxElement = std::max(maxElement, std::pair { 1, customers[i] }, [] (auto const& a, auto const& b) { return a.second < b.second || (a.second == b.second && a.first < b.first); });
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
                    
                    maxElement = std::max(maxElement, std::pair { cumulativeGrumpy, cumulativeSum }, [] (auto const& a, auto const& b) { return a.second < b.second || (a.second == b.second && a.first < b.first); });
                }
                else
                {
                    cumulativeSum += grumpy[i] ? customers[i] : 0;
                    cumulativeGrumpy += grumpy[i];
                }
            }
            
            if(!grumpy[i])
                sum += customers[i];
            
        }

        return sum + maxElement.second;
    }
};

int main()
{
    std::cout << Solution().maxSatisfied({1,0,1,2,1,1,7,5}, {0,1,0,1,0,1,0,1}, 3) << std::endl;
}
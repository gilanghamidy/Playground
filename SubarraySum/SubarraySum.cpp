#include <iostream>
#include <vector>
#include <unordered_map>

class Solution 
{
public:
    int subarraysDivByK(std::vector<int> const& nums, int k) {
        std::unordered_map<int, int> modMap;
        int sum = 0;
        int counter = 0;
        modMap[0] = 1;

        for(int n : nums)
        {
            
            sum = (sum + n % k + k) % k;
            counter += modMap[sum];
            modMap[sum]++;
        }
        return counter;
    }
};

int main()
{
    std::cout << Solution().subarraysDivByK({4,5,0,-2,-3,1}, 5) << " 7\n";
}
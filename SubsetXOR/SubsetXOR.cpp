#include <climits>
#include <limits>
#include <vector>
#include <array>
#include <cstdint>
#include <iostream>

constexpr uint8_t CountOnes(uint16_t val)
{
    uint8_t count = 0;
    while (val != 0) {
        if((val & 1) != 0)
            count++;
        val = val >> 1;    
    }
    return count;
}

constexpr std::array<uint8_t, 12> GetIndex(uint16_t n)
{
    std::array<uint8_t, 12> ret;
    
    int count = 0;
    int radix = 0;
    int val = n;
    while (val != 0) {
        if((val & 1) != 0)
        {
            ret[count] = radix;
            count++;
        }
        radix++;
        val = val >> 1;
    }

    for(int i = count; i < ret.size(); i++)
        ret[i] = std::numeric_limits<uint8_t>::max();
    
    return ret;
}

constexpr std::array<std::array<uint8_t, 12>, 4096> BuildIndexMap()
{
    std::array<std::array<uint8_t, 12>, 4096> ret;

    for(int i = 0; i < 4096; i++)
        ret[i] = GetIndex(i);

    return ret;
}

auto map = BuildIndexMap();

constexpr size_t MaxCombination(int size)
{
    return 1 << size;
}


class Solution {
public:
    int subsetXORSum(std::vector<int>& nums) 
    {
        int max = MaxCombination(nums.size());

        int sum = 0;

        for(int i = 1; i < max; i++)
        {
            auto& arr = map[i];
            int xorSum = nums[arr[0]];
            for(int idx = 1; idx < 12 && arr[idx] != std::numeric_limits<uint8_t>::max(); idx++)
                xorSum = xorSum ^ nums[arr[idx]];
            sum += xorSum;
        }

        return sum;
    }
};

int main()
{
    {
        std::vector<int> nums = {10,5,8,3,6,12,2,4,11,7,1,9};
        int res = Solution().subsetXORSum(nums);
        std::cout << "Res: " << res << std::endl;
    }
    
    {
        std::vector<int> nums = {3,4,5,6,7,8};
        int res = Solution().subsetXORSum(nums);
        std::cout << "Res: " << res << std::endl;
    }
}
#include <iostream>
#include <vector>

class Solution {
public:
    int backtrackTriplet(std::vector<int> const& arr, size_t begin, size_t end, std::vector<int>& cumulativeSum, int currentSum)
    {
        if(begin == end)
        {
            if((currentSum ^ arr[end]) == cumulativeSum.back())
                return 1;
            return 0;
        }
            

        int expectedSum = cumulativeSum.back();
        cumulativeSum.pop_back();

        int count = 0;

        int thisSum = currentSum ^ arr[end];
        if(thisSum == cumulativeSum.back())
            count += 1;

        count += backtrackTriplet(arr, begin, end - 1, cumulativeSum, thisSum);

        cumulativeSum.push_back(expectedSum);
        return count;
    }

    int countTriplets(std::vector<int> const& arr) {
        std::vector<int> xorSum;



        int count = 0;
        for(size_t i = 0; i < arr.size(); i++)
        {
            int sum = 0;
            std::vector<int> cumulativeSum;
            for(size_t j = i; j < arr.size(); j++)
            {
                sum = sum ^ arr[j];
                cumulativeSum.push_back(sum);
                if(sum == 0)
                {
                    count += backtrackTriplet(arr, i, j, cumulativeSum, 0);
                }
            }
        }
        
        return count;
    }
};

int main()
{
    std::cout << Solution().countTriplets({2,3,1,6,7}) << std::endl;
    std::cout << "Haha" << std::endl;
    std::cout << Solution().countTriplets({1,1,1,1,1}) << std::endl;
}
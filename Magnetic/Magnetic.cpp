#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

class Solution {
public:
    int maxDistance(std::vector<int>&& position, int m) 
    {
        std::ranges::sort(position);
        int a = 1, c = std::ceil((double)position.back() / (m - 1)), ret = 0;
        while (a <= c)
        {
            int b = a + (c - a) / 2;
            
            int curr = position[0];
            int count = 1;
            
            for(int i = 1; i < position.size() && count < m; i++)
                if(position[i] - curr >= b)
                    count++ && (curr = position[i]);
            
            if(count == m)
                ret = b, a = b + 1;
            else
                c = b - 1;
            
        }
        return ret;
    }
};

int main()
{
    std::cout << Solution().maxDistance({79,74,57,22}, 4) << std::endl;

    std::cout << Solution().maxDistance({1,2,3,4,5,6,7,8,9,10}, 4) << std::endl;
}
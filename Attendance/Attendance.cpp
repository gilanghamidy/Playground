#include <array>
#include <iostream>
#include <vector>



class Solution {
public:
    int checkRecord(int n) {
        auto dpRec = 
        [ memo = std::vector<std::array<std::array<int, 3>, 2>> (n + 1, {std::array<int, 3> {-1, -1, -1}, {-1, -1, -1}}) ] 
        (auto& dpRec, int current, int absent, int late) mutable 
        {
            constexpr int modulus = 1000000007;

            if(absent >= 2 || late >= 3)
                return 0;

            if(current == 0)
                return 1;

            if(auto val = memo[current][absent][late]; val != -1)
                return val;

            int count = dpRec(dpRec, current - 1, absent, 0);
            count = (count + dpRec(dpRec, current - 1, absent + 1, 0)) % modulus;
            count = (count + dpRec(dpRec, current - 1, absent, late + 1)) % modulus;

            return memo[current][absent][late] = count;
                
        };

        return dpRec(dpRec, n, 0, 0);
    }
};

int main()
{

    std::cout << Solution().checkRecord(2) << std::endl;
    std::cout << Solution().checkRecord(1) << std::endl;
    std::cout << Solution().checkRecord(10101) << std::endl;
}
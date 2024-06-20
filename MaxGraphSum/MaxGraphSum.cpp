#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <queue>

struct TreeNode
{
    int idx;
    int num;
    int numXor;

    std::vector<std::reference_wrapper<TreeNode>> children;

    bool needXor() { return numXor > num; }
    bool visited { false };
    

    TreeNode(int idx, int num, int k) : idx(idx), num(num), numXor(num ^ k) { }
};

class Solution {
public:


    long long maximumValueSum(std::vector<int>& nums, int k, std::vector<std::vector<int>>& edges) {

        std::vector<TreeNode> treeNodes;

        int counter = 0;
        std::ranges::for_each(nums, [&] (int x) {
            treeNodes.emplace_back(counter++, x, k);
        });

        std::ranges::for_each(edges, [&] (std::vector<int> const& ref) {
            int first = ref[0];
            int second = ref[1];
            treeNodes[first].children.emplace_back(treeNodes[second]);
        });

        // BFS
        std::queue<std::reference_wrapper<TreeNode>> bfsQueue;
        bfsQueue.push(treeNodes[0]);

        while(!bfsQueue.empty())
        {
            TreeNode& current = bfsQueue.front();
            bfsQueue.pop();

            std::cout << "Visit: " << current.idx << std::endl;

            

            std::ranges::for_each(current.children, [&] (auto const& nodeRef) { 
                bfsQueue.push(nodeRef);
            });
        }


        return 0;
    }
};

int main()
{
    {
        std::vector<int> nums  { 1, 2, 1 };
        int k = 3;
        std::vector<std::vector<int>> edges {{0,1},{0,2}};
        int res = Solution().maximumValueSum(nums, k, edges);
        std::cout << "Res: " << res << std::endl;
    }

    {
        std::vector<int> nums  {7, 7, 7, 7, 7, 7};
        int k = 3;
        std::vector<std::vector<int>> edges {{0,1},{0,2},{0,3},{0,4},{0,5}};
        int res = Solution().maximumValueSum(nums, k, edges);
        std::cout << "Res: " << res << std::endl;
    }
}
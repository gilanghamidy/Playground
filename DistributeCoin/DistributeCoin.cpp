 #include <tuple>
 
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

struct Settlement
{
    int coins;
    int danglingSteps;
    int accumulatedSteps;
};
 
class Solution {
public:
    int distributeCoins(TreeNode* root) {
        return 0;
    }

    Settlement dfsDistribtion(TreeNode* current, int depth)
    {
        if(!current)
        {
            return {0, 0, 0};
        }
        else if(!current->left && !current->right)
        {
            if(current->val == 1)
                return {0, 0,0};
            else if(current->val == 0) 
                return {-1, 1,0};
            else 
                return {current->val - 1, current->val - 1, 0};
        }
        else 
        {
            Settlement childRes[] = {
                dfsDistribtion(current->left, depth + 1),
                dfsDistribtion(current->right, depth + 1)
            };

            if(childRes[0].coins < 0 && childRes[1].coins < 0 || childRes[0].coins > 0 && childRes[1].coins > 0)
            {
                childRes[0].coins += childRes[1].coins;
                childRes[0].accumulatedSteps += childRes[1].accumulatedSteps;
                childRes[0].danglingSteps += childRes[1].danglingSteps;

                

                return childRes[0];
            }

            

        }
    }


};

int main()
{
    TreeNode root { 0, new TreeNode(3), new TreeNode(0)};

}
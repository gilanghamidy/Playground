#include <algorithm>
#include <alloca.h>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

struct Node
{
    std::vector<std::reference_wrapper<Node>> edgeList;
    int value;
    mutable bool visited { false };

    Node(int val) : value(val) { }
};

int dfsMax( Node const& visit, int value ) { 
    int max = value + visit.value;
    visit.visited = true;
    for(auto item : visit.edgeList)
        if(!item.get().visited)
            max = std::max(max, dfsMax(item.get(), value + visit.value));
    visit.visited = false;
    return max; 
}

class Solution {
public:
    int getMaximumGold(std::vector<std::vector<int>>& grid) 
    {
        int height = grid.size();
        int width = grid[0].size();

        int max = 0;

        std::vector<std::vector<Node>> nodeList;
        nodeList.reserve(grid.size());

        // Build node map
        std::ranges::for_each(grid, [&] (auto& x) { 
            auto& curr = nodeList.emplace_back();
            curr.reserve(x.size());
            std::ranges::for_each(x, [&] (auto y) {
                curr.emplace_back(y);
                max = std::max(max, y);
            });
        });

        std::vector<std::reference_wrapper<Node>> goldNode;

        for(int y = 0; y < height; y++)
            for(int x = 0; x < width; x++)
            {
                auto& currentNode = nodeList[y][x];
                if(currentNode.value == 0)
                    continue;

                goldNode.emplace_back(currentNode);

                if(x - 1 >= 0 && nodeList[y][x-1].value != 0)
                    currentNode.edgeList.emplace_back(nodeList[y][x-1]);
                if(x + 1 < width && nodeList[y][x+1].value != 0)
                    currentNode.edgeList.emplace_back(nodeList[y][x+1]);
                if(y - 1 >= 0 && nodeList[y-1][x].value != 0)
                    currentNode.edgeList.emplace_back(nodeList[y-1][x]);
                if(y + 1 < height && nodeList[y+1][x].value != 0)
                    currentNode.edgeList.emplace_back(nodeList[y+1][x]);
                
            }

        for(auto current: goldNode)
        {
            max = std::max(max, dfsMax(current, 0));
        }


        return max;
    }
};

typedef struct GoldNode {
    struct GoldNode* edgeList[5];
    int value;
    int visited;
} GoldNode;

int index(int x, int y, int width)
{
    return y * width + x;
}

int dfsMax(GoldNode* visit, int value) { 
    int max = value + visit->value;
    visit->visited = true;
    for(GoldNode** curr = visit->edgeList; *curr != NULL; curr++)
    {
        if(!(*curr)->visited)
        {
            int newMax = dfsMax(*curr, value + visit->value);
            if(newMax > max)
                max = newMax;
        }
    }
    visit->visited = false;
    return max; 
}

int getMaximumGold(int** grid, int height, int* gridColSize)
{
    int width = gridColSize[0];

    GoldNode nodeMap[height * width];
    GoldNode* filledNode[26];
    memset(nodeMap, 0, sizeof(GoldNode) * (height * width));
    memset(filledNode, 0, sizeof(GoldNode*) + 26);

    int fillIdx = 0;

    // Build node map
    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
        {
            if(grid[y][x] == 0)
                continue;

            GoldNode* currentNode = &nodeMap[index(x, y, width)];
            filledNode[fillIdx++] = currentNode;
            currentNode->value = grid[y][x];

            int edgeIdx = 0;

            if(x - 1 >= 0 && grid[y][x-1] != 0)
                currentNode->edgeList[edgeIdx++] = &nodeMap[index(x - 1, y, width)];
            if(x + 1 < width && grid[y][x+1] != 0)
                currentNode->edgeList[edgeIdx++] = &nodeMap[index(x + 1, y, width)];
            if(y - 1 >= 0 && grid[y-1][x] != 0)
                currentNode->edgeList[edgeIdx++] = &nodeMap[index(x, y - 1, width)];
            if(y + 1 < height && grid[y+1][x] != 0)
                currentNode->edgeList[edgeIdx++] = &nodeMap[index(x, y + 1, width)];
        }

    int max = 0;
    for(GoldNode** curr = filledNode; *curr != NULL; curr++)
    {
        int newMax = dfsMax(*curr, 0);
        if(newMax > max)
            max = newMax;
    }
    return max;
}


int main()
{
    {
        std::vector<std::vector<int>> grid {{0,0,1},
                                            {1,1,0},
                                            {1,1,0}};

        int maxGold = Solution().getMaximumGold(grid);

        std::cout << "Res (4): " << maxGold << "\n";
    }

    {
        std::vector<std::vector<int>> grid {{0,6,0},
                                            {5,8,7},
                                            {0,9,0}}
;

        int maxGold = Solution().getMaximumGold(grid);

        std::cout << "Res (24): " << maxGold << "\n";
    }

    {
        std::vector<std::vector<int>> grid {{1,0,7},
                                            {2,0,6},
                                            {3,4,5},
                                            {0,3,0},
                                            {9,0,20}};

        int maxGold = Solution().getMaximumGold(grid);

        std::cout << "Res (28): " << maxGold << "\n";
    }
}
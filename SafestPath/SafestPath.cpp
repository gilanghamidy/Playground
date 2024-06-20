#include <algorithm>
#include <deque>
#include <limits>
#include <optional>
#include <queue>
#include <vector>
#include <iostream>
#include <array>

struct SafeMapNode
{
    int val { std::numeric_limits<int>::max() };
    bool visited { false };
};

struct PathfindQueue
{
    std::pair<int, int> coordinate;
    int val;

    PathfindQueue(int x, int y, int val) : coordinate(x, y), val(val) { }
};

class Solution {
public:
    
    static int manhattanDistance(std::pair<int, int> a, std::pair<int, int> b)
    {
        return std::abs(a.first - b.first) + std::abs(a.second - b.second);
    }

    static int greedyPathfind(std::vector<std::vector<SafeMapNode>>& grid)
    {
        int minSafety = grid[0][0].val;

        int height = grid.size();
        int width = grid[0].size();

        std::deque<PathfindQueue> queue;

        queue.emplace_back(0, 0, grid[0][0].val);

        while(!queue.empty())
        {
            auto front = queue.front();
            queue.pop_front();

            minSafety = std::min(minSafety, front.val);
            auto [x, y] = front.coordinate;

            if(x == width - 1 && y == height - 1)
                break;

            std::array<std::pair<int, int>, 4> nextCoord {{{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}}};

            auto bound = [width, height] (int x, int y) { return x >= 0 && y >= 0 && x < width && y < height; };

            for(auto [nextX, nextY] : nextCoord)
                if(bound(nextX, nextY) && grid[nextY][nextX].visited)
                {
                    int safety = grid[nextY][nextX].val;
                    grid[nextY][nextX].visited = false;

                    if(safety < minSafety)
                        queue.emplace_back(nextX, nextY, safety);
                    else
                        queue.emplace_front(nextX, nextY, safety);
                }
        }

        return minSafety;

    }

    static int maximumSafenessFactor(std::vector<std::vector<int>>& grid) {
        int x = 0, y = 0;

        std::vector<std::vector<SafeMapNode>> safeMap;
        for(int i = 0; i < grid.size(); i++)
        {
            safeMap.emplace_back(static_cast<size_t>(grid[i].size()));
        }

        std::deque<PathfindQueue> processingQueue;
        std::ranges::for_each(grid, [&] (auto& xList) {
            std::ranges::for_each(xList, [&] (auto v) {
                if(v == 1)
                {
                    processingQueue.emplace_back(x, y, 1);
                    safeMap[y][x].val = 0;
                    safeMap[y][x].visited = true;
                }
                x++;
            });
            x = 0;
            y++;
        });

        int height = grid.size();
        int width = grid[0].size();



        auto bound = [width, height] (int x, int y) { return x >= 0 && y >= 0 && x < width && y < height; };

        while(!processingQueue.empty())
        {
            auto front = processingQueue.front();
            processingQueue.pop_front();
            auto [x, y] = front.coordinate;

            std::array<std::pair<int, int>, 4> nextCoord {{{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}}};
            for(auto [nextX, nextY] : nextCoord)
                if(bound(nextX, nextY) && !safeMap[nextY][nextX].visited)
                {
                    safeMap[nextY][nextX].val = front.val;
                    safeMap[nextY][nextX].visited = true;
                    processingQueue.emplace_back(nextX, nextY, front.val + 1);
                }
            
        }

        std::ranges::for_each(safeMap, [&] (auto& xList) {
            std::ranges::for_each(xList, [&] (auto v) {
                std::cout << v.val << " ";
            });
            std::cout << std::endl;
        });
        

        return greedyPathfind(safeMap);
    }
};

int main()
{
    {
        std::vector<std::vector<int>> grid {{0,0,0,1},
                                            {0,0,0,0},
                                            {0,0,0,0},
                                            {1,0,0,0}};

        int maxGold = Solution().maximumSafenessFactor(grid);

        std::cout << "Res (2): " << maxGold << "\n";
    }

    {
        std::vector<std::vector<int>> grid {{0,0,1},
                                            {0,0,0},
                                            {0,0,0}};

        int maxGold = Solution().maximumSafenessFactor(grid);

        std::cout << "Res (2): " << maxGold << "\n";
    }
}
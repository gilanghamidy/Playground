#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>

struct Project
{
    int profit;
    int capital;

    Project(int profit, int capital) : profit(profit), capital(capital) { }

    bool operator<(Project const& that) const
    {
        return  profit < that.profit;
    }
};


class Solution {
public:
    int findMaximizedCapital(int k, int w, std::vector<int> const& profits, std::vector<int> const& capital) 
    {
        std::vector<Project> project;
        project.reserve(profits.size());
        
        for(int i = 0; i < profits.size(); i++)
            project.emplace_back(profits[i], capital[i]);

        std::ranges::sort(project, [] (Project const& a, Project const& b) {
            return a.capital > b.capital;
        });

        std::priority_queue<Project> topProjects;

        for(;k > 0; k--)
        {
            auto iter = std::ranges::find_if(project, [&] (auto& proj) { return proj.capital <= w; });

            std::for_each(iter, project.end(), [&] (auto& proj) { 
                topProjects.emplace(proj);
            });

            project.erase(iter, project.end());

            if(topProjects.empty())
                break;

            Project top = topProjects.top();
            topProjects.pop();

            w += top.profit;
        }
        
        return w;
    }
};

int main()
{
    std::cout << Solution().findMaximizedCapital(3, 0,  {1,2,3},  {0,1,2}) << std::endl;
    std::cout << Solution().findMaximizedCapital(2, 0,  {1,2,3},  {0,1,1}) << std::endl;
    std::cout << Solution().findMaximizedCapital(2, 0,  {1,2,3},  {0,1,1}) << std::endl;
}
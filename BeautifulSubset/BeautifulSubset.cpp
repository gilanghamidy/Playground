#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>
#include <iostream>
#include <cstdint>
#include <unordered_set>

struct SequenceNode
{
    uint16_t num;
    std::vector<std::reference_wrapper<SequenceNode>> next;
    bool visited;
};

struct SubsetMap
{
    uint16_t count;
    uint16_t nums[20];

    bool operator==(SubsetMap const& that) const
    {
        if(that.count != this->count)
            return false;

        for(int i = 0; i < this->count; i++)
            if(nums[i] != that.nums[i])
                return false;

        return true;
    }
};

template<>
struct std::hash<SubsetMap>
{
    size_t operator()(const SubsetMap& s) const noexcept
    {
        size_t ret = s.count;
        for(int i = 0; i < s.count; i++)
        {
            ret = ret ^ s.nums[i];
            ret = ret << 8;
        }
        
        return ret;
    }
};

void dfs(SequenceNode& node, std::unordered_set<SubsetMap>& subset, SubsetMap& current)
{

    current.nums[current.count++] = node.num;
    subset.insert(current);
    for(auto& next : node.next)
        dfs(next, subset, current);
    current.count--;
}

struct Solution
{
    int beautifulSubsets(std::vector<int>& nums, int k)
    {
        std::vector<SequenceNode> numsGraph;
        std::ranges::sort(nums);
        std::ranges::for_each(nums, [&] (auto num) {
            numsGraph.emplace_back(num);
        });

        for(int i = 0; i < nums.size(); i++)
        {
            auto& currentNode = numsGraph[i];
            for(int j = i + 1; j < nums.size(); j++)
            {
                int diff = currentNode.num - nums[j];
                if(diff != k && diff != -k)
                {
                    currentNode.next.emplace_back(numsGraph[j]);
                }
            }
        }
        
        std::unordered_set<SubsetMap> subsets;

        std::ranges::for_each(numsGraph, [&] (auto& node) { 
            SubsetMap map { 0 };
            dfs(node, subsets, map);
        });


        int count = 0;
        std::ranges::for_each(subsets, [&] (SubsetMap const& subset) {
            for(int i = 0; i < subset.count; i++)
                for(int j = i + 1; j < subset.count; j++)
                    if(int diff = subset.nums[i] - subset.nums[j]; diff == k || diff == -k)
                        return;
            count++;
        });


        return count;
    }
};

class Solution2 {
public:
    int beautifulSubsets(std::vector<int>& nums, int k) {
        // Frequency map to track elements
        std::unordered_map<int, int> freqMap;
        // Sort nums array
        sort(nums.begin(), nums.end());
        return countBeautifulSubsets(nums, k, freqMap, 0) - 1;
    }

private:
    int countBeautifulSubsets(std::vector<int>& nums, int difference, std::unordered_map<int, int>& freqMap, int i) {
        // Base case: Return 1 for a subset of size 1
        if (i == nums.size()) {
            std::cout << "[ ";
            std::ranges::for_each(freqMap, [] (auto& x) {
                if(x.second != 0)
                    std::cout << x.first << " ";
            });
            std::cout << "]\n";
            return 1;
        }
        // Count subsets where nums[i] is not taken
        int totalCount = countBeautifulSubsets(nums, difference, freqMap,
                                               i + 1); // nums[i] not taken

        // If nums[i] can be taken without violating the condition
        if (!freqMap[nums[i] - difference]) {
            freqMap[nums[i]]++;
            // Recursively count subsets where nums[i] is taken
            totalCount += countBeautifulSubsets(nums, difference, freqMap,
                                                i + 1); // nums[i] taken
            freqMap[nums[i]]--;
        }

        return totalCount;
    }
};

int main()
{
    {
        std::vector<int> nums {20,14,22,1,4,11,21,19,29,25,12,18,9,15,23,6,27,16,26,5};
        int k = 13;
        std::cout << "Res: " << Solution2().beautifulSubsets(nums, k) << std::endl;
    }
}
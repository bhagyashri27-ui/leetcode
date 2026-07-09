#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        
        vector<int> compId(n, 0);
        int currentId = 0;
        
        compId[0] = currentId;
        for (int i = 1; i < n; ++i) {
           
            if (nums[i] - nums[i-1] > maxDiff) {
                
                currentId++;
            }
            compId[i] = currentId;
        }
        
        
        int q = queries.size();
        vector<bool> answer(q);
        
        for (int i = 0; i < q; ++i) {
            int u = queries[i][0];
            int v = queries[i][1];
            
            
            answer[i] = (compId[u] == compId[v]);
        }
        
        return answer;
    }
};

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
       
        vector<pair<int, int>> sorted_nodes(n);
        for (int i = 0; i < n; ++i) {
            sorted_nodes[i] = {nums[i], i};
        }
       
        sort(sorted_nodes.begin(), sorted_nodes.end());

        vector<int> vals(n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            vals[i] = sorted_nodes[i].first;
            pos[sorted_nodes[i].second] = i;
        }

        
        vector<int> nxt(n);
        for (int i = 0; i < n; ++i) {
            int target_val = vals[i] + maxDiff;
          
            auto it = upper_bound(vals.begin(), vals.end(), target_val);
            nxt[i] = (it - vals.begin()) - 1;
        }

      
        int LOG = 18; 
        vector<vector<int>> up(LOG, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            up[0][i] = nxt[i];
        }

        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int u = q[0];
            int v = q[1];

            if (u == v) {
                answer.push_back(0);
                continue;
            }
            if (nums[u] == nums[v]) {
                answer.push_back(1);
                continue;
            }

            int p1 = pos[u];
            int p2 = pos[v];
            if (vals[p1] > vals[p2]) {
                swap(p1, p2);
            }

            int target = vals[p2];
            int curr = p1;
            int steps = 0;

            
            for (int j = LOG - 1; j >= 0; --j) {
                int next_node = up[j][curr];
                if (vals[next_node] < target && next_node != curr) {
                    curr = next_node;
                    steps += (1 << j);
                }
            }

            if (vals[nxt[curr]] >= target) {
                answer.push_back(steps + 1);
            } else {
                answer.push_back(-1);
            }
        }

        return answer;
    }
};

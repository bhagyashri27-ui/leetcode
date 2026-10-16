#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    static const int MOD = 1e9 + 7;
    
    struct Node {
        long long sum = 0;
        long long lazy = 0;
    };

    vector<Node> tree;

    void push(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            long long val = tree[node].lazy;
            int mid = (l + r) / 2;
            
            // Left child
            tree[2 * node].sum = (tree[2 * node].sum + val * (mid - l + 1)) % MOD;
            tree[2 * node].lazy = (tree[2 * node].lazy + val) % MOD;
            
            // Right child
            tree[2 * node + 1].sum = (tree[2 * node + 1].sum + val * (r - mid)) % MOD;
            tree[2 * node + 1].lazy = (tree[2 * node + 1].lazy + val) % MOD;
            
            tree[node].lazy = 0;
        }
    }

    void update(int node, int l, int r, int ql, int qr, long long val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node].sum = (tree[node].sum + val * (r - l + 1)) % MOD;
            tree[node].lazy = (tree[node].lazy + val) % MOD;
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node].sum = (tree[2 * node].sum + tree[2 * node + 1].sum) % MOD;
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node].sum;
        push(node, l, r);
        int mid = (l + r) / 2;
        return (query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr)) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        tree.assign(4 * n + 1, Node());
        
        unordered_map<int, int> last_pos;
        long long current_sum_squares = 0;
        long long total_sum = 0;

        for (int j = 0; j < n; ++j) {
            int last = -1;
            if (last_pos.find(nums[j]) != last_pos.end()) {
                last = last_pos[nums[j]];
            }
            
            // Subarrays starting from last + 1 to j have their distinct count increased by 1
            long long sum_subarray_counts = query(1, 0, n - 1, last + 1, j);
            current_sum_squares = (current_sum_squares + 2 * sum_subarray_counts + (j - last)) % MOD;
            
            update(1, 0, n - 1, last + 1, j, 1);
            last_pos[nums[j]] = j;
            
            total_sum = (total_sum + current_sum_squares) % MOD;
        }

        return total_sum;
    }
};
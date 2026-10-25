class Solution {
private:
    bool dfs(int r, int c, vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // If we hit the boundary, this island touches the edge and is NOT closed.
        if (r < 0 || r >= m || c < 0 || c >= n) {
            return false;
        }
        
        // If it's water (1), it's safe boundary/surrounding.
        if (grid[r][c] == 1) {
            return true;
        }
        
        // Mark current land as visited by turning it into water (1)
        grid[r][c] = 1;
        
        // Traverse all 4 directions
        bool left = dfs(r, c - 1, grid);
        bool right = dfs(r, c + 1, grid);
        bool up = dfs(r - 1, c, grid);
        bool down = dfs(r + 1, c, grid);
        
        // An island is closed only if all four directions are valid (don't touch the border)
        return left && right && up && down;
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Step 1: Eliminate all 0s connected to the borders
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ((i == 0 || i == m - 1 || j == 0 || j == n - 1) && grid[i][j] == 0) {
                    dfs(i, j, grid);
                }
            }
        }
        
        // Step 2: Count the remaining closed islands in the interior
        int closedIslandsCount = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    // If DFS returns true, it's completely surrounded by 1s
                    if (dfs(i, j, grid)) {
                        closedIslandsCount++;
                    }
                }
            }
        }
        
        return closedIslandsCount;
    }
};
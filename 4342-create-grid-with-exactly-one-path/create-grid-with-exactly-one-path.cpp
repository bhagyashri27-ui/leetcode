class Solution {
public:
    vector<string> createGrid(int m, int n) {
        // Initialize the grid with all obstacles '#'
        vector<string> grid(m, string(n, '#'));
        
        // Carve a path: go all the way right on the first row, then all the way down on the last column
        for (int j = 0; j < n; ++j) {
            grid[0][j] = '.';
        }
        for (int i = 0; i < m; ++i) {
            grid[i][n - 1] = '.';
        }
        
        return grid;
    }
};
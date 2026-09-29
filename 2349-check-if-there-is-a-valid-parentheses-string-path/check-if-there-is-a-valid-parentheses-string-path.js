/**
 * @param {character[][]} grid
 * @return {boolean}
 */
var hasValidPath = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    
    // A valid parentheses string must have an even length
    if ((m + n - 1) % 2 !== 0) return false;
    // Must start with '(' and end with ')'
    if (grid[0][0] === ')' || grid[m - 1][n - 1] === '(') return false;
    
    // visited[r][c][bal] tracks if we've visited cell (r, c) with a specific balance
    const maxBal = Math.floor((m + n) / 2);
    const visited = Array.from({ length: m }, () => 
        Array.from({ length: n }, () => new Array(maxBal + 1).fill(false))
    );
    
    // Queue stores elements as [r, c, bal]
    const queue = [[0, 0, 1]];
    visited[0][0][1] = true;
    
    while (queue.length > 0) {
        const [r, c, bal] = queue.shift();
        
        // If we reached the bottom-right corner and balance is 0, we found a valid path
        if (r === m - 1 && c === n - 1 && bal === 0) {
            return true;
        }
        
        // Explore moving Down and Right
        const directions = [[r + 1, c], [r, c + 1]];
        
        for (const [nextR, nextC] of directions) {
            if (nextR < m && nextC < n) {
                const nextBal = bal + (grid[nextR][nextC] === '(' ? 1 : -1);
                
                // Keep balance within valid boundaries: 
                // 1. Cannot go below 0
                // 2. Cannot exceed max possible balance needed to close the remaining path
                if (nextBal >= 0 && nextBal <= maxBal && !visited[nextR][nextC][nextBal]) {
                    visited[nextR][nextC][nextBal] = true;
                    queue.push([nextR, nextC, nextBal]);
                }
            }
        }
    }
    
    return false;
};

/**
 * @param {number[]} nums
 * @return {number}
 */
var numOfWays = function(nums) {
    const MOD = 1000000007n; // Using BigInt to prevent arithmetic overflow
    const n = nums.length;
    
    // Precompute Pascal's Triangle for combinations nCr % MOD
    const table = Array.from({ length: n + 1 }, () => new Array(n + 1).fill(0n));
    for (let i = 0; i <= n; i++) {
        table[i][0] = 1n;
        for (let j = 1; j <= i; j++) {
            table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MOD;
        }
    }
    
    // Helper function to recursively compute the number of ways
    function dfs(arr) {
        if (arr.length <= 2) return 1n;
        
        const root = arr[0];
        const left = [];
        const right = [];
        
        // Partition elements into left and right subtrees
        for (let i = 1; i < arr.length; i++) {
            if (arr[i] < root) {
                left.push(arr[i]);
            } else {
                right.push(arr[i]);
            }
        }
        
        const leftWays = dfs(left);
        const rightWays = dfs(right);
        const lLen = left.length;
        const rLen = right.length;
        
        // Formuala: combinations(L+R, L) * ways(left) * ways(right)
        return (table[lLen + rLen][lLen] * leftWays % MOD) * rightWays % MOD;
    }
    
    // Subtract 1 to exclude the original permutation
    const ans = (dfs(nums) - 1n + MOD) % MOD;
    return Number(ans);
};

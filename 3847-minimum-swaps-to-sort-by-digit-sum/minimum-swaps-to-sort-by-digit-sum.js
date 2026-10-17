/**
 * @param {number[]} nums
 * @return {number}
 */
var minSwaps = function(nums) {
    const n = nums.length;
    
    // Helper function to calculate the sum of digits of a number
    const getDigitSum = (num) => {
        let sum = 0;
        while (num > 0) {
            sum += num % 10;
            num = Math.floor(num / 10);
        }
        return sum;
    };
    
    // Create an array of objects storing value, digit sum, and original index
    const arr = nums.map((val, idx) => ({
        val: val,
        digitSum: getDigitSum(val),
        idx: idx
    }));
    
    // Sort based on digit sum first, then by value
    arr.sort((a, b) => {
        if (a.digitSum !== b.digitSum) {
            return a.digitSum - b.digitSum;
        }
        return a.val - b.val;
    });
    
    // Track visited nodes to count permutation cycles
    const visited = new Array(n).fill(false);
    let swaps = 0;
    
    for (let i = 0; i < n; i++) {
        // If already visited or already in the correct position
        if (visited[i] || arr[i].idx === i) {
            continue;
        }
        
        // Traverse the cycle
        let cycleSize = 0;
        let curr = i;
        while (!visited[curr]) {
            visited[curr] = true;
            curr = arr[curr].idx;
            cycleSize++;
        }
        
        // If a cycle is of size `cycleSize`, it requires `cycleSize - 1` swaps
        if (cycleSize > 1) {
            swaps += (cycleSize - 1);
        }
    }
    
    return swaps;
};

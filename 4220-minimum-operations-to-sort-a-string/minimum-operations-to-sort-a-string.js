/**
 * @param {string} s
 * @return {number}
 */
var minOperations = function(s) {
    let n = s.length;

    // 1. Check if already sorted
    let isSorted = true;
    for (let i = 1; i < n; i++) {
        if (s[i] < s[i - 1]) {
            isSorted = false;
            break;
        }
    }
    if (isSorted) return 0;

    // 2. Not sorted and length <= 2 is impossible
    if (n <= 2) return -1;

    // Get the sorted version to know the exact global min and max characters
    let sortedArr = s.split('').sort();
    let globalMin = sortedArr[0];
    let globalMax = sortedArr[n - 1];

    // 3. 1 Operation: If the boundary is already in the correct spot
    if (s[0] === globalMin || s[n - 1] === globalMax) {
        return 1;
    }

    // 4. 2 Operations: If min is accessible in the prefix OR max is accessible in the suffix
    let minInPrefix = false;
    for (let i = 0; i < n - 1; i++) {
        if (s[i] === globalMin) {
            minInPrefix = true;
            break;
        }
    }

    let maxInSuffix = false;
    for (let i = 1; i < n; i++) {
        if (s[i] === globalMax) {
            maxInSuffix = true;
            break;
        }
    }

    if (minInPrefix || maxInSuffix) {
        return 2;
    }

    // 5. 3 Operations: Worst case scenario (e.g., "edc")
    return 3;
};

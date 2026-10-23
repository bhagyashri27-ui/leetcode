/**
 * @param {number[]} nums
 * @return {number}
 */
var sortPermutation = function(nums) {
    let isSorted = true;
    let k = -1; // Initialize with all bits set (equivalent to 0xFFFFFFFF)

    for (let i = 0; i < nums.length; i++) {
        if (nums[i] !== i) {
            isSorted = false;
            k &= nums[i];
        }
    }

    // If the array is already sorted, return 0. Otherwise, return the computed k.
    return isSorted ? 0 : k;
};

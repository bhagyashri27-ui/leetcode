/**
 * @param {string} s
 * @return {number}
 */
var maxDepth = function(s) {
    let currentDepth = 0;
    let maxDepthValue = 0;

    // Scan each character in the string
    for (let i = 0; i < s.length; i++) {
        if (s[i] === '(') {
            currentDepth++;
            // Update the maximum depth seen so far
            if (currentDepth > maxDepthValue) {
                maxDepthValue = currentDepth;
            }
        } else if (s[i] === ')') {
            currentDepth--;
        }
    }

    return maxDepthValue;
};

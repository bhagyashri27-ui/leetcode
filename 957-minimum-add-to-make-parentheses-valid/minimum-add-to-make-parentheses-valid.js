/**
 * @param {string} s
 * @return {number}
 */
var minAddToMakeValid = function(s) {
    let leftCount = 0;  // Unmatched '(' needing a ')'
    let ans = 0;        // Unmatched ')' needing a '('

    for (let i = 0; i < s.length; i++) {
        if (s[i] === '(') {
            leftCount++;
        } else {
            if (leftCount > 0) {
                leftCount--; // Match with an existing '('
            } else {
                ans++;       // Unmatched ')' found
            }
        }
    }

    return ans + leftCount; // Unmatched right brackets + unmatched left brackets
};

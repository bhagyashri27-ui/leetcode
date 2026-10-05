/**
 * @param {string} s
 * @return {number}
 */
var scoreOfParentheses = function(s) {
    let score = 0;
    let depth = 0;
    
    for (let i = 0; i < s.length; i++) {
        if (s[i] === '(') {
            depth++;
        } else {
            depth--;
            // If the previous character was '(', we found a core "()"
            if (s[i - 1] === '(') {
                score += 1 << depth; // 1 << depth is equivalent to 2^depth
            }
        }
    }
    
    return score;
};

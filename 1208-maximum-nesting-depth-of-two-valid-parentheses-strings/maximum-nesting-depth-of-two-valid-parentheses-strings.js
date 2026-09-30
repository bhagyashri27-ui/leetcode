/**
 * @param {string} seq
 * @return {number[]}
 */
var maxDepthAfterSplit = function(seq) {
    let ans = new Array(seq.length);
    let depth = 0;
    
    for (let i = 0; i < seq.length; i++) {
        if (seq[i] === '(') {
            // Increase depth for the incoming '('
            depth++;
            // Assign based on whether the current depth is even (0) or odd (1)
            ans[i] = depth % 2;
        } else {
            // Assign based on the current depth BEFORE decreasing it
            ans[i] = depth % 2;
            // Decrease depth as the '(' is now closed
            depth--;
        }
    }
    
    return ans;
};

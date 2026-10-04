/**
 * @param {string} s
 * @return {boolean}
 */
var checkValidString = function(s) {
    let minOpen = 0;
    let maxOpen = 0;

    for (let i = 0; i < s.length; i++) {
        const char = s[i];

        if (char === '(') {
            minOpen++;
            maxOpen++;
        } else if (char === ')') {
            minOpen--;
            maxOpen--;
        } else { // char === '*'
            minOpen--; // If we treat '*' as ')'
            maxOpen++; // If we treat '*' as '('
        }

        // More ')' than possible '(' and '*' combined
        if (maxOpen < 0) return false;

        // minOpen cannot be negative because we can't have "negative" open brackets.
        // It just means we shouldn't utilize '*' as ')' if it makes it invalid.
        if (minOpen < 0) minOpen = 0;
    }

    // If minOpen is 0, we can successfully balance all parentheses
    return minOpen === 0;
};

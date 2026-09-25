/**
 * @param {string} expression
 * @return {string[]}
 */
var braceExpansionII = function(expression) {
    let i = 0;

    // Parses a comma-separated list of terms (Union operation)
    function parseExpr() {
        let res = new Set();
        while (i < expression.length) {
            let term = parseTerm();
            for (let word of term) {
                res.add(word);
            }
            if (i < expression.length && expression[i] === ',') {
                i++; // Skip the ','
            } else {
                break;
            }
        }
        return res;
    }

    // Parses adjacent factors (Concatenation / Cartesian Product operation)
    function parseTerm() {
        let res = new Set([""]);
        while (i < expression.length && (expression[i] === '{' || (expression[i] >= 'a' && expression[i] <= 'z'))) {
            let nextFactor = parseFactor();
            let nextRes = new Set();
            for (let w1 of res) {
                for (let w2 of nextFactor) {
                    nextRes.add(w1 + w2);
                }
            }
            res = nextRes;
        }
        return res;
    }

    // Parses a single unit (either a letter or a nested braced expression)
    function parseFactor() {
        if (expression[i] === '{') {
            i++; // Skip '{'
            let res = parseExpr();
            i++; // Skip '}'
            return res;
        } else {
            let res = new Set([expression[i]]);
            i++; // Skip the letter
            return res;
        }
    }

    // Evaluate the expression and return sorted unique words
    let finalSet = parseExpr();
    return Array.from(finalSet).sort();
};

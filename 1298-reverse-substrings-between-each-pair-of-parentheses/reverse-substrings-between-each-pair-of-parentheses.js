/**
 * @param {string} s
 * @return {string}
 */
var reverseParentheses = function(s) {
    let stack = [];
    
    for (let char of s) {
        if (char === ')') {
            let queue = [];
            // Pop characters until we find the matching opening parenthesis
            while (stack.length > 0 && stack[stack.length - 1] !== '(') {
                queue.push(stack.pop());
            }
            // Pop the opening parenthesis '(' off the stack
            stack.pop(); 
            
            // Push the reversed characters back onto the stack
            for (let qChar of queue) {
                stack.push(qChar);
            }
        } else {
            // Push characters and opening parentheses onto the stack
            stack.push(char);
        }
    }
    
    // Join the remaining characters in the stack to form the final result
    return stack.join('');
};

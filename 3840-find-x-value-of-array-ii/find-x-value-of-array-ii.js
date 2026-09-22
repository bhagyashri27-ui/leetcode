/**
 * @param {number[]} nums
 * @param {number} k
 * @param {number[][]} queries
 * @return {number[]}
 */
var resultArray = function(nums, k, queries) {
    const n = nums.length;
    
    // Flattened segment tree arrays for optimization
    // Size 4 * n is sufficient for a complete binary tree mapping
    const treeProd = new Int32Array(4 * n * k);
    const treeCnt = new Int32Array(4 * n * k * k);

    // Merge helper to combine left and right child results into node
    function merge(node, left, right) {
        const nodeProdOffset = node * k;
        const leftProdOffset = left * k;
        const rightProdOffset = right * k;

        const nodeCntOffset = node * k * k;
        const leftCntOffset = left * k * k;
        const rightCntOffset = right * k * k;

        for (let rIn = 0; rIn < k; rIn++) {
            const midProd = treeProd[leftProdOffset + rIn];
            treeProd[nodeProdOffset + rIn] = treeProd[rightProdOffset + midProd];
            
            const nRowOffset = nodeCntOffset + rIn * k;
            const lRowOffset = leftCntOffset + rIn * k;
            const rRowOffset = rightCntOffset + midProd * k;

            for (let rOut = 0; rOut < k; rOut++) {
                treeCnt[nRowOffset + rOut] = treeCnt[lRowOffset + rOut] + treeCnt[rRowOffset + rOut];
            }
        }
    }

    // Build the initial segment tree
    function build(node, start, end) {
        if (start === end) {
            const v = nums[start] % k;
            const prodOffset = node * k;
            const cntOffset = node * k * k;
            for (let rIn = 0; rIn < k; rIn++) {
                const rOut = (rIn * v) % k;
                treeProd[prodOffset + rIn] = rOut;
                treeCnt[cntOffset + rIn * k + rOut] = 1;
            }
            return;
        }
        const mid = Math.floor((start + end) / 2);
        const left = 2 * node;
        const right = 2 * node + 1;
        build(left, start, mid);
        build(right, mid + 1, end);
        merge(node, left, right);
    }

    // Process segment tree point updates
    function update(node, start, end, idx, val) {
        if (start === end) {
            const v = val % k;
            const prodOffset = node * k;
            const cntOffset = node * k * k;
            // Clear prior counts
            treeCnt.fill(0, cntOffset, cntOffset + k * k);
            for (let rIn = 0; rIn < k; rIn++) {
                const rOut = (rIn * v) % k;
                treeProd[prodOffset + rIn] = rOut;
                treeCnt[cntOffset + rIn * k + rOut] = 1;
            }
            return;
        }
        const mid = Math.floor((start + end) / 2);
        const left = 2 * node;
        const right = 2 * node + 1;
        if (idx <= mid) {
            update(left, start, mid, idx, val);
        } else {
            update(right, mid + 1, end, idx, val);
        }
        merge(node, left, right);
    }

    // Query range tracking structures to avoid allocation overhead during recursive query
    const resProd = new Int32Array(k);
    const resCnt = new Int32Array(k * k);
    
    const tempProd = new Int32Array(k);
    const tempCnt = new Int32Array(k * k);

    function query(node, start, end, l, r) {
        if (l <= start && end <= r) {
            const prodOffset = node * k;
            const cntOffset = node * k * k;
            for (let i = 0; i < k; i++) resProd[i] = treeProd[prodOffset + i];
            for (let i = 0; i < k * k; i++) resCnt[i] = treeCnt[cntOffset + i];
            return;
        }
        
        const mid = Math.floor((start + end) / 2);
        const left = 2 * node;
        const right = 2 * node + 1;

        if (r <= mid) {
            query(left, start, mid, l, r);
            return;
        }
        if (l > mid) {
            query(right, mid + 1, end, l, r);
            return;
        }

        // Segment straddles both children
        query(left, start, mid, l, mid);
        for (let i = 0; i < k; i++) tempProd[i] = resProd[i];
        for (let i = 0; i < k * k; i++) tempCnt[i] = resCnt[i];

        query(right, mid + 1, end, mid + 1, r);

        // Merge left child (stored in temp) with right child (stored in res)
        const finalProd = new Int32Array(k);
        const finalCnt = new Int32Array(k * k);

        for (let rIn = 0; rIn < k; rIn++) {
            const midProd = tempProd[rIn];
            finalProd[rIn] = resProd[midProd];
            
            const fRow = rIn * k;
            const tRow = rIn * k;
            const rRow = midProd * k;

            for (let rOut = 0; rOut < k; rOut++) {
                finalCnt[fRow + rOut] = tempCnt[tRow + rOut] + resCnt[rRow + rOut];
            }
        }
        
        for (let i = 0; i < k; i++) resProd[i] = finalProd[i];
        for (let i = 0; i < k * k; i++) resCnt[i] = finalCnt[i];
    }

    // Build the tree initial state
    build(1, 0, n - 1);
    
    const result = [];
    const baseIn = 1 % k; // Correctly sets index 0 if k=1, or index 1 if k>1
    
    for (let i = 0; i < queries.length; i++) {
        const [idx, val, start, x] = queries[i];
        
        // Step 1: Update nums array persistently 
        update(1, 0, n - 1, idx, val);
        
        // Step 2: Query active target range [start, n - 1]
        query(1, 0, n - 1, start, n - 1);
        
        // Collect matches for remainder x given our starting base product of 1
        result.push(resCnt[baseIn * k + x]);
    }
    
    return result;
};

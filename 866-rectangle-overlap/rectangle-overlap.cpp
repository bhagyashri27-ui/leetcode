class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // min(right1, right2) > max(left1, left2) && min(top1, top2) > max(bottom1, bottom2)
        return min(rec1[2], rec2[2]) > max(rec1[0], rec2[0]) && 
               min(rec1[3], rec2[3]) > max(rec1[1], rec2[1]);
    }
};
class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // Find the closest point on/in the rectangle to the circle's center
        int closestX = std::max(x1, std::min(xCenter, x2));
        int closestY = std::max(y1, std::min(yCenter, y2));
        
        // Calculate squared distance from circle center to closest point
        int dx = xCenter - closestX;
        int dy = yCenter - closestY;
        
        return (dx * dx + dy * dy) <= (radius * radius);
    }
};
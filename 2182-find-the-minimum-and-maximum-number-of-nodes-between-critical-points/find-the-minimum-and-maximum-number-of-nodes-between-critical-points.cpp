class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // A linked list must have at least 3 nodes to have a critical point
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        int firstCrit = -1;
        int lastCrit = -1;
        int minDistance = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;
        int currentIndex = 1;

        while (curr->next != nullptr) {
            ListNode* nextNode = curr->next;

            // Check for local maxima or local minima
            if ((curr->val > prev->val && curr->val > nextNode->val) ||
                (curr->val < prev->val && curr->val < nextNode->val)) {
                
                if (firstCrit == -1) {
                    // First critical point found
                    firstCrit = currentIndex;
                } else {
                    // Subsequent critical point: update minDistance
                    minDistance = min(minDistance, currentIndex - lastCrit);
                }
                // Always update the last seen critical point
                lastCrit = currentIndex;
            }

            // Move pointers forward
            prev = curr;
            curr = nextNode;
            currentIndex++;
        }

        // If less than two critical points were found
        if (minDistance == INT_MAX) {
            return {-1, -1};
        }

        // Max distance is the difference between the last and first critical points
        int maxDistance = lastCrit - firstCrit;

        return {minDistance, maxDistance};
    }
};
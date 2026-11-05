class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        // Sort arr2 to enable binary search
        sort(arr2.begin(), arr2.end());
        int distanceValue = 0;

        for (int x : arr1) {
            // Find the first element in arr2 that is >= x
            auto it = lower_bound(arr2.begin(), arr2.end(), x);
            bool isValid = true;

            // Check the element greater than or equal to x
            if (it != arr2.end() && abs(*it - x) <= d) {
                isValid = false;
            }
            // Check the element smaller than x
            if (isValid && it != arr2.begin() && abs(*(it - 1) - x) <= d) {
                isValid = false;
            }

            if (isValid) {
                distanceValue++;
            }
        }

        return distanceValue;
    }
};
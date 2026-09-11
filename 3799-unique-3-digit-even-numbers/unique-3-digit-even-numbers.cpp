class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> count(10, 0);
        for (int d : digits) {
            count[d]++;
        }

        int total = 0;
        for (int num = 100; num < 1000; num += 2) {
            int d1 = num / 100;       // Hundreds digit
            int d2 = (num / 10) % 10;  // Tens digit
            int d3 = num % 10;        // Units digit

            vector<int> req(10, 0);
            req[d1]++;
            req[d2]++;
            req[d3]++;

            bool possible = true;
            for (int i = 0; i < 10; ++i) {
                if (req[i] > count[i]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                total++;
            }
        }

        return total;
    }
};
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int startR = -1, startC = -1;
        vector<pair<int, int>> litters;
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (classroom[r][c] == 'S') {
                    startR = r;
                    startC = c;
                } else if (classroom[r][c] == 'L') {
                    litters.push_back({r, c});
                }
            }
        }
        
        int numLitters = litters.size();
        int fullMask = (1 << numLitters) - 1;
        if (fullMask == 0) return 0; // No litter to collect
        
        // Map litter positions to bit indices
        auto getLitterIndex = [&](int r, int c) {
            for (int i = 0; i < numLitters; ++i) {
                if (litters[i].first == r && litters[i].second == c) return i;
            }
            return -1;
        };

        // Queue stores: {r, c, mask, currEnergy, steps}
        queue<tuple<int, int, int, int, int>> q;
        
        // bestEnergy[r][c][mask] keeps track of max energy seen at state
        vector<vector<vector<int>>> bestEnergy(m, vector<vector<int>>(n, vector<int>(1 << numLitters, -1)));
        
        q.push({startR, startC, 0, energy, 0});
        bestEnergy[startR][startC][0] = energy;
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [r, c, mask, e, steps] = q.front();
            q.pop();
            
            if (mask == fullMask) {
                return steps;
            }
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                    int nextEnergy = e - 1;
                    if (nextEnergy < 0) continue; // Out of energy
                    
                    int nextMask = mask;
                    char cell = classroom[nr][nc];
                    
                    if (cell == 'L') {
                        int idx = getLitterIndex(nr, nc);
                        if (idx != -1) {
                            nextMask |= (1 << idx);
                        }
                    } else if (cell == 'R') {
                        nextEnergy = energy; // Reset energy to max
                    }
                    
                    if (nextEnergy > bestEnergy[nr][nc][nextMask]) {
                        bestEnergy[nr][nc][nextMask] = nextEnergy;
                        q.push({nr, nc, nextMask, nextEnergy, steps + 1});
                    }
                }
            }
        }
        
        return -1;
    }
};
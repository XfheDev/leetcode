#include <vector>
#include <queue>
#include <cmath>
#include <limits>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> inMST(n, false);       // track points already in MST
        vector<int> minDist(n, INT_MAX);    // min distance to MST
        minDist[0] = 0;                     // start from point 0
        int result = 0;

        for (int i = 0; i < n; ++i) {
            int u = -1;
            // find the point with the smallest distance not in MST
            for (int j = 0; j < n; ++j) {
                if (!inMST[j] && (u == -1 || minDist[j] < minDist[u])) {
                    u = j;
                }
            }

            inMST[u] = true;
            result += minDist[u];

            // update distances for remaining points
            for (int v = 0; v < n; ++v) {
                if (!inMST[v]) {
                    int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    if (dist < minDist[v]) {
                        minDist[v] = dist;
                    }
                }
            }
        }

        return result;
    }
};

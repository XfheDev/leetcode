#include <vector>
#include <queue>
#include <tuple>
using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(), n = heightMap[0].size();
        if (m < 3 || n < 3) return 0; // havuz olamaz

        // Min-heap: (yükseklik, i, j)
        using T = tuple<int,int,int>;
        priority_queue<T, vector<T>, greater<T>> pq;

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Kenarları heap'e ekle
        for (int i = 0; i < m; i++) {
            pq.emplace(heightMap[i][0], i, 0);
            pq.emplace(heightMap[i][n-1], i, n-1);
            visited[i][0] = visited[i][n-1] = true;
        }
        for (int j = 1; j < n-1; j++) {
            pq.emplace(heightMap[0][j], 0, j);
            pq.emplace(heightMap[m-1][j], m-1, j);
            visited[0][j] = visited[m-1][j] = true;
        }

        int water = 0, maxHeight = 0;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

        while (!pq.empty()) {
            auto [h, i, j] = pq.top(); pq.pop();
            maxHeight = max(maxHeight, h);

            for (auto& d : dirs) {
                int ni = i + d[0], nj = j + d[1];
                if (ni < 0 || nj < 0 || ni >= m || nj >= n || visited[ni][nj]) continue;
                visited[ni][nj] = true;

                int nh = heightMap[ni][nj];
                if (nh < maxHeight) {
                    water += maxHeight - nh;
                }
                pq.emplace(nh, ni, nj);
            }
        }

        return water;
    }
};

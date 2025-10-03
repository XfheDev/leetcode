#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if (m == 0) return 0;
        int n = heightMap[0].size();
        if (n == 0) return 0;

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        using Cell = pair<int, pair<int,int>>; 
        priority_queue<Cell, vector<Cell>, greater<Cell>> pq;

        // Kenar hücrelerini ekle
        for (int i = 0; i < m; i++) {
            pq.push({heightMap[i][0], {i,0}});
            pq.push({heightMap[i][n-1], {i,n-1}});
            visited[i][0] = true;
            visited[i][n-1] = true;
        }
        for (int j = 0; j < n; j++) {
            pq.push({heightMap[0][j], {0,j}});
            pq.push({heightMap[m-1][j], {m-1,j}});
            visited[0][j] = true;
            visited[m-1][j] = true;
        }

        int water = 0;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

        while (!pq.empty()) {
            auto cell = pq.top(); pq.pop();
            int height = cell.first;
            int x = cell.second.first;
            int y = cell.second.second;

            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];

                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    // Daha düşükse su tutulur
                    if (height > heightMap[nx][ny]) {
                        water += height - heightMap[nx][ny];
                    }
                    // Yükseklik güncellenir
                    pq.push({max(height, heightMap[nx][ny]), {nx, ny}});
                }
            }
        }
        return water;
    }
};


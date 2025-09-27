#include <vector>
#include <cmath>
#include <limits>
using namespace std;

class Solution {
public:
    double largestTriangleArea(const vector<vector<int>>& points) {
        const int n = points.size();
        double maxArea = 0.0;

        // Direct reference to avoid repeated indexing overhead
        for (int i = 0; i < n; ++i) {
            const int xi = points[i][0], yi = points[i][1];
            for (int j = i + 1; j < n; ++j) {
                const int xj = points[j][0], yj = points[j][1];
                for (int k = j + 1; k < n; ++k) {
                    const int xk = points[k][0], yk = points[k][1];

                    // Compute area using determinant method
                    const double area = 0.5 * fabs(
                        (double)xi * (yj - yk) +
                        (double)xj * (yk - yi) +
                        (double)xk * (yi - yj)
                    );

                    // Branch-minimized max update
                    if (area > maxArea) maxArea = area;
                }
            }
        }
        return maxArea;
    }
};

class Solution {
public:
    int maxArea(vector<int>& height) { // vector reference kullan
        int l = 0, r = (int)height.size() - 1;
        int area = 0;

        while (l < r) {
            int h = height[l] < height[r] ? height[l] : height[r];
            int w = r - l;
            area = area > h * w ? area : h * w;

            // kısa kenar ilerle
            if (height[l] < height[r]) ++l;
            else --r;
        }

        return area;
    }
};

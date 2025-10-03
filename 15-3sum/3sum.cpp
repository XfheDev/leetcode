#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        if (n < 3) return res;

        sort(nums.begin(), nums.end());
        res.reserve(n); // sonuç için ön bellek ayır

        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // tekrarları atla

            int left = i + 1, right = n - 1;
            while (left < right) {
                long sum = (long)nums[i] + nums[left] + nums[right];
                if (sum < 0) {
                    left++;
                } else if (sum > 0) {
                    right--;
                } else {
                    res.push_back({nums[i], nums[left], nums[right]});
                    int lastLeft = nums[left], lastRight = nums[right];
                    while (left < right && nums[left] == lastLeft) left++;
                    while (left < right && nums[right] == lastRight) right--;
                }
            }
        }
        return res;
    }
};


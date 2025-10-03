#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int closest = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n - 2; i++) {
            // Erken durdurma 1: en küçük üçlü bile target'tan büyükse
            int minSum = nums[i] + nums[i+1] + nums[i+2];
            if (minSum > target) {
                if (minSum - target < abs(closest - target)) closest = minSum;
                break; // daha iyisi mümkün değil
            }

            // Erken durdurma 2: en büyük üçlü bile target'tan küçükse
            int maxSum = nums[i] + nums[n-2] + nums[n-1];
            if (maxSum < target) {
                if (target - maxSum < abs(closest - target)) closest = maxSum;
                continue;
            }

            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == target) return target; // mükemmel eşleşme → bitir

                // abs yerine inline fark
                int diff = sum - target;
                if (diff < 0) diff = -diff;
                int bestDiff = closest - target;
                if (bestDiff < 0) bestDiff = -bestDiff;
                if (diff < bestDiff) closest = sum;

                if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return closest;
    }
};


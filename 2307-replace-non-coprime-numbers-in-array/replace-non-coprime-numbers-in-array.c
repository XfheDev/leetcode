static inline long long gcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    int top = 0;
    
    for (int i = 0; i < numsSize; i++) {
        long long cur = nums[i];
        
        while (top) {
            long long g = gcd(nums[top - 1], cur);
            if (g == 1) break;
            cur = nums[--top] / g * cur;
        }
        
        nums[top++] = cur;
    }
    
    *returnSize = top;
    return nums;
}
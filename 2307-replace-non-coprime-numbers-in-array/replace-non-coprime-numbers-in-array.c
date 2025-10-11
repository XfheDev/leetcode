static inline long long gcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    long long* stack = (long long*)malloc(numsSize * sizeof(long long));
    int top = 0;
    
    for (int i = 0; i < numsSize; i++) {
        long long cur = nums[i];
        
        while (top) {
            long long g = gcd(stack[top - 1], cur);
            if (g == 1) break;
            cur = stack[--top] / g * cur;
        }
        
        stack[top++] = cur;
    }
    
    int* result = (int*)malloc(top * sizeof(int));
    for (int i = 0; i < top; i++) {
        result[i] = stack[i];
    }
    free(stack);
    
    *returnSize = top;
    return result;
}
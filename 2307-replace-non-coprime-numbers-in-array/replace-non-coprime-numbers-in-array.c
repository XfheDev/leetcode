long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    int* stack = (int*)malloc(numsSize * sizeof(int));
    int top = 0;
    
    for (int i = 0; i < numsSize; i++) {
        long long cur = nums[i];
        
        while (top > 0 && gcd(stack[top - 1], cur) > 1) {
            cur = lcm(stack[top - 1], cur);
            top--;
        }
        
        stack[top++] = cur;
    }
    
    *returnSize = top;
    return stack;
}
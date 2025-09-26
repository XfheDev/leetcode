class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        const int INT_MAX_DIV10 = INT_MAX / 10;
        const int INT_MIN_DIV10 = INT_MIN / 10;

        while (x) {
            int pop = x % 10;
            x /= 10;

            // Branchless-ish overflow check
            if (rev > INT_MAX_DIV10 || (rev == INT_MAX_DIV10 && pop > 7) ||
                rev < INT_MIN_DIV10 || (rev == INT_MIN_DIV10 && pop < -8))
                return 0;

            rev = rev * 10 + pop;
        }

        return rev;
    }
};

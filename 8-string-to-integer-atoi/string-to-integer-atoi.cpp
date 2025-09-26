class Solution {
public:
    int myAtoi(string s) {
        int n = s.size();
        int i = 0;

        // 1. skip leading whitespace
        while (i < n && s[i] == ' ') i++;

        // 2. sign
        int sign = 1;
        if (i < n) {
            if (s[i] == '-') { sign = -1; i++; }
            else if (s[i] == '+') { i++; }
        }

        int res = 0;
        const int INT_MAX_DIV10 = INT_MAX / 10;

        // 3. parse digits
        while (i < n && isdigit(s[i])) {
            int digit = s[i] - '0';

            // 4. overflow check
            if (res > INT_MAX_DIV10 || (res == INT_MAX_DIV10 && digit > 7)) {
                return sign == 1 ? INT_MAX : INT_MIN;
            }

            res = res * 10 + digit;
            i++;
        }

        return res * sign;
    }
};

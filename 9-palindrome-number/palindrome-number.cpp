class Solution {
public:
    bool isPalindrome(int x) {
        // negatif sayı palindrome olmaz
        if (x < 0) return false;

        // tek basamak palindrome
        if (x < 10) return true;

        string s = to_string(x); // string dönüşü
        int n = s.size();
        for (int i = 0; i < n / 2; ++i) {
            if (s[i] != s[n - 1 - i]) return false;
        }
        return true;
    }
};

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int start = 0, maxLen = 1;

        auto expand = [&](int left, int right) {
            while (left >= 0 && right < s.size() && s[left] == s[right]) {
                left--; right++;
            }
            return right - left - 1; // palindrom uzunluğu
        };

        for (int i = 0; i < s.size(); i++) {
            int len1 = expand(i, i);     // tek uzunluk
            int len2 = expand(i, i + 1); // çift uzunluk
            int len = max(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }
        return s.substr(start, maxLen);
    }
};

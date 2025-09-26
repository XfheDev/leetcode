class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> lastIndex(256, -1); // ASCII için
        int maxLen = 0, left = 0;

        for (int right = 0; right < s.size(); right++) {
            if (lastIndex[s[right]] >= left) {
                left = lastIndex[s[right]] + 1; // pencereyi sağa kaydır
            }
            lastIndex[s[right]] = right; 
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<bool> dp(n+1, false);
        dp[0] = true; // boş string boş pattern ile eşleşir

        // İlk satır (i=0) için '*' ile eşleşmeleri ayarla
        for (int j = 2; j <= n; j += 2) {
            if (p[j-1] == '*') dp[j] = dp[j-2];
        }

        for (int i = 1; i <= m; ++i) {
            vector<bool> new_dp(n+1, false);
            for (int j = 1; j <= n; ++j) {
                if (p[j-1] == s[i-1] || p[j-1] == '.') {
                    new_dp[j] = dp[j-1];
                } else if (p[j-1] == '*') {
                    new_dp[j] = new_dp[j-2]; // 0 kez
                    if (p[j-2] == s[i-1] || p[j-2] == '.')
                        new_dp[j] = new_dp[j] || dp[j]; // 1+ kez
                }
            }
            dp.swap(new_dp); // rolling
        }

        return dp[n];
    }
};

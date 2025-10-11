#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int, long long> freq;
        for (int p : power) freq[p]++;

        vector<long long> vals;
        vals.reserve(freq.size());
        for (auto& [v, _] : freq) vals.push_back(v);
        sort(vals.begin(), vals.end());

        int n = vals.size();
        vector<long long> dp(n, 0);

        dp[0] = vals[0] * freq[vals[0]];
        for (int i = 1; i < n; ++i) {
            long long gain = vals[i] * freq[vals[i]];
            int j = i - 1;
            while (j >= 0 && vals[i] - vals[j] <= 2) j--;
            long long include = gain + (j >= 0 ? dp[j] : 0);
            long long exclude = dp[i - 1];
            dp[i] = max(include, exclude);
        }

        return dp.back();
    }
};

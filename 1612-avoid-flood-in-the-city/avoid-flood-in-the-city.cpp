#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n, 1);
        map<int,int> full;
        vector<int> dryDays;

        for(int i = 0; i < n; i++) {
            int lake = rains[i];
            if(lake == 0) {
                dryDays.push_back(i);
                continue;
            }
            ans[i] = -1;
            if(full.count(lake)) {
                auto it = upper_bound(dryDays.begin(), dryDays.end(), full[lake]);
                if(it == dryDays.end()) return {};
                ans[*it] = lake;
                dryDays.erase(it);
            }
            full[lake] = i;
        }
        return ans;
    }
};

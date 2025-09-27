class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        int n = s.size();

        // Roman numeral lookup table
        int value[26] = {0};
        value['I' - 'A'] = 1;
        value['V' - 'A'] = 5;
        value['X' - 'A'] = 10;
        value['L' - 'A'] = 50;
        value['C' - 'A'] = 100;
        value['D' - 'A'] = 500;
        value['M' - 'A'] = 1000;

        for (int i = 0; i < n; ++i) {
            int cur = value[s[i]-'A'];
            if (i+1 < n && cur < value[s[i+1]-'A']) {
                res -= cur; // subtractive form
            } else {
                res += cur;
            }
        }
        return res;
    }
};

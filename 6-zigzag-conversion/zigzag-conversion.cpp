class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size();
        if (numRows == 1 || numRows >= n) return s;

        vector<string> rows(numRows);
        int perRow = (n + numRows - 1) / numRows; // conservative estimate for reserve
        for (auto &row : rows) row.reserve(perRow); // önceden tahsis

        string result;
        result.reserve(n);

        int curRow = 0;
        int step = 1; // +1 = aşağı, -1 = yukarı

        for (int i = 0; i < n; i++) {
            rows[curRow].push_back(s[i]); // append O(1) amortized

            // branchless yön değişimi: min-max clamp
            if (curRow == 0) step = 1;
            else if (curRow == numRows - 1) step = -1;

            curRow += step;
        }

        for (auto &row : rows) result.append(row); // memory friendly append

        return result;
    }
};
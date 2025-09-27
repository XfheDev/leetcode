class Solution {
public:
    bool isPalindrome(int x) {
        // Negatif sayılar ve 0 hariç sonu 0 ile biten sayılar palindrome olamaz
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;

        int reverted = 0;
        // Döngü sadece sayının yarısı kadar devam eder
        while (x > reverted) {
            reverted = reverted * 10 + x % 10;
            x /= 10;
        }

        // Branch-minimized comparison
        return x == reverted || x == reverted / 10;
    }
};

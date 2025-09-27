class Solution {
public:
    bool isPalindrome(int x) {
        // Negatifler ve 0 hariç sonu 0 olan sayılar palindrome olamaz
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;

        int reverted = 0;
        while (x > reverted) {
            reverted = reverted * 10 + x % 10;
            x /= 10;
        }

        // Tek veya çift basamaklı kontrol
        return x == reverted || x == reverted / 10;
    }
};

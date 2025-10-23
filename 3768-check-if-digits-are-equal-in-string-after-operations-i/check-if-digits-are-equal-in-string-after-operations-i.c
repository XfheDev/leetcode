#include <stdbool.h>
#include <string.h>

bool hasSameDigits(char* s) {
    int n = strlen(s);
    int digits[100];

    // string → sayı dizisine dönüştür
    for (int i = 0; i < n; ++i)
        digits[i] = s[i] - '0';

    // işlemleri aynı dizi üzerinde yap
    while (n > 2) {
        for (int i = 0; i < n - 1; ++i)
            digits[i] = (digits[i] + digits[i + 1]) % 10;
        n--;
    }

    // son iki eleman eşit mi?
    return digits[0] == digits[1];
}

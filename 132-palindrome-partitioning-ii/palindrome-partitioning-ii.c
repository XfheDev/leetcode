#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minCut(char * s) {
    int n = strlen(s);
    if (n <= 1) return 0;

    // 1. Palindrom tablosunu oluştur
    // isPal[i][j], s[i...j] palindrom ise true olur
    int **isPal = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        isPal[i] = (int *)calloc(n, sizeof(int));
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (len == 1) {
                isPal[i][j] = 1;
            } else if (len == 2) {
                isPal[i][j] = (s[i] == s[j]);
            } else {
                isPal[i][j] = (s[i] == s[j] && isPal[i + 1][j - 1]);
            }
        }
    }

    // 2. DP tablosunu oluştur
    int *dp = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        if (isPal[0][i]) {
            dp[i] = 0;
        } else {
            dp[i] = i; // Maksimum kesim sayısı (her karakter arası)
            for (int j = 0; j < i; j++) {
                if (isPal[j + 1][i]) {
                    dp[i] = MIN(dp[i], dp[j] + 1);
                }
            }
        }
    }

    int result = dp[n - 1];

    // Bellek temizliği
    for (int i = 0; i < n; i++) free(isPal[i]);
    free(isPal);
    free(dp);

    return result;
}
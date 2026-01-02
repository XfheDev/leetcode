#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minCut(char * s) {
    int n = strlen(s);
    if (n <= 1) return 0;


    int *dp = (int *)malloc((n + 1) * sizeof(int));
    

    for (int i = 0; i <= n; i++) {
        dp[i] = i - 1;
    }

    for (int center = 0; center < n; center++) {
        // 1. Tek uzunluklu palindromlar (Örn: "aba"daki 'b' merkezi)
        for (int i = 0; center - i >= 0 && center + i < n && s[center - i] == s[center + i]; i++) {
            dp[center + i + 1] = MIN(dp[center + i + 1], dp[center - i] + 1);
        }

        // 2. Çift uzunluklu palindromlar (Örn: "abba"daki 'bb' merkezi)
        for (int i = 1; center - i + 1 >= 0 && center + i < n && s[center - i + 1] == s[center + i]; i++) {
            dp[center + i + 1] = MIN(dp[center + i + 1], dp[center - i + 1] + 1);
        }
    }

    int result = dp[n];
    free(dp);
    return result;
}
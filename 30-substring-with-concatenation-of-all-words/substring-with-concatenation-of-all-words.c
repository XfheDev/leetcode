#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int count;
    int id;
} WordCount;

int compareStrs(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int* findSubstring(char * s, char ** words, int wordsSize, int* returnSize) {
    int sLen = strlen(s);
    int wordLen = strlen(words[0]);
    int totalWordsLen = wordsSize * wordLen;
    *returnSize = 0;
    if (sLen < totalWordsLen) return NULL;

    int *result = (int *)malloc(sizeof(int) * sLen);
    
    // 1. Kelimeleri sırala ve benzersiz olanları frekanslarıyla belirle
    qsort(words, wordsSize, sizeof(char *), compareStrs);
    
    int *targetFreq = (int *)calloc(wordsSize, sizeof(int));
    char **uniqueWords = (char **)malloc(sizeof(char *) * wordsSize);
    int uniqueCount = 0;

    for (int i = 0; i < wordsSize; i++) {
        if (i > 0 && strcmp(words[i], words[i-1]) == 0) {
            targetFreq[uniqueCount - 1]++;
        } else {
            uniqueWords[uniqueCount] = words[i];
            targetFreq[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    // 2. Sliding Window (Kaydıran Pencere)
    for (int i = 0; i < wordLen; i++) {
        int left = i, right = i, foundWords = 0;
        int *currentFreq = (int *)calloc(uniqueCount, sizeof(int));

        while (right + wordLen <= sLen) {
            char temp[wordLen + 1];
            memcpy(temp, s + right, wordLen);
            temp[wordLen] = '\0';
            
            // Kelimeyi Binary Search ile bul
            int foundIdx = -1;
            int low = 0, high = uniqueCount - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                int cmp = strcmp(temp, uniqueWords[mid]);
                if (cmp == 0) { foundIdx = mid; break; }
                if (cmp < 0) high = mid - 1;
                else low = mid + 1;
            }

            if (foundIdx != -1) {
                currentFreq[foundIdx]++;
                foundWords++;
                
                // Eğer kelime sayısı sınırı aşarsa soldan daralt
                while (currentFreq[foundIdx] > targetFreq[foundIdx]) {
                    char leftTemp[wordLen + 1];
                    memcpy(leftTemp, s + left, wordLen);
                    leftTemp[wordLen] = '\0';
                    
                    int leftIdx = -1;
                    int l_low = 0, l_high = uniqueCount - 1;
                    while (l_low <= l_high) {
                        int mid = (l_low + l_high) / 2;
                        int cmp = strcmp(leftTemp, uniqueWords[mid]);
                        if (cmp == 0) { leftIdx = mid; break; }
                        if (cmp < 0) l_high = mid - 1;
                        else l_low = mid + 1;
                    }
                    currentFreq[leftIdx]--;
                    foundWords--;
                    left += wordLen;
                }
                
                if (foundWords == wordsSize) {
                    result[(*returnSize)++] = left;
                }
            } else {
                // Geçersiz kelime: Pencereyi sıfırla
                memset(currentFreq, 0, sizeof(int) * uniqueCount);
                foundWords = 0;
                left = right + wordLen;
            }
            right += wordLen;
        }
        free(currentFreq);
    }

    free(uniqueWords);
    free(targetFreq);
    return result; // umarım olur ya
}
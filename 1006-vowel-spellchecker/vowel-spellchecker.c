#define MAX_LEN 8
#define HASH_SIZE 10007

typedef struct Entry {
    char* word;
    struct Entry* next;
} Entry;

typedef struct Node {
    char* word;
    struct Node* next;
} Node;

static inline unsigned long hash(const char* str) {
    unsigned long h = 5381;
    while (*str) h = ((h << 5) + h) + *str++;
    return h % HASH_SIZE;
}

static inline void toLower(const char* str, char* res) {
    while (*str) {
        *res++ = tolower(*str++);
    }
    *res = '\0';
}

static inline void toVowel(const char* str, char* res) {
    while (*str) {
        char c = tolower(*str++);
        *res++ = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ? '*' : c;
    }
    *res = '\0';
}

static inline Entry* findEntry(Entry* head, const char* pattern) {
    char temp[MAX_LEN];
    while (head) {
        toLower(head->word, temp);
        if (strcmp(temp, pattern) == 0) return head;
        head = head->next;
    }
    return NULL;
}

static inline Entry* findVowelEntry(Entry* head, const char* pattern) {
    char temp[MAX_LEN], temp2[MAX_LEN];
    while (head) {
        toLower(head->word, temp);
        toVowel(temp, temp2);
        if (strcmp(temp2, pattern) == 0) return head;
        head = head->next;
    }
    return NULL;
}

char** spellchecker(char** wordlist, int wordlistSize, char** queries, int queriesSize, int* returnSize) {
    Node** exactMap = (Node**)calloc(HASH_SIZE, sizeof(Node*));
    Entry** lowerMap = (Entry**)calloc(HASH_SIZE, sizeof(Entry*));
    Entry** vowelMap = (Entry**)calloc(HASH_SIZE, sizeof(Entry*));
    
    char buf1[MAX_LEN], buf2[MAX_LEN];
    
    for (int i = 0; i < wordlistSize; i++) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->word = wordlist[i];
        unsigned long h = hash(wordlist[i]);
        node->next = exactMap[h];
        exactMap[h] = node;
        
        toLower(wordlist[i], buf1);
        h = hash(buf1);
        if (!findEntry(lowerMap[h], buf1)) {
            Entry* e = (Entry*)malloc(sizeof(Entry));
            e->word = wordlist[i];
            e->next = lowerMap[h];
            lowerMap[h] = e;
        }
        
        toVowel(buf1, buf2);
        h = hash(buf2);
        if (!findVowelEntry(vowelMap[h], buf2)) {
            Entry* e = (Entry*)malloc(sizeof(Entry));
            e->word = wordlist[i];
            e->next = vowelMap[h];
            vowelMap[h] = e;
        }
    }
    
    char** answer = (char**)malloc(queriesSize * sizeof(char*));
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        answer[i] = (char*)malloc(MAX_LEN);
        answer[i][0] = '\0';
        
        unsigned long h = hash(queries[i]);
        Node* n = exactMap[h];
        while (n) {
            if (strcmp(n->word, queries[i]) == 0) {
                strcpy(answer[i], n->word);
                goto next;
            }
            n = n->next;
        }
        
        toLower(queries[i], buf1);
        h = hash(buf1);
        Entry* e = findEntry(lowerMap[h], buf1);
        if (e) {
            strcpy(answer[i], e->word);
            goto next;
        }
        
        toVowel(buf1, buf2);
        h = hash(buf2);
        e = findVowelEntry(vowelMap[h], buf2);
        if (e) strcpy(answer[i], e->word);
        
        next:;
    }
    
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *n = exactMap[i];
        while (n) {
            Node *t = n;
            n = n->next;
            free(t);
        }
        Entry *e = lowerMap[i];
        while (e) {
            Entry *t = e;
            e = e->next;
            free(t);
        }
        e = vowelMap[i];
        while (e) {
            Entry *t = e;
            e = e->next;
            free(t);
        }
    }
    free(exactMap);
    free(lowerMap);
    free(vowelMap);
    
    return answer;
}
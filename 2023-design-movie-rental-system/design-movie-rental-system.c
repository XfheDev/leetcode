#define MAX_MOVIE 10001
#define HASH_SIZE 300007

typedef struct {
    int shop;
    int movie;
    int price;
    char rented;
} Entry;

typedef struct {
    Entry*** entries;
    int* counts;
    Entry** hashMap;
    Entry* rentedArr;
    int rentedCount;
    int rentedCap;
} MovieRentingSystem;

static inline int cmpEntry(const void* a, const void* b) {
    Entry* ea = *(Entry**)a;
    Entry* eb = *(Entry**)b;
    return (ea->price != eb->price) ? ea->price - eb->price : ea->shop - eb->shop;
}

static inline int cmpRented(const void* a, const void* b) {
    Entry* ea = (Entry*)a;
    Entry* eb = (Entry*)b;
    if (ea->price != eb->price) return ea->price - eb->price;
    if (ea->shop != eb->shop) return ea->shop - eb->shop;
    return ea->movie - eb->movie;
}

static inline int hash(int shop, int movie) {
    return (((unsigned)shop * 10001U + movie) & 0x7FFFFFFF) % HASH_SIZE;
}

MovieRentingSystem* movieRentingSystemCreate(int n, int** entries, int entriesSize, int* entriesColSize) {
    MovieRentingSystem* obj = (MovieRentingSystem*)calloc(1, sizeof(MovieRentingSystem));
    obj->entries = (Entry***)calloc(MAX_MOVIE, sizeof(Entry**));
    obj->counts = (int*)calloc(MAX_MOVIE, sizeof(int));
    obj->hashMap = (Entry**)calloc(HASH_SIZE, sizeof(Entry*));
    obj->rentedCap = 128;
    obj->rentedArr = (Entry*)malloc(obj->rentedCap * sizeof(Entry));
    
    int* sizes = (int*)calloc(MAX_MOVIE, sizeof(int));
    
    for (int i = 0; i < entriesSize; i++) {
        sizes[entries[i][1]]++;
    }
    
    for (int i = 0; i < MAX_MOVIE; i++) {
        if (sizes[i]) {
            obj->entries[i] = (Entry**)malloc(sizes[i] * sizeof(Entry*));
        }
    }
    
    for (int i = 0; i < entriesSize; i++) {
        Entry* e = (Entry*)malloc(sizeof(Entry));
        e->shop = entries[i][0];
        e->movie = entries[i][1];
        e->price = entries[i][2];
        e->rented = 0;
        
        int h = hash(e->shop, e->movie);
        while (obj->hashMap[h]) h = (h + 1) % HASH_SIZE;
        obj->hashMap[h] = e;
        
        obj->entries[e->movie][obj->counts[e->movie]++] = e;
    }
    
    for (int i = 0; i < MAX_MOVIE; i++) {
        if (obj->counts[i] > 1) {
            qsort(obj->entries[i], obj->counts[i], sizeof(Entry*), cmpEntry);
        }
    }
    
    free(sizes);
    return obj;
}

int* movieRentingSystemSearch(MovieRentingSystem* obj, int movie, int* retSize) {
    int* res = (int*)malloc(5 * sizeof(int));
    int cnt = 0;
    Entry** arr = obj->entries[movie];
    int len = obj->counts[movie];
    
    for (int i = 0; i < len && cnt < 5; i++) {
        if (!arr[i]->rented) res[cnt++] = arr[i]->shop;
    }
    
    *retSize = cnt;
    return res;
}

void movieRentingSystemRent(MovieRentingSystem* obj, int shop, int movie) {
    int h = hash(shop, movie);
    Entry* e = obj->hashMap[h];
    while (e->shop != shop || e->movie != movie) {
        h = (h + 1) % HASH_SIZE;
        e = obj->hashMap[h];
    }
    
    e->rented = 1;
    
    if (obj->rentedCount == obj->rentedCap) {
        obj->rentedCap <<= 1;
        obj->rentedArr = (Entry*)realloc(obj->rentedArr, obj->rentedCap * sizeof(Entry));
    }
    
    obj->rentedArr[obj->rentedCount++] = *e;
}

void movieRentingSystemDrop(MovieRentingSystem* obj, int shop, int movie) {
    int h = hash(shop, movie);
    Entry* e = obj->hashMap[h];
    while (e->shop != shop || e->movie != movie) {
        h = (h + 1) % HASH_SIZE;
        e = obj->hashMap[h];
    }
    
    e->rented = 0;
    
    for (int i = obj->rentedCount - 1; i >= 0; i--) {
        if (obj->rentedArr[i].shop == shop && obj->rentedArr[i].movie == movie) {
            obj->rentedArr[i] = obj->rentedArr[--obj->rentedCount];
            return;
        }
    }
}

int** movieRentingSystemReport(MovieRentingSystem* obj, int* retSize, int** retColSize) {
    int sz = obj->rentedCount < 5 ? obj->rentedCount : 5;
    *retSize = sz;
    
    if (!sz) {
        *retColSize = NULL;
        return NULL;
    }
    
    if (sz < obj->rentedCount) {
        Entry temp[5];
        memcpy(temp, obj->rentedArr, 5 * sizeof(Entry));
        
        for (int i = 5; i < obj->rentedCount; i++) {
            int maxIdx = 0;
            for (int j = 1; j < 5; j++) {
                if (cmpRented(&temp[j], &temp[maxIdx]) > 0) maxIdx = j;
            }
            if (cmpRented(&obj->rentedArr[i], &temp[maxIdx]) < 0) {
                temp[maxIdx] = obj->rentedArr[i];
            }
        }
        
        qsort(temp, 5, sizeof(Entry), cmpRented);
        
        int** res = (int**)malloc(5 * sizeof(int*));
        *retColSize = (int*)malloc(5 * sizeof(int));
        for (int i = 0; i < 5; i++) {
            res[i] = (int*)malloc(2 * sizeof(int));
            res[i][0] = temp[i].shop;
            res[i][1] = temp[i].movie;
            (*retColSize)[i] = 2;
        }
        return res;
    }
    
    Entry* temp = (Entry*)malloc(sz * sizeof(Entry));
    memcpy(temp, obj->rentedArr, sz * sizeof(Entry));
    qsort(temp, sz, sizeof(Entry), cmpRented);
    
    int** res = (int**)malloc(sz * sizeof(int*));
    *retColSize = (int*)malloc(sz * sizeof(int));
    for (int i = 0; i < sz; i++) {
        res[i] = (int*)malloc(2 * sizeof(int));
        res[i][0] = temp[i].shop;
        res[i][1] = temp[i].movie;
        (*retColSize)[i] = 2;
    }
    
    free(temp);
    return res;
}

void movieRentingSystemFree(MovieRentingSystem* obj) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (obj->hashMap[i]) free(obj->hashMap[i]);
    }
    for (int i = 0; i < MAX_MOVIE; i++) {
        if (obj->entries[i]) free(obj->entries[i]);
    }
    free(obj->entries);
    free(obj->counts);
    free(obj->hashMap);
    free(obj->rentedArr);
    free(obj);
}
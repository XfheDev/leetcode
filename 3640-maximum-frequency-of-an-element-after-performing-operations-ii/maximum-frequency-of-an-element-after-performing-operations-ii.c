#include <stdlib.h>

typedef long long ll;

int cmp_ll(const void *a, const void *b) {
    ll x = *(const ll*)a, y = *(const ll*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a, y = *(const int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int maxFrequency(int* nums, int numsSize, int k, int numOperations) {
    if (numsSize == 0) return 0;
    int n = numsSize;
    ll *events_pos = (ll*)malloc(sizeof(ll) * (2 * n + n));
    int *events_delta = (int*)malloc(sizeof(int) * (2 * n + n));
    ll *nums_ll = (ll*)malloc(sizeof(ll) * n);
    for (int i = 0; i < n; ++i) nums_ll[i] = (ll)nums[i];


    int ecount = 0;
    for (int i = 0; i < n; ++i) {
        ll L = nums_ll[i] - (ll)k;
        ll R1 = nums_ll[i] + (ll)k + 1; 
        events_pos[ecount] = L; events_delta[ecount] = 1; ecount++;
        events_pos[ecount] = R1; events_delta[ecount] = -1; ecount++;
    }

    for (int i = 0; i < n; ++i) {
        events_pos[ecount] = nums_ll[i];
        events_delta[ecount] = 0;
        ecount++;
    }


    typedef struct { ll p; int d; } Ev;
    Ev *ev = (Ev*)malloc(sizeof(Ev) * ecount);
    for (int i = 0; i < ecount; ++i) { ev[i].p = events_pos[i]; ev[i].d = events_delta[i]; }
    free(events_pos); free(events_delta);

    qsort(ev, ecount, sizeof(Ev), cmp_ll); 

    int ec = ecount;

    free(ev);
    ev = (Ev*)malloc(sizeof(Ev) * ec);

    int idx = 0;
    for (int i = 0; i < n; ++i) {
        ll L = nums_ll[i] - (ll)k;
        ll R1 = nums_ll[i] + (ll)k + 1;
        ev[idx].p = L; ev[idx].d = 1; idx++;
        ev[idx].p = R1; ev[idx].d = -1; idx++;
    }
    for (int i = 0; i < n; ++i) { ev[idx].p = nums_ll[i]; ev[idx].d = 0; idx++; }

    int ev_count = idx;

    int ev_cmp(const void *a, const void *b) {
        const Ev *A = (const Ev*)a;
        const Ev *B = (const Ev*)b;
        if (A->p < B->p) return -1;
        if (A->p > B->p) return 1;

        return 0;
    }
    qsort(ev, ev_count, sizeof(Ev), ev_cmp);


    qsort(nums, n, sizeof(int), cmp_int);
    int uniq_cnt = 0;
    int *uniq_vals = (int*)malloc(sizeof(int) * n);
    int *uniq_freq = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ) {
        int v = nums[i];
        int j = i;
        while (j < n && nums[j] == v) j++;
        uniq_vals[uniq_cnt] = v;
        uniq_freq[uniq_cnt] = j - i;
        uniq_cnt++;
        i = j;
    }


    long long ans = 1;
    long long cover = 0;
    int i = 0;
    while (i < ev_count) {
        ll pos = ev[i].p;

        int j = i;
        while (j < ev_count && ev[j].p == pos) {
            cover += ev[j].d;
            j++;
        }

        int target = (int)pos;
        int l = 0, r = uniq_cnt - 1;
        int freq = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (uniq_vals[mid] == target) { freq = uniq_freq[mid]; break; }
            else if (uniq_vals[mid] < target) l = mid + 1;
            else r = mid - 1;
        }
        long long possible = cover; // number intervals covering pos
        long long canMake = (long long)freq + (long long)numOperations;
        if (canMake < possible) possible = canMake;
        if (possible > ans) ans = possible;

        i = j;
    }

    free(ev);
    free(nums_ll);
    free(uniq_vals);
    free(uniq_freq);
    return (int)ans;
}

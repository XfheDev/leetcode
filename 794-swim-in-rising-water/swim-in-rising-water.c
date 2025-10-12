#include <stdbool.h>

#define MAXN 55

typedef struct {
    int h, x, y;
} Node;

typedef struct {
    Node a[MAXN * MAXN];
    int sz;
} Heap;

static inline void heap_swap(Node *a, Node *b) {
    Node t = *a; *a = *b; *b = t;
}

static inline void heap_push(Heap *h, Node v) {
    int i = ++h->sz;
    h->a[i] = v;
    while (i > 1 && h->a[i].h < h->a[i >> 1].h) {
        heap_swap(&h->a[i], &h->a[i >> 1]);
        i >>= 1;
    }
}

static inline Node heap_pop(Heap *h) {
    Node r = h->a[1];
    h->a[1] = h->a[h->sz--];
    int i = 1;
    while (1) {
        int l = i << 1, rgt = l | 1, s = i;
        if (l <= h->sz && h->a[l].h < h->a[s].h) s = l;
        if (rgt <= h->sz && h->a[rgt].h < h->a[s].h) s = rgt;
        if (s == i) break;
        heap_swap(&h->a[i], &h->a[s]);
        i = s;
    }
    return r;
}

int swimInWater(int** grid, int n, int* gridColSize) {
    bool vis[MAXN][MAXN] = {0};
    Heap pq = { .sz = 0 };
    heap_push(&pq, (Node){grid[0][0], 0, 0});
    vis[0][0] = true;
    int maxH = grid[0][0];

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    while (pq.sz) {
        Node cur = heap_pop(&pq);
        if (cur.h > maxH) maxH = cur.h;
        if (cur.x == n-1 && cur.y == n-1) return maxH;

        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d], ny = cur.y + dy[d];
            if ((unsigned)nx >= (unsigned)n || (unsigned)ny >= (unsigned)n) continue;
            if (vis[nx][ny]) continue;
            vis[nx][ny] = true;
            heap_push(&pq, (Node){grid[nx][ny], nx, ny});
        }
    }
    return maxH;
}

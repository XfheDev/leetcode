
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 55
#define INF 1000000000

typedef struct {
    int h, x, y;
} Node;


int cmp(const void *a, const void *b) {
    return ((Node *)a)->h - ((Node *)b)->h;
}


typedef struct {
    Node heap[MAXN * MAXN + 5];
    int size;
} MinHeap;

void push(MinHeap *pq, Node val) {
    pq->heap[++pq->size] = val;
    int i = pq->size;
    while (i > 1 && pq->heap[i].h < pq->heap[i / 2].h) {
        Node tmp = pq->heap[i];
        pq->heap[i] = pq->heap[i / 2];
        pq->heap[i / 2] = tmp;
        i /= 2;
    }
}

Node pop(MinHeap *pq) {
    Node res = pq->heap[1];
    pq->heap[1] = pq->heap[pq->size--];
    int i = 1;
    while (1) {
        int l = i * 2, r = l + 1, smallest = i;
        if (l <= pq->size && pq->heap[l].h < pq->heap[smallest].h) smallest = l;
        if (r <= pq->size && pq->heap[r].h < pq->heap[smallest].h) smallest = r;
        if (smallest == i) break;
        Node tmp = pq->heap[i];
        pq->heap[i] = pq->heap[smallest];
        pq->heap[smallest] = tmp;
        i = smallest;
    }
    return res;
}

bool empty(MinHeap *pq) {
    return pq->size == 0;
}


int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};


int swimInWater(int** grid, int n, int* gridColSize) {
    bool visited[MAXN][MAXN] = {false};
    MinHeap pq = {0};

    push(&pq, (Node){grid[0][0], 0, 0});
    visited[0][0] = true;
    int maxElev = 0;

    while (!empty(&pq)) {
        Node cur = pop(&pq);
        if (cur.h > maxElev) maxElev = cur.h;
        if (cur.x == n - 1 && cur.y == n - 1) return maxElev;

        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dirs[d][0];
            int ny = cur.y + dirs[d][1];
            if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if (visited[nx][ny]) continue;
            visited[nx][ny] = true;
            push(&pq, (Node){grid[nx][ny], nx, ny});
        }
    }
    return -1;
}

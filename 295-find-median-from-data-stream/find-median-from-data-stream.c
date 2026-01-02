#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
    int isMinHeap; 
} Heap;

Heap* createHeap(int capacity, int isMinHeap) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->data = (int*)malloc(sizeof(int) * (capacity + 1));
    h->size = 0;
    h->capacity = capacity;
    h->isMinHeap = isMinHeap;
    return h;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(Heap* h, int val) {
    h->data[++h->size] = val;
    int cur = h->size;
    while (cur > 1) {
        int parent = cur / 2;
        if (h->isMinHeap ? h->data[cur] < h->data[parent] : h->data[cur] > h->data[parent]) {
            swap(&h->data[cur], &h->data[parent]);
            cur = parent;
        } else break;
    }
}

int pop(Heap* h) {
    int top = h->data[1];
    h->data[1] = h->data[h->size--];
    int cur = 1;
    while (cur * 2 <= h->size) {
        int child = cur * 2;
        if (child + 1 <= h->size && (h->isMinHeap ? h->data[child + 1] < h->data[child] : h->data[child + 1] > h->data[child])) {
            child++;
        }
        if (h->isMinHeap ? h->data[child] < h->data[cur] : h->data[child] > h->data[cur]) {
            swap(&h->data[cur], &h->data[child]);
            cur = child;
        } else break;
    }
    return top;
}

typedef struct {
    Heap* maxHeap; // Sol taraf (küçük sayılar)
    Heap* minHeap; // Sağ taraf (büyük sayılar)
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* mf = (MedianFinder*)malloc(sizeof(MedianFinder));
    mf->maxHeap = createHeap(50001, 0);
    mf->minHeap = createHeap(50001, 1);
    return mf;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    push(obj->maxHeap, num);
    push(obj->minHeap, pop(obj->maxHeap));
    if (obj->minHeap->size > obj->maxHeap->size) {
        push(obj->maxHeap, pop(obj->minHeap));
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->maxHeap->size > obj->minHeap->size) {
        return (double)obj->maxHeap->data[1];
    }
    return (obj->maxHeap->data[1] + obj->minHeap->data[1]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->maxHeap->data);
    free(obj->maxHeap);
    free(obj->minHeap->data);
    free(obj->minHeap);
    free(obj); //kod çalışmazsa yazılımı bırakıyorum 
}
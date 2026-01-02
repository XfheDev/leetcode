#include <stdlib.h>

typedef struct {
    int* max_h; 
    int* min_h; 
    int max_sz;
    int min_sz;
} MedianFinder;


void max_push(int* heap, int* size, int val) {
    int i = ++(*size);
    while (i > 1 && val > heap[i / 2]) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = val;
}


int max_pop(int* heap, int* size) {
    int top = heap[1];
    int last = heap[(*size)--];
    int i = 1, child;
    while (i * 2 <= *size) {
        child = i * 2;
        if (child < *size && heap[child + 1] > heap[child]) child++;
        if (last >= heap[child]) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = last;
    return top;
}


void min_push(int* heap, int* size, int val) {
    int i = ++(*size);
    while (i > 1 && val < heap[i / 2]) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = val;
}


int min_pop(int* heap, int* size) {
    int top = heap[1];
    int last = heap[(*size)--];
    int i = 1, child;
    while (i * 2 <= *size) {
        child = i * 2;
        if (child < *size && heap[child + 1] < heap[child]) child++;
        if (last <= heap[child]) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = last;
    return top;
}

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));

    obj->max_h = (int*)malloc(sizeof(int) * 25005);
    obj->min_h = (int*)malloc(sizeof(int) * 25005);
    obj->max_sz = 0;
    obj->min_sz = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    max_push(obj->max_h, &obj->max_sz, num);
    
    min_push(obj->min_h, &obj->min_sz, max_pop(obj->max_h, &obj->max_sz));
    
    if (obj->max_sz < obj->min_sz) {
        max_push(obj->max_h, &obj->max_sz, min_pop(obj->min_h, &obj->min_sz));
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->max_sz > obj->min_sz) {
        return (double)obj->max_h[1];
    }
    return (obj->max_h[1] + obj->min_h[1]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->max_h);
    free(obj->min_h);
    free(obj); //kodu optimize ettim çalışmazsa harbici bırakıyom ya
}
#include <stdio.h>
#include <stdlib.h>

#define maxn 100010
#define lson(idx) (2*idx+1)
#define rson(idx) (2*idx+2)
#define parent(idx) ((idx-1)/2)

int data[maxn];
int heap_size = 0;

int cmp_small(int a, int b) {
    return a < b;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shiftUp(int curr) {
    if (curr == 0) return;
    int par = parent(curr);
    if (cmp_small(data[curr], data[par])) {
        swap(&data[curr], &data[par]);
        shiftUp(par);
    }
}

void shiftDown(int curr) {
    int lsonId = lson(curr);
    int rsonId = rson(curr);
    int optId = curr;
    if (lsonId < heap_size && cmp_small(data[lsonId], data[optId])) {
        optId = lsonId;
    }
    if (rsonId < heap_size && cmp_small(data[rsonId], data[optId])) {
        optId = rsonId;
    }
    if (optId != curr) {
        swap(&data[curr], &data[optId]);
        shiftDown(optId);
    }
}

void heap_push(int val) {
    data[heap_size++] = val;
    shiftUp(heap_size - 1);
}

void heap_pop() {
    swap(&data[0], &data[heap_size - 1]);
    heap_size--;
    shiftDown(0);
}

int heap_top() {
    return data[0];
}

void heap_clear() {
    heap_size = 0;
}

int main() {
    heap_clear();
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        heap_push(x);
    }
    for (int i = 0; i < k; ++i) {
        int x;
        scanf("%d", &x);
        if (x > heap_top()) {
            heap_push(x);
            heap_pop();
        }
        printf("%d ", heap_top());
    }
    printf("\n");
    return 0;
}
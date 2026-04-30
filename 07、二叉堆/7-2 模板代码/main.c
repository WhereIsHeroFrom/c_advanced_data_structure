#include <stdio.h>
#include <stdlib.h>

#define maxn 100010
#define lson(idx) (2*idx+1)
#define rson(idx) (2*idx+2)
#define parent(idx) ((idx-1)/2)

int data[maxn];
int heap_size = 0;

int cmp_big(int a, int b) {
    return a > b;
}

int cmp_small(int a, int b) {
    return a < b;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shiftUp(int curr, int (*cmp)(int, int)) {
    if (curr == 0) return;
    int par = parent(curr);
    if (cmp(data[curr], data[par])) {
        swap(&data[curr], &data[par]);
        shiftUp(par, cmp);
    }
}

void shiftDown(int curr, int (*cmp)(int, int)) {
    int lsonId = lson(curr);
    int rsonId = rson(curr);
    int optId = curr;
    if (lsonId < heap_size && cmp(data[lsonId], data[optId])) {
        optId = lsonId;
    }
    if (rsonId < heap_size && cmp(data[rsonId], data[optId])) {
        optId = rsonId;
    }
    if (optId != curr) {
        swap(&data[curr], &data[optId]);
        shiftDown(optId, cmp);
    }
}

void heap_push(int val, int (*cmp)(int, int)) {
    data[heap_size++] = val;
    shiftUp(heap_size - 1, cmp);
}

void heap_pop(int (*cmp)(int, int)) {
    swap(&data[0], &data[heap_size - 1]);
    heap_size--;
    shiftDown(0, cmp);
}

int heap_top() {
    return data[0];
}

int heap_empty() {
    return heap_size == 0;
}

void heap_clear() {
    heap_size = 0;
}

int main() {
    heap_clear();
    for (int i = 0; i < 5; ++i) {
        int x = rand() % 30, y = rand() % 30;
        heap_push(x, cmp_big);
        heap_push(y, cmp_big);
        printf("塞入两个数：%d %d\n", x, y);
        printf("目前最大的数是：%d\n", heap_top());
        heap_pop(cmp_big);
        printf("弹出最大的那个数\n");
    }
    return 0;
}
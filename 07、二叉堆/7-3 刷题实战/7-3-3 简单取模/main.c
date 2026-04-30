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

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shiftUp(int curr) {
    if (curr == 0) return;
    int par = parent(curr);
    if (cmp_big(data[curr], data[par])) {
        swap(&data[curr], &data[par]);
        shiftUp(par);
    }
}

void shiftDown(int curr) {
    int lsonId = lson(curr);
    int rsonId = rson(curr);
    int optId = curr;
    if (lsonId < heap_size && cmp_big(data[lsonId], data[optId])) {
        optId = lsonId;
    }
    if (rsonId < heap_size && cmp_big(data[rsonId], data[optId])) {
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

int heap_empty() {
    return heap_size == 0;
}

void heap_clear() {
    heap_size = 0;
}

int main() {
    heap_clear();
    int n, k;
    long long sum = 0;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        heap_push(x);
        sum += x;
    }
    while (k--) {
        int x;
        scanf("%d", &x);
        while (!heap_empty()) {
            if (heap_top() >= x) {
                sum -= heap_top();
                int y = heap_top() % x;
                sum += y;
                heap_pop();
                heap_push(y);
            } else break;
        }
        printf("%lld ", sum);
    }
    printf("\n");
    return 0;
}
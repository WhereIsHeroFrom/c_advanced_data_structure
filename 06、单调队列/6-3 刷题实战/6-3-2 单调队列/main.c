#include <stdio.h>
#include <stdlib.h>

#define maxn 100001

int h[maxn], ans[maxn];

typedef struct {
    int data[maxn];
    int front;
    int rear;
} MonotonicQueue;

MonotonicQueue deque;

int cmp_max(int a, int b) {
    return a <= b;
}

int cmp_min(int a, int b) {
    return a >= b;
}

void findIntervalMinMax(int n, int k, int (*cmp)(int, int)) {
    deque.front = 0;
    deque.rear = 0;
    for (int i = 0; i < n; ++i) {
        while (deque.rear > deque.front && cmp(h[deque.data[deque.rear - 1]], h[i])) {
            deque.rear--;
        }
        deque.data[deque.rear++] = i;
        while (deque.data[deque.rear - 1] - deque.data[deque.front] + 1 > k) {
            deque.front++;
        }
        ans[i] = h[deque.data[deque.front]];
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
    }
    findIntervalMinMax(n, k, cmp_min);
    for (int i = k - 1; i < n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    findIntervalMinMax(n, k, cmp_max);
    for (int i = k - 1; i < n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
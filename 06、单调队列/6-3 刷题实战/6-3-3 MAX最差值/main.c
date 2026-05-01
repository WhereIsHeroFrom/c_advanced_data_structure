#include <stdio.h>
#include <stdlib.h>

#define maxn 1000001

int h[maxn], G[maxn], F[maxn];

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

void findIntervalMinMax(int n, int k, int ans[], int (*cmp)(int, int)) {
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
    findIntervalMinMax(n, k, G, cmp_max);
    findIntervalMinMax(n, k, F, cmp_min);
    int ret = -1000000000;
    for (int i = 0; i < n; ++i) {
        int v = G[i] - F[i];
        if (v > ret) {
            ret = v;
        }
    }
    printf("%d\n", ret);
    return 0;
}
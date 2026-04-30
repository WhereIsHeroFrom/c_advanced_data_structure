#include <stdio.h>
#include <stdlib.h>

#define maxn 1000001

int h[maxn], G[maxn], F[maxn];
int deque[maxn];
int deque_front, deque_back;

int cmp_max(int a, int b) {
    return a <= b;
}

int cmp_min(int a, int b) {
    return a >= b;
}

void findIntervalMinMax(int n, int k, int ans[], int (*cmp)(int, int)) {
    deque_front = 0;
    deque_back = 0;
    for (int i = 0; i < n; ++i) {
        while (deque_back > deque_front && cmp(h[deque[deque_back - 1]], h[i])) {
            deque_back--;
        }
        deque[deque_back++] = i;
        while (deque[deque_back - 1] - deque[deque_front] + 1 > k) {
            deque_front++;
        }
        ans[i] = h[deque[deque_front]];
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
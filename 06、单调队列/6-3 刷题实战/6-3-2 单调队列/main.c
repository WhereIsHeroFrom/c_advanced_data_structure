#include <stdio.h>
#include <stdlib.h>

#define maxn 100001

int h[maxn], ans[maxn];
int deque[maxn];
int deque_front, deque_back;

int cmp_max(int a, int b) {
    return a <= b;
}

int cmp_min(int a, int b) {
    return a >= b;
}

void findIntervalMinMax(int n, int k, int (*cmp)(int, int)) {
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
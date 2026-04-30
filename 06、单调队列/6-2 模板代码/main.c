#include <stdio.h>
#include <stdlib.h>

#define maxn 100001

int deque[maxn];
int deque_front, deque_back;

int cmp_max(int a, int b) {
    return a <= b;
}

int cmp_min(int a, int b) {
    return a >= b;
}

void findIntervalMinMax(int n, int h[], int k, int ans[], int (*cmp)(int, int)) {
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
    int h[] = {8, 7, 6, 9, 11};
    int ans[10];
    findIntervalMinMax(5, h, 3, ans, cmp_max);
    for (int i = 0; i < 5; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    findIntervalMinMax(5, h, 3, ans, cmp_min);
    for (int i = 0; i < 5; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define maxn 100001

int h[maxn], ans[maxn];

typedef struct {
    int data[maxn];
    int top;
} MonotonicStack;

MonotonicStack stk;

int cmp(int a, int b) {
    return a >= b;
}

void findFirstMeetOnLeft(int n) {
    stk.top = 0;
    stk.data[stk.top++] = 0;
    for (int i = 1; i <= n; ++i) {
        while (stk.top > 0 && !cmp(h[stk.data[stk.top - 1]], h[i])) {
            stk.top--;
        }
        ans[i] = stk.data[stk.top - 1];
        stk.data[stk.top++] = i;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
    }
    findFirstMeetOnLeft(n);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define maxn 700001
#define inf 2000000000

int h[maxn], ans[maxn];

typedef struct {
    int data[maxn];
    int top;
} MonotonicStack;

MonotonicStack stk;

int cmp(int a, int b) {
    return a > b;
}

void findFirstMeetOnLeft(int n) {
    stk.top = 0;
    h[0] = inf;
    stk.data[stk.top++] = 0;
    for (int i = 1; i <= n; ++i) {
        while (stk.top > 0 && !cmp(h[stk.data[stk.top - 1]], h[i])) {
            stk.top--;
        }
        ans[i] = stk.data[stk.top - 1];
        stk.data[stk.top++] = i;
    }
}

void reverseArray(int n, int arr[]) {
    for (int i = 1; i <= n / 2; ++i) {
        int tmp = arr[i];
        arr[i] = arr[n + 1 - i];
        arr[n + 1 - i] = tmp;
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
        if (ans[i] == 0) ans[i] = -1;
        printf("%d ", ans[i]);
    }
    printf("\n");
    reverseArray(n, h);
    findFirstMeetOnLeft(n);
    reverseArray(n, ans);
    reverseArray(n, h);
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == 0) ans[i] = -1;
        else ans[i] = (n + 1) - ans[i];
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define maxn 300001
#define inf -1

int h[maxn], l[maxn], r[maxn];
int stk[maxn];
int stk_top;

int cmp(int a, int b) {
    return a < b;
}

void findFirstMeetOnLeft(int n, int ans[]) {
    stk_top = 0;
    h[0] = inf;
    stk[stk_top++] = 0;
    for (int i = 1; i <= n; ++i) {
        while (stk_top > 0 && !cmp(h[stk[stk_top - 1]], h[i])) {
            stk_top--;
        }
        ans[i] = stk[stk_top - 1];
        stk[stk_top++] = i;
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
    findFirstMeetOnLeft(n, l);
    reverseArray(n, h);
    findFirstMeetOnLeft(n, r);
    reverseArray(n, h);
    reverseArray(n, r);
    for (int i = 1; i <= n; ++i) {
        r[i] = (n + 1) - r[i];
    }
    long long max_val = 0;
    for (int i = 1; i <= n; ++i) {
        long long x = (long long)(r[i] - 1) - (l[i] + 1) + 1;
        x = x * h[i];
        if (x > max_val) {
            max_val = x;
        }
    }
    printf("%lld\n", max_val);
    return 0;
}
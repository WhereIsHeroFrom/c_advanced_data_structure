#include <stdio.h>
#include <stdlib.h>

#define type long long
#define maxn 500010

type tree[maxn];
int n;

int lowbit(int x) {
    return x & (-x);
}

void FenwickTree_Update(int idx, type val) {
    while (idx <= n) {
        tree[idx] += val;
        idx += lowbit(idx);
    }
}

type FenwickTree_Query(int idx) {
    type sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= lowbit(idx);
    }
    return sum;
}

type FenwickTree_QueryRange(int l, int r) {
    return FenwickTree_Query(r) - FenwickTree_Query(l - 1);
}

int main() {
    int m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        type x;
        scanf("%lld", &x);
        FenwickTree_Update(i, x);
    }
    while (m--) {
        int z, x, y;
        scanf("%d %d %d", &z, &x, &y);
        if (z == 1) {
            FenwickTree_Update(x, y);
        } else {
            printf("%lld\n", FenwickTree_QueryRange(x, y));
        }
    }
    return 0;
}
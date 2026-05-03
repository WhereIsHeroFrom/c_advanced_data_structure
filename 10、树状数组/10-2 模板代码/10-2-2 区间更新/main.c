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

void FenwickTree_UpdateInterval(int l, int r, type val) {
    FenwickTree_Update(l, val);
    FenwickTree_Update(r + 1, -val);
}

type FenwickTree_QueryIndex(int idx) {
    return FenwickTree_Query(idx);
}

int main() {
    int m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        type x;
        scanf("%lld", &x);
        FenwickTree_UpdateInterval(i, i, x);
    }
    while (m--) {
        int z, x, y, k;
        scanf("%d", &z);
        if (z == 1) {
            scanf("%d %d %d", &x, &y, &k);
            FenwickTree_UpdateInterval(x, y, k);
        } else {
            scanf("%d", &x);
            printf("%lld\n", FenwickTree_QueryIndex(x));
        }
    }
    return 0;
}
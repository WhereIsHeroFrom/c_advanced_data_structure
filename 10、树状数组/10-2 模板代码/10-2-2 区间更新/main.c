#include <stdio.h>
#include <stdlib.h>

#define maxn 500010

int tree[maxn];
int n;

int lowbit(int x) {
    return x & (-x);
}

void FenwickTree_Update(int idx, int val) {
    while (idx <= n) {
        tree[idx] += val;
        idx += lowbit(idx);
    }
}

int FenwickTree_Query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= lowbit(idx);
    }
    return sum;
}

void FenwickTree_UpdateInterval(int l, int r, int val) {
    FenwickTree_Update(l, val);
    FenwickTree_Update(r + 1, -val);
}

int FenwickTree_QueryIndex(int idx) {
    return FenwickTree_Query(idx);
}

int main() {
    int m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
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
            printf("%d\n", FenwickTree_QueryIndex(x));
        }
    }
    return 0;
}
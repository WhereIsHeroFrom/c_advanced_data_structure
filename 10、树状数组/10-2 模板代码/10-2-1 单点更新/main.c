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

int FenwickTree_QueryRange(int l, int r) {
    return FenwickTree_Query(r) - FenwickTree_Query(l - 1);
}

int main() {
    int m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        FenwickTree_Update(i, x);
    }
    while (m--) {
        int z, x, y;
        scanf("%d %d %d", &z, &x, &y);
        if (z == 1) {
            FenwickTree_Update(x, y);
        } else {
            printf("%d\n", FenwickTree_QueryRange(x, y));
        }
    }
    return 0;
}
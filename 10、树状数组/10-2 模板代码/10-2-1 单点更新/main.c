#include <stdio.h>

////////////////////////树状数组模板(单点更新)////////////////////////
#define type long long
#define maxn 500010

typedef struct {
    type tree[maxn];
    int n;
} FenwickTree;

int lowbit(int x) {
    return x & (-x);
}

void FenwickTree_Init(FenwickTree* ft, int n) {
    ft->n = n;
    for (int i = 1; i <= n; ++i) {
        ft->tree[i] = 0;
    }
}

void FenwickTree_Update(FenwickTree* ft, int idx, type val) {
    while (idx <= ft->n) {
        ft->tree[idx] += val;
        idx += lowbit(idx);
    }
}

type FenwickTree_Query(FenwickTree* ft, int idx) {
    type sum = 0;
    while (idx > 0) {
        sum += ft->tree[idx];
        idx -= lowbit(idx);
    }
    return sum;
}

type FenwickTree_QueryRange(FenwickTree* ft, int l, int r) {
    return FenwickTree_Query(ft, r) - FenwickTree_Query(ft, l - 1);
}
////////////////////////树状数组模板(单点更新)////////////////////////
FenwickTree ft;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    FenwickTree_Init(&ft, n);
    
    for (int i = 1; i <= n; ++i) {
        type x;
        scanf("%lld", &x);
        FenwickTree_Update(&ft, i, x);
    }
    while (m--) {
        int z, x, y;
        scanf("%d %d %d", &z, &x, &y);
        if (z == 1) {
            FenwickTree_Update(&ft, x, y);
        } else {
            printf("%lld\n", FenwickTree_QueryRange(&ft, x, y));
        }
    }
    return 0;
}
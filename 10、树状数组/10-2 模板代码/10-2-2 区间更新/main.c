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

void FenwickTree_UpdateInterval(FenwickTree* ft, int l, int r, type val) {
    FenwickTree_Update(ft, l, val);
    FenwickTree_Update(ft, r + 1, -val);
}

type FenwickTree_QueryIndex(FenwickTree* ft, int idx) {
    return FenwickTree_Query(ft, idx);
}

FenwickTree ft;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    
    FenwickTree_Init(&ft, n);
    
    for (int i = 1; i <= n; ++i) {
        type x;
        scanf("%lld", &x);
        FenwickTree_UpdateInterval(&ft, i, i, x);
    }
    while (m--) {
        int z, x, y, k;
        scanf("%d", &z);
        if (z == 1) {
            scanf("%d %d %d", &x, &y, &k);
            FenwickTree_UpdateInterval(&ft, x, y, k);
        } else {
            scanf("%d", &x);
            printf("%lld\n", FenwickTree_QueryIndex(&ft, x));
        }
    }
    return 0;
}
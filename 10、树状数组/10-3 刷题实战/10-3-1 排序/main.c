#include <stdio.h>
////////////////////////树状数组模板(单点更新)////////////////////////
#define type long long
#define maxn 1000010

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

int a[maxn];
FenwickTree ft;
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    
    FenwickTree_Init(&ft, maxn-1);
    
    long long sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        FenwickTree_Update(&ft, a[i], 1);
        sum += (long long)a[i] * FenwickTree_Query(&ft, a[i] - 1);
    }
    printf("%lld\n", sum);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mod 998244353

/////////////////////////////离散化模板/////////////////////////////
// https://www.luogu.com.cn/problem/B3694

// 2333 20 1.7 -5 20 1 20 -5
// 第一步：排序  -5 -5 1 1.7 20 20 20 2333
// 第二步：去重  -5 1 1.7 20 2333
//               0  1 2   3  4
#define type int
#define maxn 200010

typedef struct {
    type data[maxn];
    int size;
} Discretizer;

int cmp_type(const void* a, const void* b) {
    type va = *(type*)a;
    type vb = *(type*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

void Discretizer_Init(Discretizer* d) {
    d->size = 0;
}

void Discretizer_AddData(Discretizer* d, type v) {
    d->data[d->size++] = v;
}

void Discretizer_Process(Discretizer* d) {
    qsort(d->data, d->size, sizeof(type), cmp_type);
    int lastIdx = 0;
    for (int i = 1; i < d->size; ++i) {
        type x = d->data[i];
        if (x != d->data[lastIdx]) {
            d->data[++lastIdx] = x;
        }
    }
    d->size = lastIdx + 1;
}

int Discretizer_Get(Discretizer* d, type v) {
    int l = -1, r = d->size;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (d->data[mid] >= v) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if (r == d->size || d->data[r] != v) {
        return -1;
    }
    return r;
}
/////////////////////////////离散化模板/////////////////////////////

////////////////////////树状数组模板(单点更新)////////////////////////

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
Discretizer d;
FenwickTree ft;

int a[maxn];
int lt[maxn];

int main() {
    int n;
    scanf("%d", &n);
    
    Discretizer_Init(&d);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        Discretizer_AddData(&d, a[i]);
    }
    Discretizer_Process(&d);
    for (int i = 0; i < n; ++i) {
        a[i] = Discretizer_Get(&d, a[i]) + 1;
    }
    FenwickTree_Init(&ft, n);
    
    for (int i = 0; i < n; ++i) {
        FenwickTree_Update(&ft, a[i], 1);
        lt[i] = FenwickTree_Query(&ft, a[i] - 1);
    }
    
    FenwickTree_Init(&ft, n);
    
    long long sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        FenwickTree_Update(&ft, a[i], 1);
        int gt = FenwickTree_QueryRange(&ft, a[i] + 1, n);
        sum += (long long)lt[i] * gt % mod;
        sum %= mod;
    }
    printf("%lld\n", sum);
    return 0;
}
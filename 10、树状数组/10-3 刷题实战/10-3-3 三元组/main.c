#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mod 998244353
#define maxn 200001

int d_data[maxn];
int d_size;
int tree[maxn];
int a[maxn];
int lt[maxn];

int cmp_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

void Discretizer_AddData(int v) {
    d_data[d_size++] = v;
}

void Discretizer_Process() {
    qsort(d_data, d_size, sizeof(int), cmp_int);
    int lastIdx = 0;
    for (int i = 1; i < d_size; ++i) {
        int x = d_data[i];
        if (x != d_data[lastIdx]) {
            d_data[++lastIdx] = x;
        }
    }
    d_size = lastIdx + 1;
}

int Discretizer_Get(int v) {
    int l = -1, r = d_size;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (d_data[mid] >= v) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if (r == d_size || d_data[r] != v) {
        return -1;
    }
    return r;
}

int lowbit(int x) {
    return x & (-x);
}

void FenwickTree_Update(int idx, int val, int n) {
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

void FenwickTree_Clear(int n) {
    memset(tree, 0, sizeof(tree[0]) * (n + 1));
}

int main() {
    int n;
    scanf("%d", &n);
    d_size = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        Discretizer_AddData(a[i]);
    }
    Discretizer_Process();
    for (int i = 0; i < n; ++i) {
        a[i] = Discretizer_Get(a[i]) + 1;
    }
    FenwickTree_Clear(n);
    for (int i = 0; i < n; ++i) {
        FenwickTree_Update(a[i], 1, n);
        lt[i] = FenwickTree_Query(a[i] - 1);
    }
    FenwickTree_Clear(n);
    long long sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        FenwickTree_Update(a[i], 1, n);
        int gt = FenwickTree_QueryRange(a[i] + 1, n);
        sum += (long long)lt[i] * gt % mod;
        sum %= mod;
    }
    printf("%lld\n", sum);
    return 0;
}
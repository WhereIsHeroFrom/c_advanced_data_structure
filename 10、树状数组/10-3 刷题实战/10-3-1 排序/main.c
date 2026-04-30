#include <stdio.h>
#include <stdlib.h>

#define maxn 1000001

long long tree[maxn];

int lowbit(int x) {
    return x & (-x);
}

void FenwickTree_Update(int idx, int val) {
    while (idx < maxn) {
        tree[idx] += val;
        idx += lowbit(idx);
    }
}

long long FenwickTree_Query(int idx) {
    long long sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= lowbit(idx);
    }
    return sum;
}

long long FenwickTree_QueryRange(int l, int r) {
    return FenwickTree_Query(r) - FenwickTree_Query(l - 1);
}

int a[1000001];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    long long sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        FenwickTree_Update(a[i], 1);
        sum += (long long)a[i] * FenwickTree_Query(a[i] - 1);
    }
    printf("%lld\n", sum);
    return 0;
}
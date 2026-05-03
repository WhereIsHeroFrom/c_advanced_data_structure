#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define type int
#define maxn 200001
#define log2n_max 20

type org[maxn];
int st_min[log2n_max][maxn];
int st_max[log2n_max][maxn];
int n;

int cmp_min(int a, int b) {
    return org[a] < org[b];
}

int cmp_max(int a, int b) {
    return org[a] > org[b];
}

void SparseTable_Init() {
    int log2n = (int)log2(n) + 1;
    for (int i = 0; i < n; ++i) {
        st_min[0][i] = i;
        st_max[0][i] = i;
    }
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
            int idx1 = st_min[j - 1][i];
            int idx2 = st_min[j - 1][i + (1 << (j - 1))];
            st_min[j][i] = cmp_min(idx1, idx2) ? idx1 : idx2;
            
            idx1 = st_max[j - 1][i];
            idx2 = st_max[j - 1][i + (1 << (j - 1))];
            st_max[j][i] = cmp_max(idx1, idx2) ? idx1 : idx2;
        }
    }
}

int SparseTable_QueryMin(int l, int r) {
    if (l == r) return l;
    int k = (int)ceil(log2(r - l + 1)) - 1;
    int idx1 = st_min[k][l];
    int idx2 = st_min[k][r - (1 << k) + 1];
    return cmp_min(idx1, idx2) ? idx1 : idx2;
}

int SparseTable_QueryMax(int l, int r) {
    if (l == r) return l;
    int k = (int)ceil(log2(r - l + 1)) - 1;
    int idx1 = st_max[k][l];
    int idx2 = st_max[k][r - (1 << k) + 1];
    return cmp_max(idx1, idx2) ? idx1 : idx2;
}

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

int main() {
    int m;
    n = read();
    m = read();
    for (int i = 0; i < n; ++i) {
        org[i] = read();
    }
    SparseTable_Init();
    long long minsum = 0, maxsum = 0;
    while (m--) {
        int l = read();
        int r = read();
        l--;
        r--;
        minsum += org[SparseTable_QueryMin(l, r)];
        maxsum += org[SparseTable_QueryMax(l, r)];
    }
    printf("%lld %lld\n", minsum, maxsum);
    return 0;
}
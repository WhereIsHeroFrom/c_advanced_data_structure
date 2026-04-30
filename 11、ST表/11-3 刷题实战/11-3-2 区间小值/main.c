#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxn 1000001
#define log2n_max 20

int org[maxn];
int st[log2n_max][maxn];
int n;

int cmp_min(int a, int b) {
    return org[a] < org[b];
}

void SparseTable_Init() {
    int log2n = (int)log2(n) + 1;
    for (int i = 0; i < n; ++i) {
        st[0][i] = i;
    }
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
            int idx1 = st[j - 1][i];
            int idx2 = st[j - 1][i + (1 << (j - 1))];
            st[j][i] = cmp_min(idx1, idx2) ? idx1 : idx2;
        }
    }
}

int SparseTable_Query(int l, int r) {
    if (l == r) {
        return l;
    }
    int k = (int)ceil(log2(r - l + 1)) - 1;
    int idx1 = st[k][l];
    int idx2 = st[k][r - (1 << k) + 1];
    return cmp_min(idx1, idx2) ? idx1 : idx2;
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
    n = read();
    for (int i = 0; i < n; ++i) {
        org[i] = read();
    }
    int k = read();
    SparseTable_Init();
    for (int i = 0; i < n; ++i) {
        int l = i - k;
        int r = i + k;
        if (l < 0) l = 0;
        if (r >= n) r = n - 1;
        printf("%d ", org[SparseTable_Query(l, r)]);
    }
    printf("\n");
    return 0;
}
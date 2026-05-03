#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define type double
#define maxn 100001
#define log2n_max 20

type org[maxn];
int st[log2n_max][maxn];
int n;

int cmp_max(int a, int b) {
    return org[a] > org[b];
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
            st[j][i] = cmp_max(idx1, idx2) ? idx1 : idx2;
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
    return cmp_max(idx1, idx2) ? idx1 : idx2;
}

int main() {
    int m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &org[i]);
    }
    SparseTable_Init();
    while (m--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--;
        r--;
        printf("%.0f\n", org[SparseTable_Query(l, r)]);
    }
    return 0;
}
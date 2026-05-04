#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define type int
#define maxn 1000001
#define log2n_max 20

typedef int (*cmp_t)(type a, type b);

//////////////////////////////////////////ST表模板////////////////////////////////////////////
// RMQ模板
// https://www.luogu.com.cn/problem/P3865
// 静态区间最值问题

typedef struct {
    type org[maxn];
    int st[log2n_max][maxn];
    int n;
    cmp_t cmp;
} SparseTable;

int cmpMax(type a, type b) {
    return a > b;
}

int cmpMin(type a, type b) {
    return a < b;
}

void SparseTable_Init(SparseTable* st, int n, type* arr, cmp_t cmp) {
    st->n = n;
    st->cmp = cmp;
    for (int i = 0; i < n; ++i) {
        st->org[i] = arr[i];
    }
    
    // log2(n)+1,  n
    int log2n = (int)log2(n) + 1;
    // st[j][i] 表示的是 [i, i + 2^j-1 ] 这个区间中的最值（所在的下标）
    // st[0][i] 表示的是 [i, i] 这个区间中的最值（所在的下标），那就是 i
    for (int i = 0; i < n; ++i) {
        st->st[0][i] = i;
    }

    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
            // [i, i+(1<<j)-1]
            /*
                1、st[j][i] 的区间长度是 2^j
                2、把它拆成两个长度为 2^(j-1) 的区间
                   2.1 一个区间是 [i, i + 2^(j-1) - 1]           =>  st[j-1][i]
                   2.2 一个区间是 [i + 2^(j-1), i + 2^j - 1]     =>  st[j-1][i + (1<<(j-1))]
            */
            int idx1 = st->st[j - 1][i];
            int idx2 = st->st[j - 1][i + (1 << (j - 1))];
            st->st[j][i] = st->cmp(st->org[idx1], st->org[idx2]) ? idx1 : idx2;
        }
    }
}

/*
1、对于 [l, r] 这个区间，可以拆分成两个长度分别为 2^k 的区间：
    一个区间是以 l 作为起始的： [l, x]
    一个区间是以 r 作为结尾的： [y, r]
    并且，这两个区间的并集是 [l, r]， 所以需要满足 x+1 >= y
2、以 l 作为起始的区间的长度为 2 的 k 次
        它表示的区间就是 [l, l + 2^k - 1]    => x = l + 2^k - 1
   以 r 作为结尾的区间的长度为 2 的 k 次
        它表示的区间就是 [r - 2^k + 1, r]    => y = r - 2^k + 1
3、l + 2^k - 1 + 1 >= r - 2^k + 1
    移项：     2^(k+1)  >= r - l + 1
    取对数：     k      >= log2(r - l + 1) - 1
    所以 k 的值，为 log2(r - l + 1) 取上整 再减一
*/
int SparseTable_Query(SparseTable* st, int l, int r) {
    if (l == r) {
        return l;
    }
    int k = (int)ceil(log2(r - l + 1)) - 1;
    int idx1 = st->st[k][l];
    int idx2 = st->st[k][r - (1 << k) + 1];
    return st->cmp(st->org[idx1], st->org[idx2]) ? idx1 : idx2;
}

type SparseTable_GetValue(SparseTable* st, int idx) {
    return st->org[idx];
}
//////////////////////////////////////////ST表模板////////////////////////////////////////////
SparseTable st;

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
    int n = read();
    type arr[maxn];
    for (int i = 0; i < n; ++i) {
        arr[i] = read();
    }
    int k = read();
    
    SparseTable_Init(&st, n, arr, cmpMin);
    
    for (int i = 0; i < n; ++i) {
        int l = i - k;
        int r = i + k;
        if (l < 0) l = 0;
        if (r >= n) r = n - 1;
        printf("%d ", SparseTable_GetValue(&st, SparseTable_Query(&st, l, r)));
    }
    printf("\n");
    return 0;
}
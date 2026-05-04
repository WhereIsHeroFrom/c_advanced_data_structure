#include <stdio.h>
#include <stdlib.h>
#include <math.h>

////////////////////////////ST表模板////////////////////////////
#define type int
#define maxn 200010
#define log2n_max 18
typedef int (*cmp_t) (type a, type b);

typedef struct {
    type org[maxn];
    int st[log2n_max][maxn];
    int n;  // size
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
    for(int i = 0; i < n; ++i) {
        st->org[i] = arr[i];
    }
    int log2n = (int)log2(n) + 1;
    // st[j][i] 代表的是 [i, i+2^j-1] 这个区间里的最大值
    // st[0][i] 代表的是 [i, i] 这个区间里的最大值
    for(int i = 0; i < n; ++i) {
        st->st[0][i] = i;
    }
    for(int j = 1; (1<<j) <= n; ++j) {
        for(int i = 0; i + (1<<j) - 1 < n; ++i) {
            // st[j][i] -> [i, i + (1<<j) - 1]
            /*
                1、st[j][i] 区间长度是 2^j
                2、把它拆成两个长度为 2^(j-1) 的区间
                    2.1 一个区间是[i, i + 2^(j-1) - 1]
                    2.2 一个区间是[i + 2^(j-1), i + 2^j - 1]
                2.1 -> st[j-1][i]
                2.2 -> st[j-1][i + 1<<(j-1)]
            */
            int idx1 = st->st[j-1][i];
            int idx2 = st->st[j-1][i + (1<<(j-1))];
            st->st[j][i] = st->cmp(st->org[idx1], st->org[idx2] ) ? idx1 : idx2;
        }   
    }
}

/*
1、对于 [l, r] 这个区间，可以拆分成两个长度分别为 2^k 的区间
    一个区间是以 l 作为起始的：[l, x]
    一个区间是以 r 作为结尾的：[y, r]
    并且，这两个区间的并集是 [l, r]，所以满足 x+1 >= y
2、以 l 作为起始的区间长度为 2^k
    所以它表示的区间[l, l + 2^k -1] => x = l + 2^k - 1
   以 r 作为结尾的区间长度为 2^k
    所以它表示的区间[r - 2^k+1, r]  => y = r - 2^k + 1
3、x+1 >= y   => l + 2^k >= r - 2^k + 1
   移项：      2^(k+1)   >= r - l + 1
   取对数：      k+1      >= log2(r - l + 1)
   移项：            k    >= log2(r - l + 1) - 1
   所以 k 的值，是 log2(r - l + 1) 取上整，再减一
*/
int SparseTable_Query(SparseTable* st, int l, int r) {
    if(l == r) {
        return l;
    }
    int k = (int)ceil(  log2(r - l + 1) ) - 1;
    int idx1 = st->st[k][l];
    int idx2 = st->st[k][ r - (1<<k) + 1];
    return st->cmp(st->org[idx1], st->org[idx2]) ? idx1 : idx2;
}

type SparseTable_GetValue(SparseTable* st, int idx) {
    return st->org[ idx ];
}
////////////////////////////ST表模板////////////////////////////
SparseTable stMin, stMax;

type a[maxn];
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    SparseTable_Init(&stMin, n, a, cmpMin);
    SparseTable_Init(&stMax, n, a, cmpMax);
    long long ansMin = 0, ansMax = 0;
    while(m--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--, r--;
        int idxmin = SparseTable_Query(&stMin, l, r);
        int idxmax = SparseTable_Query(&stMax, l, r);
        ansMin += SparseTable_GetValue(&stMin, idxmin);
        ansMax += SparseTable_GetValue(&stMax, idxmax);
    }
    printf("%lld %lld\n", ansMin, ansMax);
    return 0;
}

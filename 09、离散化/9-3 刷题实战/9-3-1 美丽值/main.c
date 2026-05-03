#include <stdio.h>
#include <stdlib.h>

/////////////////////////////离散化模板/////////////////////////////
// https://www.luogu.com.cn/problem/B3694

// 2333 20 1.7 -5 20 1 20 -5
// 第一步：排序  -5 -5 1 1.7 20 20 20 2333
// 第二步：去重  -5 1 1.7 20 2333
//               0  1 2   3  4
#define type int
#define maxn 1000010

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
Discretizer d;

typedef struct {
    type h;
    int b;
} HB;

HB hb[maxn];
type k[maxn];
int maxv[maxn];

int cmp_hb(const void* a, const void* b) {
    HB* ha = (HB*)a;
    HB* hb = (HB*)b;
    if (ha->h < hb->h) return -1;
    if (ha->h > hb->h) return 1;
    return 0;
}

int main() {
    Discretizer d;
    Discretizer_Init(&d);
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &hb[i].h);
        Discretizer_AddData(&d, hb[i].h);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &hb[i].b);
    }
    for (int i = 0; i < q; ++i) {
        scanf("%d", &k[i]);
        Discretizer_AddData(&d, k[i]);
    }
    Discretizer_Process(&d);
    for (int i = 0; i < n; ++i) {
        hb[i].h = Discretizer_Get(&d, hb[i].h);
    }
    for (int i = 0; i < q; ++i) {
        k[i] = Discretizer_Get(&d, k[i]);
    }
    qsort(hb, n, sizeof(HB), cmp_hb);
    maxv[d.size] = -1;
    int j = n - 1;
    for (int i = d.size - 1; i >= 0; --i) {
        maxv[i] = maxv[i + 1];
        while (j >= 0 && hb[j].h == i) {
            if (hb[j].b > maxv[i]) {
                maxv[i] = hb[j].b;
            }
            j--;
        }
    }
    for (int i = 0; i < q; ++i) {
        int x = k[i];
        printf("%d\n", maxv[x]);
    }
    return 0;
}
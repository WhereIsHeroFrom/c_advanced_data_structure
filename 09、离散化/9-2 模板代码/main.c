#include <stdio.h>
#include <stdlib.h>

/////////////////////////////离散化模板/////////////////////////////
// https://www.luogu.com.cn/problem/B3694

// 2333 20 1.7 -5 20 1 20 -5
// 第一步：排序  -5 -5 1 1.7 20 20 20 2333
// 第二步：去重  -5 1 1.7 20 2333
//               0  1 2   3  4
#define type double
#define maxn 100010

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

type a[100001];
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        Discretizer_Init(&d);
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf", &a[i]);
            Discretizer_AddData(&d, a[i]);
        }
        Discretizer_Process(&d);
        for (int i = 0; i < n; ++i) {
            printf("%d ", Discretizer_Get(&d, a[i]) + 1);
        }
        printf("\n");
    }
    return 0;
}
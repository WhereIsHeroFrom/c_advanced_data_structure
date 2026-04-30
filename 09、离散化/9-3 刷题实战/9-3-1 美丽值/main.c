#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 1000010

int d_data[maxn];
int d_size;

typedef struct {
    int h, b;
} HB;

HB hb[maxn];
int k[maxn];
int maxv[maxn];

void Discretizer_AddData(int v) {
    d_data[d_size++] = v;
}

int cmp_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
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

int Discretizer_Size() {
    return d_size;
}

int cmp_hb(const void* a, const void* b) {
    HB* ha = (HB*)a;
    HB* hb = (HB*)b;
    return ha->h - hb->h;
}

int main() {
    d_size = 0;
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &hb[i].h);
        Discretizer_AddData(hb[i].h);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &hb[i].b);
    }
    for (int i = 0; i < q; ++i) {
        scanf("%d", &k[i]);
        Discretizer_AddData(k[i]);
    }
    Discretizer_Process();
    for (int i = 0; i < n; ++i) {
        hb[i].h = Discretizer_Get(hb[i].h);
    }
    for (int i = 0; i < q; ++i) {
        k[i] = Discretizer_Get(k[i]);
    }
    qsort(hb, n, sizeof(HB), cmp_hb);
    maxv[Discretizer_Size()] = -1;
    int j = n - 1;
    for (int i = Discretizer_Size() - 1; i >= 0; --i) {
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
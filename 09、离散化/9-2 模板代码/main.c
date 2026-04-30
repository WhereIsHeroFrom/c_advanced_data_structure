#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 100010

int data[maxn];
int data_size;

void Discretizer_AddData(int v) {
    data[data_size++] = v;
}

int cmp_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

void Discretizer_Process() {
    qsort(data, data_size, sizeof(int), cmp_int);
    int lastIdx = 0;
    for (int i = 1; i < data_size; ++i) {
        int x = data[i];
        if (x != data[lastIdx]) {
            data[++lastIdx] = x;
        }
    }
    data_size = lastIdx + 1;
}

int Discretizer_Get(int v) {
    int l = -1, r = data_size;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (data[mid] >= v) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if (r == data_size || data[r] != v) {
        return -1;
    }
    return r;
}

int Discretizer_Size() {
    return data_size;
}

double a[100001];

int main() {
    int t;
    while (scanf("%d", &t) != EOF) {
        while (t--) {
            data_size = 0;
            int n;
            scanf("%d", &n);
            for (int i = 0; i < n; ++i) {
                scanf("%lf", &a[i]);
                Discretizer_AddData((int)a[i]);
            }
            Discretizer_Process();
            for (int i = 0; i < n; ++i) {
                printf("%d ", Discretizer_Get((int)a[i]) + 1);
            }
            printf("\n");
        }
    }
    return 0;
}
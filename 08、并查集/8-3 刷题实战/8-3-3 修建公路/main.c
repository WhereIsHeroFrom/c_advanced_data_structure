#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxn 100010

typedef struct {
    int u, v;
    long long w;
} Edge;

int far[maxn];
Edge edges[maxn * 3];
int edge_count;

int cmp(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->w > e2->w ? 1 : (e1->w < e2->w ? -1 : 0);
}

void UFSet_Init(int n) {
    for (int i = 1; i <= n; ++i) {
        far[i] = i;
    }
}

int UFSet_Find(int id) {
    if (far[id] == id) {
        return id;
    }
    return far[id] = UFSet_Find(far[id]);
}

int UFSet_Union(int id1, int id2) {
    int s1 = UFSet_Find(id1);
    int s2 = UFSet_Find(id2);
    if (s1 == s2) {
        return 0;
    }
    far[s1] = s2;
    return 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    edge_count = 0;
    UFSet_Init(n);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        edges[edge_count++] = (Edge){a, b, c};
    }
    qsort(edges, edge_count, sizeof(Edge), cmp);
    long long sum = 0;
    int edge_count_result = 0;
    for (int i = 0; i < edge_count; ++i) {
        Edge* e = &edges[i];
        if (UFSet_Union(e->u, e->v)) {
            sum += e->w;
            edge_count_result++;
        }
    }
    if (edge_count_result < n - 1) {
        printf("-1\n");
    } else {
        printf("%lld\n", sum);
    }
    return 0;
}
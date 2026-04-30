#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxn 100010

typedef struct {
    int u, v, w;
} Edge;

int far[maxn];
Edge edges[maxn];

int cmp(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->w - e2->w;
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
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    qsort(edges, m, sizeof(Edge), cmp);
    UFSet_Init(n);
    int sum = 0, cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (UFSet_Union(edges[i].u, edges[i].v)) {
            sum += edges[i].w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    printf("%d\n", sum);
    return 0;
}
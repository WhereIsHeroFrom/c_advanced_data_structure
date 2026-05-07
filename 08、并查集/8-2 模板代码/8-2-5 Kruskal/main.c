#include <stdio.h>
#include <string.h>
#include <stdlib.h>

////////////////////////Kruskal算法模板////////////////////////

typedef struct {
    int u, v, w;
} Edge;

int cmp(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->w - e2->w;
}

//////////////////////并查集模板(路径压缩)//////////////////////

// 并：合并
// 查：查找
// 集：集合

#define maxn 400010

typedef struct {
    int far[maxn];
    int n;
} UFSet;

void UFSet_Init(UFSet* uf, int n) {
    uf->n = n;
    for (int i = 1; i <= n; ++i) {
        uf->far[i] = i;
    }
}

int UFSet_Find(UFSet* uf, int id) {
    if (uf->far[id] == id) {
        return id;
    }
    return uf->far[id] = UFSet_Find(uf, uf->far[id]);
}

int UFSet_Union(UFSet* uf, int id1, int id2) {
    int s1 = UFSet_Find(uf, id1);
    int s2 = UFSet_Find(uf, id2);
    if (s1 == s2) {
        return 0;
    }
    uf->far[s1] = s2;
    return 1;
}
//////////////////////并查集模板(路径压缩)//////////////////////
////////////////////////Kruskal算法模板////////////////////////

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Edge edges[maxn];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    qsort(edges, m, sizeof(Edge), cmp);
    UFSet uf;
    UFSet_Init(&uf, n);
    long long sum = 0, cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (UFSet_Union(&uf, edges[i].u, edges[i].v)) {
            sum += edges[i].w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }
    if(cnt != n - 1) {
        printf("orz\n");
    } else {
        printf("%lld\n", sum);
    }
    return 0;
}

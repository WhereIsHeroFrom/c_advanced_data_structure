#include <stdio.h>
#include <string.h>

//////////////////////并查集模板(路径压缩)//////////////////////

// 并：合并
// 查：查找
// 集：集合

#define maxn 200010

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


int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int count = n;
    UFSet uf;
    UFSet_Init(&uf, n);
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (UFSet_Union(&uf, a, b)) {
            count--;
        }
    }
    if (count <= 3) {
        printf("0\n");
    } else {
        printf("%d\n", count - 3);
    }
    return 0;
}

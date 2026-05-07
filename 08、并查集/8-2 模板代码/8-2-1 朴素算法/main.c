#include <stdio.h>
#include <string.h>

// P3367 【模板】并查集
// https://www.luogu.com.cn/problem/P3367

// 并：合并
// 查：查找
// 集：集合

#define maxn 200010

typedef struct {
    int set[maxn];
    int n;
} UFSet;

void UFSet_Init(UFSet* uf, int n) {
    uf->n = n;
    for (int i = 1; i <= n; ++i) {
        uf->set[i] = i;
    }
}

int UFSet_Find(UFSet* uf, int id) {
    return uf->set[id];
}

int UFSet_Union(UFSet* uf, int id1, int id2) {
    int s1 = UFSet_Find(uf, id1);
    int s2 = UFSet_Find(uf, id2);
    if (s1 == s2) {
        return 0;
    }
    for (int i = 1; i <= uf->n; ++i) {
        if (uf->set[i] == s1) {
            uf->set[i] = s2;
        }
    }
    return 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    UFSet uf;
    UFSet_Init(&uf, n);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a == 1) {
            UFSet_Union(&uf, b, c);
        } else {
            if (UFSet_Find(&uf, b) == UFSet_Find(&uf, c)) {
                printf("Y\n");
            } else {
                printf("N\n");
            }
        }
    }
    return 0;
}

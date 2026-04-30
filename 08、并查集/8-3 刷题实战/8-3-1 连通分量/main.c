#include <stdio.h>
#include <string.h>

#define maxn 100010

int far[maxn];

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
    int count = n;
    UFSet_Init(n);
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (UFSet_Union(a, b)) {
            count--;
        }
    }
    printf("%d\n", count);
    return 0;
}
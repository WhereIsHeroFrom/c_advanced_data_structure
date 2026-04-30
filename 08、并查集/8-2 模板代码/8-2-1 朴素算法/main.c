#include <stdio.h>
#include <string.h>

#define maxn 100010

int set[maxn];

void UFSet_Init(int n) {
    for (int i = 1; i <= n; ++i) {
        set[i] = i;
    }
}

int UFSet_Find(int id) {
    return set[id];
}

int UFSet_Union(int id1, int id2, int n) {
    int s1 = UFSet_Find(id1);
    int s2 = UFSet_Find(id2);
    if (s1 == s2) {
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        if (set[i] == s1) {
            set[i] = s2;
        }
    }
    return 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    UFSet_Init(n);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a == 1) {
            UFSet_Union(b, c, n);
        } else {
            if (UFSet_Find(b) == UFSet_Find(c)) {
                printf("Y\n");
            } else {
                printf("N\n");
            }
        }
    }
    return 0;
}
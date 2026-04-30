#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 100010

typedef struct {
    int to;
    int weight;
    int next;
} Edge;

Edge edges[maxn];
int head[maxn];
int edge_count;
int visited[maxn];

void Graph_Init(int n) {
    edge_count = 0;
    memset(head, -1, sizeof(head[0]) * n);
}

void Graph_AddEdge(int from, int to, int weight) {
    edges[edge_count].to = to;
    edges[edge_count].weight = weight;
    edges[edge_count].next = head[from];
    head[from] = edge_count++;
}

void dfs(int u, int* ans) {
    if (visited[u]) {
        return;
    }
    visited[u] = 1;
    if (u > *ans) {
        *ans = u;
    }
    for (int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].to;
        dfs(v, ans);
    }
}

int Graph_CaculateColor(int n, int u) {
    memset(visited, 0, sizeof(visited[0]) * n);
    int ans = u;
    dfs(u, &ans);
    return ans;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Graph_Init(n);
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        Graph_AddEdge(a, b, 0);
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", Graph_CaculateColor(n, i) + 1);
    }
    printf("\n");
    return 0;
}
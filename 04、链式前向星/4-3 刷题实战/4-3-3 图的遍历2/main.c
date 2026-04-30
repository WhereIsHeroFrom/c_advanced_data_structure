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
int colors[maxn];

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

void dfs(int u, int color) {
    if (colors[u] != -1) {
        return;
    }
    colors[u] = color;
    for (int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].to;
        dfs(v, color);
    }
}

void Graph_CaculateColors(int n) {
    memset(colors, -1, sizeof(colors[0]) * n);
    for (int i = n - 1; i >= 0; --i) {
        if (colors[i] == -1) {
            dfs(i, i);
        }
    }
}

int Graph_GetColor(int v) {
    return colors[v];
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
        Graph_AddEdge(b, a, 0);
    }
    Graph_CaculateColors(n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", Graph_GetColor(i) + 1);
    }
    printf("\n");
    return 0;
}
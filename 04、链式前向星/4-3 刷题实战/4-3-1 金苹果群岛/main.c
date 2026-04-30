#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 100010

typedef struct {
    int to;
    int weight;
    int next;
} Edge;

Edge edges[maxn * 2];
int head[maxn];
int edge_count;
int colors[maxn];
int count;

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

void dfs(int u) {
    if (colors[u] != -1) {
        return;
    }
    colors[u] = count;
    for (int e = head[u]; e != -1; e = edges[e].next) {
        dfs(edges[e].to);
    }
}

int Graph_CountConnectedBlock(int n) {
    count = 0;
    memset(colors, -1, sizeof(colors[0]) * n);
    for (int i = 0; i < n; ++i) {
        if (colors[i] == -1) {
            dfs(i);
            count++;
        }
    }
    return count;
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
        Graph_AddEdge(b, a, 0);
    }
    printf("%d\n", Graph_CountConnectedBlock(n) - 1);
    return 0;
}
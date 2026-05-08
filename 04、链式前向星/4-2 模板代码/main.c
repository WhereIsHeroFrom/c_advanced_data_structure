#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////C链式前向星模板////////////////////////

#define maxn 100010
#define maxm 200010

typedef struct {
    int to;
    int weight;
    int next;
} Edge;

typedef struct {
    Edge edges[maxm];
    int head[maxn];
    int edge_count;
    int n;
} Graph;

void Graph_Init(Graph* g, int n) {
    g->n = n;
    g->edge_count = 0;
    memset(g->head, -1, sizeof(g->head[0]) * n);
}

void Graph_AddEdge(Graph* g, int from, int to, int weight) {
    g->edges[g->edge_count].to = to;
    g->edges[g->edge_count].weight = weight;
    g->edges[g->edge_count].next = g->head[from];
    g->head[from] = g->edge_count++;
}

void Graph_PrintEdges(Graph* g) {
    for (int i = 0; i < g->n; ++i) {
        printf("%d:", i);
        for (int e = g->head[i]; e != -1; e = g->edges[e].next) {
            int v = g->edges[e].to;
            int w = g->edges[e].weight;
            printf("(%d,%d)", v, w);
        }
        printf("\n");
    }
}

////////////////////////C链式前向星模板////////////////////////

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Graph g;
    Graph_Init(&g, n);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Graph_AddEdge(&g, a, b, c);
    }
    Graph_PrintEdges(&g);
    return 0;
}

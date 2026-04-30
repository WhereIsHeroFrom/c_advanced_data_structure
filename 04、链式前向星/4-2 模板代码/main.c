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

void Graph_PrintEdges(int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d:", i);
        for (int e = head[i]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            printf("(%d,%d)", v, w);
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Graph_Init(n);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Graph_AddEdge(a, b, c);
    }
    Graph_PrintEdges(n);
    return 0;
}
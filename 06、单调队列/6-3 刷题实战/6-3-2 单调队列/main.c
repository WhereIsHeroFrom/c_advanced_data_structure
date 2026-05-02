#include <stdio.h>

/////////////////////////////单调队列模板/////////////////////////////
#define type int
#define maxn 1000001
typedef int (* cmp_t)(type a, type b);

typedef struct {
    int data[maxn];
    int front;
    int rear;
} MonotonicQueue;

// <  单调递增队列(队首->队尾)：1 2 3 4 5
int cmpLT(type a, type b) {
    return a < b;
}
// <= 单调不减队列(队首->队尾)：2 2 3 3 4
int cmpLE(type a, type b) {
    return a <= b;
}
// >  单调递减队列(队首->队尾)：6 5 4 3 2
int cmpGT(type a, type b) {
    return a > b;
}
// >= 单调不增队列(队首->队尾): 6 6 5 4 3
int cmpGE(type a, type b) {
    return a >= b;
}

// ans[i] 代表 [i-k+1, i] 中，最大值或最小值的下标
// cmpGT :  存储最大值的下标
// cmpLT :  存储最小值的下标
void findIntervalMinMax(MonotonicQueue *que, 
    int n, int k, type h[], int ans[], cmp_t cmp) {
    que->front = que->rear = 0;
    for (int i = 1; i <= n; ++i) {
        while (que->rear > que->front && !cmp(h[que->data[que->rear - 1]], h[i])) {
            que->rear--;
        }
        que->data[que->rear++] = i;
        while (que->data[que->rear - 1] - que->data[que->front] + 1 > k) {
            que->front++;
        }
        ans[i] = h[que->data[que->front]];
    }
}
/////////////////////////////单调队列模板/////////////////////////////

MonotonicQueue que;
type h[maxn];
int ans[maxn];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
    }
    findIntervalMinMax(&que, n, k, h, ans, cmpLT);
    for (int i = k; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    findIntervalMinMax(&que, n, k, h, ans, cmpGT);
    for (int i = k; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
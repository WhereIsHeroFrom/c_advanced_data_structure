#include <stdio.h>
#include <stdlib.h>

#define maxn 1000001

long long tree[4 * maxn];
long long lazy[4 * maxn];
long long arr[maxn];
int n;

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    build(leftChild, start, mid);
    build(rightChild, mid + 1, end);
    tree[node] = tree[leftChild] + tree[rightChild];
}

void pushDown(int node, int start, int end) {
    if (lazy[node] != 0) {
        int mid = (start + end) / 2;
        int leftChild = node * 2 + 1;
        int rightChild = node * 2 + 2;
        tree[leftChild] += lazy[node] * (mid - start + 1);
        tree[rightChild] += lazy[node] * (end - mid);
        lazy[leftChild] += lazy[node];
        lazy[rightChild] += lazy[node];
        lazy[node] = 0;
    }
}

void updateRange(int node, int start, int end, int l, int r, long long val) {
    if (start > r || end < l) return;
    if (start >= l && end <= r) {
        tree[node] += val * (end - start + 1);
        lazy[node] += val;
        return;
    }
    pushDown(node, start, end);
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    updateRange(leftChild, start, mid, l, r, val);
    updateRange(rightChild, mid + 1, end, l, r, val);
    tree[node] = tree[leftChild] + tree[rightChild];
}

long long queryRange(int node, int start, int end, int l, int r) {
    if (start > r || end < l) return 0;
    if (start >= l && end <= r) {
        return tree[node];
    }
    pushDown(node, start, end);
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    long long leftSum = queryRange(leftChild, start, mid, l, r);
    long long rightSum = queryRange(rightChild, mid + 1, end, l, r);
    return leftSum + rightSum;
}

void SegmentTree_Init() {
    build(0, 0, n - 1);
}

void SegmentTree_Update(int l, int r, long long val) {
    updateRange(0, 0, n - 1, l, r, val);
}

long long SegmentTree_Query(int l, int r) {
    return queryRange(0, 0, n - 1, l, r);
}

int main() {
    int m;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }
    SegmentTree_Init();
    scanf("%d", &m);
    while (m--) {
        int z, x, y;
        scanf("%d %d %d", &z, &x, &y);
        if (z == 1) {
            x--;
            SegmentTree_Update(x, x, y);
        } else {
            x--;
            y--;
            printf("%lld\n", SegmentTree_Query(x, y));
        }
    }
    return 0;
}
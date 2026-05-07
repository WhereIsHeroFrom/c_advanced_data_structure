#include <stdio.h>
#include <stdlib.h>



/////////////////////////线段树模板(区间求和)/////////////////////////
#define type long long
#define maxn 100001

typedef struct {
    type tree[4 * maxn];
    type lazy[4 * maxn];
    type arr[maxn];
    int n;
} SegmentTree;

void build(SegmentTree* st, int node, int start, int end) {
    if (start == end) {
        st->tree[node] = st->arr[start];
        return;
    }
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    build(st, leftChild, start, mid);
    build(st, rightChild, mid + 1, end);
    st->tree[node] = st->tree[leftChild] + st->tree[rightChild];
}

void pushDown(SegmentTree* st, int node, int start, int end) {
    if (st->lazy[node] != 0) {
        int mid = (start + end) / 2;
        int leftChild = node * 2 + 1;
        int rightChild = node * 2 + 2;
        st->tree[leftChild] += st->lazy[node] * (mid - start + 1);
        st->tree[rightChild] += st->lazy[node] * (end - mid);
        st->lazy[leftChild] += st->lazy[node];
        st->lazy[rightChild] += st->lazy[node];
        st->lazy[node] = 0;
    }
}

void updateRange(SegmentTree* st, int node, int start, int end, int l, int r, type val) {
    if (start > r || end < l) return;
    if (start >= l && end <= r) {
        st->tree[node] += val * (end - start + 1);
        st->lazy[node] += val;
        return;
    }
    pushDown(st, node, start, end);
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    updateRange(st, leftChild, start, mid, l, r, val);
    updateRange(st, rightChild, mid + 1, end, l, r, val);
    st->tree[node] = st->tree[leftChild] + st->tree[rightChild];
}

type queryRange(SegmentTree* st, int node, int start, int end, int l, int r) {
    if (start > r || end < l) return 0;
    if (start >= l && end <= r) {
        return st->tree[node];
    }
    pushDown(st, node, start, end);
    int mid = (start + end) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    type leftSum = queryRange(st, leftChild, start, mid, l, r);
    type rightSum = queryRange(st, rightChild, mid + 1, end, l, r);
    return leftSum + rightSum;
}

void SegmentTree_Init(SegmentTree* st, int n, type* arr) {
    st->n = n;
    for (int i = 0; i < n; ++i) {
        st->arr[i] = arr[i];
    }
    for (int i = 0; i < 4 * n; ++i) {
        st->tree[i] = 0;
        st->lazy[i] = 0;
    }
    build(st, 0, 0, n - 1);
}

void SegmentTree_Update(SegmentTree* st, int l, int r, type val) {
    updateRange(st, 0, 0, st->n - 1, l, r, val);
}

type SegmentTree_Query(SegmentTree* st, int l, int r) {
    return queryRange(st, 0, 0, st->n - 1, l, r);
}
/////////////////////////线段树模板(区间求和)/////////////////////////

SegmentTree st;


int main() {
    int n, m;
    scanf("%d", &n);
    type arr[maxn];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }
    scanf("%d", &m);
    SegmentTree_Init(&st, n, arr);
    while (m--) {
        int z, x, y;
        scanf("%d %d %d", &z, &x, &y);
        if (z == 1) {
            --x;
            SegmentTree_Update(&st, x, x, y);
        } else {
            --x;
            --y;
            printf("%lld\n", SegmentTree_Query(&st, x, y));
        }
    }
    return 0;
}

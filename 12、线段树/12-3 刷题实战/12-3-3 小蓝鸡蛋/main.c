#include <stdio.h>

//////////////////////////线段树模板(区间求和)//////////////////////////

#define type long long
#define maxn 200010

typedef struct {
    type tree[maxn * 4];
    type lazy[maxn * 4];
    type arr[maxn];
    int n;
} SegmentTree;

void build(SegmentTree *st, int node, int start, int end) { 
    if(start == end) {
        st->tree[node] = st->arr[start];
        return ;
    }
    int mid = (start + end) >> 1;
    int leftChild = node * 2 + 1;
    int rightChild = leftChild + 1;
    build(st, leftChild, start, mid);
    build(st, rightChild, mid+1, end);
    st->tree[node] = st->tree[leftChild] + st->tree[rightChild];
}

void pushDown(SegmentTree *st, int node, int start, int end) {
    if( st->lazy[node] ) {
        int mid = (start + end) >> 1;
        int leftChild = node * 2 + 1;
        int rightChild = leftChild + 1;
        st->tree[leftChild] += st->lazy[node]  * (mid - start + 1);
        st->tree[rightChild] += st->lazy[node] * (end - mid);

        st->lazy[leftChild] += st->lazy[node];
        st->lazy[rightChild] += st->lazy[node];

        st->lazy[node] = 0;
    }
}

void updateRange(SegmentTree *st, int node, int start, int end, int l, int r, type val) {
    if(start > r || end < l) {
        return ;
    }
    // l      start    end      r
    if(start >= l && end <= r) {
        st->tree[node] += val * (end - start + 1);
        st->lazy[node] += val;
        return ;
    }
    pushDown(st, node, start, end);
    int mid = (start + end) >> 1;
    int leftChild = node * 2 + 1;
    int rightChild = leftChild + 1;
    updateRange(st, leftChild, start, mid, l, r, val);
    updateRange(st, rightChild, mid+1, end, l, r, val);
    st->tree[node] = st->tree[leftChild] + st->tree[rightChild];
}

type queryRange(SegmentTree *st, int node, int start, int end, int l, int r) {
    if(start > r || end < l) {
        return 0;
    }
    // l      start    end      r
    if(start >= l && end <= r) {
        return st->tree[node];
    }
    pushDown(st, node, start, end);
    int mid = (start + end) >> 1;
    int leftChild = node * 2 + 1;
    int rightChild = leftChild + 1;
    type lsum = queryRange(st, leftChild, start, mid, l, r);
    type rsum = queryRange(st, rightChild, mid+1, end, l, r);
    return lsum + rsum;
}


void SegmentTree_Init(SegmentTree *st, int n, type* arr) {
    st->n = n;
    for(int i = 0; i < n; ++i) {
        st->arr[i] = arr[i];
    }
    for(int i = 0; i < n * 4; ++i) {
        st->tree[i] = 0;
        st->lazy[i] = 0;
    }
    build(st, 0, 0, n-1);
}

void SegmentTree_Update(SegmentTree *st, int l, int r, type val) {
    updateRange(st, 0, 0, st->n-1, l, r, val);
}

type SegmentTree_Query(SegmentTree *st, int l, int r) {
    return queryRange(st, 0, 0, st->n-1, l, r);
}
//////////////////////////线段树模板(区间求和)//////////////////////////
SegmentTree st;
type a[maxn];

int main() {
    int n, m;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    scanf("%d", &m);
    SegmentTree_Init(&st, n, a);
    while(m--) {
        int z, x, y;
        scanf("%d %d %d", &z, &x, &y);
        x -= 1;
        if(z == 1) {
            SegmentTree_Update(&st, x, x, y);
        }else {
            y -= 1;
            type ans = SegmentTree_Query(&st, x, y);
            printf("%lld\n", ans);
        }
    }
    return 0;
}

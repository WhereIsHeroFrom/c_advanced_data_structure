/*
用大顶堆来维护一个递减序列
sum 维护堆中所有元素的和
对于模数 x
每次弹出所有 >= x 的元素
（
为什么弹出 >= x 的元素
因为这是一个顶堆
弹出的元素一定比堆中所有元素都要大
所以如果某个堆顶元素 < x
那么所有堆中元素堆 x 取模的值都是元素本身
也就是这个 sum 值
所以不需要再弹出来
）
把弹出元素取模以后再放回堆中
并且同时维护 sum 的值
*/

#include <stdio.h>

/////////////////////////////二叉堆模板/////////////////////////////
#define type int
#define maxn 100010
typedef int (* cmp_t)(type a, type b);

typedef struct {
    type data[maxn];
    int size;
    cmp_t cmp;
} Heap;

int Heap_CmpGreater(type a, type b) {
    return a > b;
}

int Heap_CmpLess(type a, type b) {
    return a < b;
}

int lson(int idx) {
    return 2 * idx + 1;
}

int rson(int idx) {
    return 2 * idx + 2;
}

int parent(int idx) {
    return (idx - 1) / 2;
}

void swap(type* a, type* b) {
    type tmp = *a;
    *a = *b;
    *b = tmp;
}

void shiftUp(Heap* heap, int curr) {
    if (curr == 0) return;
    int par = parent(curr);
    if (heap->cmp(heap->data[curr], heap->data[par])) {
        swap(&heap->data[curr], &heap->data[par]);
        shiftUp(heap, par);
    }
}

void shiftDown(Heap* heap, int curr) {
    int lson_id = lson(curr);
    int rson_id = rson(curr);
    int opt_id = curr;
    if (lson_id < heap->size && heap->cmp(heap->data[lson_id], heap->data[opt_id])) {
        opt_id = lson_id;
    }
    if (rson_id < heap->size && heap->cmp(heap->data[rson_id], heap->data[opt_id])) {
        opt_id = rson_id;
    }
    if (opt_id != curr) {
        swap(&heap->data[curr], &heap->data[opt_id]);
        shiftDown(heap, opt_id);
    }
}

void Heap_Init(Heap* heap, cmp_t cmp) {
    heap->size = 0;
    heap->cmp = cmp;
}

void Heap_Push(Heap* heap, type val) {
    heap->data[heap->size++] = val;
    shiftUp(heap, heap->size - 1);
}

void Heap_Pop(Heap* heap) {
    swap(&heap->data[0], &heap->data[heap->size - 1]);
    heap->size--;
    shiftDown(heap, 0);
}

type Heap_Top(Heap* heap) {
    return heap->data[0];
}

int Heap_Empty(Heap* heap) {
    return heap->size == 0;
}
/////////////////////////////二叉堆模板/////////////////////////////
Heap heap;

int main() {
    Heap_Init(&heap, Heap_CmpGreater);
    int n, k;
    long long sum = 0;
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        Heap_Push(&heap, x);
        sum += x;
    }
    while(k--) {
        int x;
        scanf("%d", &x);
        while( !Heap_Empty(&heap) ) {
            if( Heap_Top(&heap) >= x ) {
                sum -= Heap_Top(&heap);
                int y = Heap_Top(&heap) % x;
                sum += y;
                Heap_Pop(&heap);
                Heap_Push(&heap, y);
            }else break;
        }
        printf("%lld ", sum);
    }
    printf("\n");
    return 0;
}
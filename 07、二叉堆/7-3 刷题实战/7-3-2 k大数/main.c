/*
1 2 3 4 5 6 7 8 9

建立一个小顶堆
并且始终保持堆的大小是 n
那么堆顶元素就是第 n 大的
n=9 第n大的数 = 1

分情况讨论
插入的元素比堆顶的元素的关系
1、<= 堆顶
2、>  堆顶
因为没有删除操作
所以如果一个元素 <= 堆顶元素
那么根本不需要插入堆中
会破坏原有堆的性质
因为要保证堆的元素始终是 n 个
只有当 > 堆顶元素的时候
把它插进去并且把堆顶元素删除
因为现在是 n+1 个元素
所以堆顶是第 n+1 大的那个
而这个元素以后再也不会被用到
所以直接删除
那么这时候堆顶的元素就是第 n 大的
所有操作都是 O(1) 的
*/
#include <stdio.h>

/////////////////////////////二叉堆模板/////////////////////////////
#define maxn 100010
typedef int (* cmp_t)(int a, int b);

typedef struct {
    int data[maxn];
    int size;
    cmp_t cmp;
} Heap;

// 大顶堆
int Heap_CmpGreater(int a, int b) {
    return a > b;
}

// 小顶堆
int Heap_CmpLess(int a, int b) {
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

void swap(int* a, int* b) {
    int tmp = *a;
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
    if (lson_id < heap->size && \
        heap->cmp(heap->data[lson_id], heap->data[opt_id])) {
        opt_id = lson_id;
    }
    if (rson_id < heap->size && \
        heap->cmp(heap->data[rson_id], heap->data[opt_id])) {
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

void Heap_Push(Heap* heap, int val) {
    heap->data[heap->size++] = val;
    shiftUp(heap, heap->size - 1);
}

void Heap_Pop(Heap* heap) {
    swap(&heap->data[0], &heap->data[heap->size - 1]);
    heap->size--;
    shiftDown(heap, 0);
}

int Heap_Top(Heap* heap) {
    return heap->data[0];
}

int Heap_Empty(Heap* heap) {
    return heap->size == 0;
}
/////////////////////////////二叉堆模板/////////////////////////////
Heap heap;

int main() {
    Heap_Init(&heap, Heap_CmpLess);
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        Heap_Push(&heap, x);
    }
    for (int i = 0; i < k; ++i) {
        int x;
        scanf("%d", &x);
        if (x > Heap_Top(&heap)) {
            Heap_Push(&heap, x);
            Heap_Pop(&heap);
        }
        printf("%d ", Heap_Top(&heap));
    }
    printf("\n");
    return 0;
}
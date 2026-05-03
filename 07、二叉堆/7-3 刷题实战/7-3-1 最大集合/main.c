/*
首先看到求最大的数，我们首先想到的就是 大顶堆
那么假设有一个堆 heap
往里面不断压入元素
heap: 6 7 4 2 1 5 7
如果没有加减的操作
那么每次弹出的堆顶元素就是最大值
但是要把堆中的每个元素都加上x或者减去x
这个操作对于堆来说是不支持的
所以可以采用一个额外的变量 sum
所有的加减操作都是在这个sum上进行
比如往堆中按顺序压入
5 6 7 3 2
然后突然进行了一些加减操作
+x -y +z -w
这些元素的和我们可以用一个变量 sum 表示
你就可以想象成这个sum累加到了堆中的元素的每一项上
但是实际上并没有加上（因为堆不支持这个操作）
当我弹出一个堆顶元素的时候
实际的值其实就是 堆顶元素 + sum
这样一来，2 3 4 的操作的时间复杂度
就都是 O(logn) 的了

再来看第一个操作
如果目前 sum 不等于 0
然后我往堆里压入一个元素 x
弹出的时候，根据我们的要求它是 x + sum
你会发现 压入 和 弹出 的值不匹配
多 sum 这部分
原因是 这个 sum 是在压入元素之前累加上的
x 本身并没有享受到这个 sum 的加成
所以只有在压入 x 以后产生的 sum 
才需要在弹出的时候累加上

那我们是否需要多个 sum 呢？

不需要

我只需要在进入堆的时候
把实际要压入的值变成 x - sum
这样一来
弹出的时候，其实就是 (x - sum) + sum
就得到了原值 x
这样操作 1 也变成 O(logn)
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
    Heap_Init(&heap, Heap_CmpGreater);
    int n, k;
    int sum = 0;
    scanf("%d %d", &n, &k);
    Heap_Push(&heap, k);
    while(n--) {
        int a;
        scanf("%d", &a);
        if(a == 4) {
            printf("%d\n", Heap_Top(&heap) + sum);
            Heap_Pop(&heap);
        } else {
            int x;
            scanf("%d", &x);
            if(a == 1) {
                Heap_Push(&heap, x - sum);
            }else if(a == 2) {
                sum += x;
            }else {
                sum -= x;
            }
        }

    }
    return 0;
}

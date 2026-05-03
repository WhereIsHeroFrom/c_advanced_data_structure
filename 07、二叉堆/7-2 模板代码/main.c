#include <stdio.h>

/////////////////////////////¶þ²æ¶ÑÄ£°å/////////////////////////////
#define maxn 100010
typedef int (* cmp_t)(int a, int b);

typedef struct {
    int data[maxn];
    int size;
    cmp_t cmp;
} Heap;

// ´ó¶¥¶Ñ
int Heap_CmpGreater(int a, int b) {
    return a > b;
}

// Ð¡¶¥¶Ñ
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
/////////////////////////////¶þ²æ¶ÑÄ£°å/////////////////////////////
Heap heap;

int main() {    
    Heap_Init(&heap, Heap_CmpGreater);
    printf("push :");
    for (int i = 0; i < 5; ++i) {
        int x = rand() % 30, y = rand() % 30;
        Heap_Push(&heap, x);
        printf("%d ", x);
    }
    printf("\n");

    printf("top :");
    while (!Heap_Empty(&heap)) {
        printf("%d ", Heap_Top(&heap));
        Heap_Pop(&heap);
    }
    printf("\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define maxn 100010

typedef struct {
    int data[maxn];
    int size;
} Heap;

int Heap_CmpGreater(int a, int b) {
    return a > b;
}

int Heap_CmpLess(int a, int b) {
    return a < b;
}

int Heap_Lson(int idx) {
    return 2 * idx + 1;
}

int Heap_Rson(int idx) {
    return 2 * idx + 2;
}

int Heap_Parent(int idx) {
    return (idx - 1) / 2;
}

void Heap_Swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Heap_ShiftUp(Heap* heap, int curr, int (*cmp)(int, int)) {
    if (curr == 0) return;
    int par = Heap_Parent(curr);
    if (cmp(heap->data[curr], heap->data[par])) {
        Heap_Swap(&heap->data[curr], &heap->data[par]);
        Heap_ShiftUp(heap, par, cmp);
    }
}

void Heap_ShiftDown(Heap* heap, int curr, int (*cmp)(int, int)) {
    int lson_id = Heap_Lson(curr);
    int rson_id = Heap_Rson(curr);
    int opt_id = curr;
    if (lson_id < heap->size && cmp(heap->data[lson_id], heap->data[opt_id])) {
        opt_id = lson_id;
    }
    if (rson_id < heap->size && cmp(heap->data[rson_id], heap->data[opt_id])) {
        opt_id = rson_id;
    }
    if (opt_id != curr) {
        Heap_Swap(&heap->data[curr], &heap->data[opt_id]);
        Heap_ShiftDown(heap, opt_id, cmp);
    }
}

void Heap_Init(Heap* heap) {
    heap->size = 0;
}

void Heap_Push(Heap* heap, int val, int (*cmp)(int, int)) {
    heap->data[heap->size++] = val;
    Heap_ShiftUp(heap, heap->size - 1, cmp);
}

void Heap_Pop(Heap* heap, int (*cmp)(int, int)) {
    Heap_Swap(&heap->data[0], &heap->data[heap->size - 1]);
    heap->size--;
    Heap_ShiftDown(heap, 0, cmp);
}

int Heap_Top(Heap* heap) {
    return heap->data[0];
}

void Heap_Clear(Heap* heap) {
    heap->size = 0;
}

int main() {
    Heap heap;
    Heap_Init(&heap);
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        Heap_Push(&heap, x, Heap_CmpLess);
    }
    for (int i = 0; i < k; ++i) {
        int x;
        scanf("%d", &x);
        if (x > Heap_Top(&heap)) {
            Heap_Push(&heap, x, Heap_CmpLess);
            Heap_Pop(&heap, Heap_CmpLess);
        }
        printf("%d ", Heap_Top(&heap));
    }
    printf("\n");
    return 0;
}
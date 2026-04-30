#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* dummy_head;
    int size;
} DoublyLinkedList;

Node* Node_Create(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void Node_Destroy(Node* node) {
    free(node);
}

void DoublyLinkedList_Init(DoublyLinkedList* list) {
    list->size = 0;
    list->dummy_head = Node_Create(0);
    list->dummy_head->prev = list->dummy_head;
    list->dummy_head->next = list->dummy_head;
}

void DoublyLinkedList_Destroy(DoublyLinkedList* list) {
    while (list->size > 0) {
        Node* next = list->dummy_head->next->next;
        Node_Destroy(list->dummy_head->next);
        list->dummy_head->next = next;
        list->size--;
    }
    Node_Destroy(list->dummy_head);
    list->dummy_head = NULL;
}

void DoublyLinkedList_PushFront(DoublyLinkedList* list, int value) {
    Node* new_node = Node_Create(value);
    new_node->prev = list->dummy_head;
    new_node->next = list->dummy_head->next;
    list->dummy_head->next->prev = new_node;
    list->dummy_head->next = new_node;
    list->size++;
}

void DoublyLinkedList_PushBack(DoublyLinkedList* list, int value) {
    Node* new_node = Node_Create(value);
    new_node->prev = list->dummy_head->prev;
    new_node->next = list->dummy_head;
    list->dummy_head->prev->next = new_node;
    list->dummy_head->prev = new_node;
    list->size++;
}

void DoublyLinkedList_DeleteNode(DoublyLinkedList* list, Node* node) {
    if (node == NULL || node == list->dummy_head) {
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    Node_Destroy(node);
    list->size--;
}

Node* DoublyLinkedList_Find(const DoublyLinkedList* list, int value) {
    Node* curr = list->dummy_head->next;
    while (curr != list->dummy_head) {
        if (curr->data == value) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void DoublyLinkedList_Print(const DoublyLinkedList* list) {
    Node* curr = list->dummy_head->next;
    while (curr != list->dummy_head) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    DoublyLinkedList dll;
    DoublyLinkedList_Init(&dll);
    
    for (int i = 1; i <= 10; ++i) {
        DoublyLinkedList_PushBack(&dll, i);
    }
    
    int n;
    scanf("%d", &n);
    while (n--) {
        int x;
        scanf("%d", &x);
        Node* nd = DoublyLinkedList_Find(&dll, x);
        if (nd != NULL) {
            nd->prev->next = nd->next;
            nd->next->prev = nd->prev;
            nd->prev = dll.dummy_head;
            nd->next = dll.dummy_head->next;
            dll.dummy_head->next->prev = nd;
            dll.dummy_head->next = nd;
        }
        DoublyLinkedList_Print(&dll);
    }
    
    DoublyLinkedList_Destroy(&dll);
    return 0;
}
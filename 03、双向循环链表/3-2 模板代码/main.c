#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void DoublyLinkedList_InsertAfter(DoublyLinkedList* list, Node* node, int value) {
    if (node == NULL || node == list->dummy_head) {
        return;
    }
    Node* new_node = Node_Create(value);
    new_node->prev = node;
    new_node->next = node->next;
    node->next->prev = new_node;
    node->next = new_node;
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

void DoublyLinkedList_Modify(Node* node, int value) {
    if (node == NULL) {
        return;
    }
    node->data = value;
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

int DoublyLinkedList_Size(const DoublyLinkedList* list) {
    return list->size;
}

int DoublyLinkedList_Empty(const DoublyLinkedList* list) {
    return list->size == 0;
}

int main() {
    DoublyLinkedList dll;
    DoublyLinkedList_Init(&dll);
    
    DoublyLinkedList_PushBack(&dll, 'i');
    DoublyLinkedList_Print(&dll);
    DoublyLinkedList_PushBack(&dll, 'c');
    DoublyLinkedList_Print(&dll);
    DoublyLinkedList_PushBack(&dll, 'p');
    DoublyLinkedList_Print(&dll);
    DoublyLinkedList_PushBack(&dll, 'c');
    DoublyLinkedList_Print(&dll);

    DoublyLinkedList_PushFront(&dll, 'm');
    DoublyLinkedList_Print(&dll);
    DoublyLinkedList_PushFront(&dll, 'a');
    DoublyLinkedList_Print(&dll);

    Node* nd = DoublyLinkedList_Find(&dll, 'a');
    DoublyLinkedList_InsertAfter(&dll, nd, 'c');
    DoublyLinkedList_Print(&dll);
    
    nd = DoublyLinkedList_Find(&dll, 'm');
    DoublyLinkedList_InsertAfter(&dll, nd, '/');
    DoublyLinkedList_Print(&dll);

    nd = DoublyLinkedList_Find(&dll, 'i');
    DoublyLinkedList_Modify(nd, 'c');
    DoublyLinkedList_Print(&dll);

    nd = DoublyLinkedList_Find(&dll, 'm');
    DoublyLinkedList_DeleteNode(&dll, nd);
    DoublyLinkedList_Print(&dll);

    printf("%d\n", DoublyLinkedList_Empty(&dll));
    printf("%d\n", DoublyLinkedList_Size(&dll));

    DoublyLinkedList_Destroy(&dll);
    return 0;
}
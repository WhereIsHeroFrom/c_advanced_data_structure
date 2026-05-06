#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////×ÖµäÊ÷Ä£°å(Ç°×ºÅÐ¶¨)/////////////////////////

#define ALPHABET_SIZE 62
#define type int

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
    int count;
    type val;
} TrieNode;

TrieNode* TrieNode_Create() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        node->children[i] = NULL;
    }
    node->isEndOfWord = 0;
    node->count = 0;
    node->val = 0;
    return node;
}

void TrieNode_Delete(TrieNode* node) {
    if (node == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        TrieNode_Delete(node->children[i]);
    }
    free(node);
}

int trieIndex(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 26;
    }
    return c - '0' + 52;
}

void Trie_Insert(TrieNode* root, const char* key, type val) {
    TrieNode* node = root;
    for (int i = 0; key[i] != '\0'; ++i) {
        int index = trieIndex(key[i]);
        if (node->children[index] == NULL) {
            node->children[index] = TrieNode_Create();
        }
        node = node->children[index];
        node->count++;
    }
    node->isEndOfWord = 1;
    node->val = val;
}

int Trie_Search(TrieNode* root, const char* key, type* val) {
    TrieNode* node = root;
    for (int i = 0; key[i] != '\0'; ++i) {
        int index = trieIndex(key[i]);
        if (node->children[index] == NULL) {
            return 0;
        }
        node = node->children[index];
    }
    if (node->isEndOfWord) {
        *val = node->val;
        return 1;
    }
    return 0;
}

int Trie_QueryPrefixCount(TrieNode* root, const char* prefix) {
    TrieNode* node = root;
    for (int i = 0; prefix[i] != '\0'; ++i) {
        int index = trieIndex(prefix[i]);
        if (node->children[index] == NULL) {
            return 0;
        }
        node = node->children[index];
    }
    return node->count;
}
/////////////////////////×ÖµäÊ÷Ä£°å(Ç°×ºÅÐ¶¨)/////////////////////////

int Trie_QueryMaxPrefix(TrieNode* root, const char* prefix) {
    TrieNode* node = root;
    int maxLen = 0;
    for (int i = 0; prefix[i] != '\0'; ++i) {
        int index = trieIndex(prefix[i]);
        if (node->children[index] == NULL) {
            break;
        }
        node = node->children[index];
        if (node->count > 1) {
            maxLen = i + 1;
        }
    }
    return maxLen;
}

char str[1000100];

int main() {
    int n;
    scanf("%d", &n);
    TrieNode* root = TrieNode_Create();
    int pos = 0;
    char* p = str;
    for (int i = 0; i < n; ++i) {
        scanf("%s", p);
        Trie_Insert(root, p, 1);
        p = p + strlen(p) + 1;
    }
    p = str;
    for (int i = 0; i < n; ++i) {
        printf("%d\n", Trie_QueryMaxPrefix(root, p));
        p = p + strlen(p) + 1;
    }
    TrieNode_Delete(root);
    return 0;
}
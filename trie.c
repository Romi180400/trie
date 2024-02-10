#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRIE_BASE_CHAR ' '
#define ALPHABET_SIZE 95

typedef struct line_list {
    int line;
    struct line_list *next;
} LineList;

typedef struct trie_node {
    LineList *lines;
    struct trie_node *children[ALPHABET_SIZE];
} TrieNode;

TrieNode *createTrieNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node) {
        int i;
        node->lines = NULL;
        for (i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

LineList *addLine(LineList *list, int line) {
    LineList *newNode = (LineList *)malloc(sizeof(LineList));
    if (newNode) {
        newNode->line = line;
        newNode->next = list;
        return newNode;
    }
    return list;
}

void insertWord(TrieNode *root, const char *word, int line) {
    TrieNode *current = root;
    while (*word) {
        if (!current->children[*word - TRIE_BASE_CHAR]) {
            current->children[*word - TRIE_BASE_CHAR] = createTrieNode();
        }
        current = current->children[*word - TRIE_BASE_CHAR];
        word++;
    }

    current->lines = addLine(current->lines, line);
}

void printTrie(TrieNode *node, char *prefix, int level) {
    int i;
    LineList *cur;

    if (node == NULL) return;
    if (node->lines != NULL) {
        prefix[level] = '\0';
        printf("%s lines in appears ", prefix);

        cur = node->lines;
        while (cur != NULL) {
            printf("%d%s", cur->line, cur->next ? ", " : "\n");
            cur = cur->next;
        }
    }

    i = 0;
    while (i < ALPHABET_SIZE) {
        if (node->children[i] != NULL) {
            prefix[level] = i + TRIE_BASE_CHAR;
            printTrie(node->children[i], prefix, level + 1);
        }
        i++;
    }
}

void freeTrie(TrieNode *node) {
    int i;

    if (!node) return;

    i = 0;
    while (i < ALPHABET_SIZE) {
        if (node->children[i]) {
            freeTrie(node->children[i]);
        }
        i++;
    }

    while (node->lines) {
        LineList *temp = node->lines;
        node->lines = node->lines->next;
        free(temp);
    }
    free(node);
}

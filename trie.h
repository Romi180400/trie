#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>

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

TrieNode *createTrieNode(void);
LineList *addLine(LineList *list, int line);
void insertWord(TrieNode *root, const char *word, int line);
void printTrie(TrieNode *node, char *prefix, int level);
void freeTrie(TrieNode *node);

#endif

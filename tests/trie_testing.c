#include "trie.h"
#include <assert.h>
#include <string.h>

void insertTextIntoTrie(TrieNode *root, const char *text[], int lineCount) {
    int i;
    for (i = 0; i < lineCount; ++i) {
        const char *line = text[i];
        char word[256];
        while (*line) {
            int wordLength = 0;
            while (*line && (*line == ' ' || *line == '\n')) line++;
            while (*line && *line != ' ' && *line != '\n') {
                word[wordLength++] = *line++;
            }
            word[wordLength] = '\0';

            if (wordLength > 0) {
                insertWord(root, word, i + 1);
            }
        }
    }
}

void testInsertAndPrint() {
    const char *text[] = {
            "jack and jill",
            "went up the hill",
            "jack and jill",
            "went down the hill",
            "then the hill disappeared"
    };
    int lineCount = sizeof(text) / sizeof(text[0]);

    TrieNode *root = createTrieNode();
    assert(root != NULL);

    insertTextIntoTrie(root, text, lineCount);

    char prefix[1024] = {0};
    printTrie(root, prefix, 0);


    freeTrie(root);

    printf("Test passed successfully.\n");
}

int main() {
    testInsertAndPrint();
    return 0;
}

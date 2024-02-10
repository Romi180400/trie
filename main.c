#include "trie.h"
#include <string.h>

void readFileAndPopulateTrie(const char *filename, TrieNode *root) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[1024];
    int lineNum = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *word = strtok(line, " \n");
        while (word != NULL) {
            insertWord(root, word, lineNum);
            word = strtok(NULL, " \n");
        }
        lineNum++;
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    TrieNode *root = createTrieNode();
    if (!root) {
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;
    }

    readFileAndPopulateTrie(argv[1], root);

    char prefix[1024];
    printTrie(root, prefix, 0);

    freeTrie(root);
    return EXIT_SUCCESS;
}

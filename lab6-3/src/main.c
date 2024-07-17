#include "tree.h"
#include "wordSearch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH_STRING 10000

int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("None\n0");
        return 1;
    }
    if (N == 0) {
        printf("None\n0");
        return 0;
    }

    TTree* tree = NULL;

    for (int i = 0; i < N; ++i) {
        char* word = malloc(sizeof(char) * (MAX_LENGTH_STRING + 1));
        assert(word != NULL);
        if (scanf("%10000s", word) != 1) {
            free(word);
            return 1;
        }
        tree = InsertKey(tree, word, (int)strlen(word));
        free(word);
    }

    char* searchPrefix = malloc(sizeof(char) * (MAX_LENGTH_STRING + 1));
    assert(searchPrefix != NULL);

    if (scanf("%10000s\n", searchPrefix) != 1) {
        free(searchPrefix);
        DeleteTree(tree);
        return 1;
    }

    PrintWords(tree, searchPrefix);
    PrintHeight(tree);

    free(searchPrefix);
    DeleteTree(tree);

    return 0;
}

#include "RedBlackTree.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        return 1;
    }

    if (N == 0) {
        printf("0\n");
        return 0;
    }

    TNode nodePool = malloc(N * sizeof(struct TNode));
    if (nodePool == NULL) {
        return 1;
    }

    int key;
    if (scanf("%d", &key) != 1) {
        free(nodePool);
        return 1;
    }
    TNode tree = CreateNode(key, nodePool);
    tree->Color = Black;

    for (int i = 1; i < N; ++i) {
        int data;
        if (scanf("%d", &data) != 1) {
            free(nodePool);
            return 1;
        }
        tree = Insert(tree, data, nodePool + i);
    }

    tree->Color = Black;
    printf("%d\n", GetHeight(tree));

    free(nodePool);

    return 0;
}




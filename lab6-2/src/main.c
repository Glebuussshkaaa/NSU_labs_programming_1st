#include "BTree.h"
#include <stdio.h>

int main(void) {
    int degree;
    if (!scanf("%d", &degree)) {
        return 1;
    }

    int N;
    if (!scanf("%d", &N)) {
        return 1;
    }
    if (N == 0) {
        printf("0\n");
        return 0;
    }

    TNode tree = NULL;

    for (int i = 0; i < N; ++i) {
        int key;
        if (!scanf("%d", &key)) {
            DestroyTree(&tree);
            return 1;
        }
        tree = Insert(tree, key, degree);
    }

    printf("%d\n", GetHeight(tree));

    DestroyTree(&tree);

    return 0;
}



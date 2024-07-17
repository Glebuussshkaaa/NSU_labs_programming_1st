#pragma once

#include <stdbool.h>

typedef struct TNode {
    bool Leaf;
    int KeyCount;
    int* Keys;
    struct TNode** Children;
} *TNode;


TNode Insert(TNode tree, const int key, const int degree);
int GetHeight(TNode tree);
void DestroyTree(TNode *tree);



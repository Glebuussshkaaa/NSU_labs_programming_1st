#include "tree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

void Push(TTreesList** list, const int frequency, TTree* tree) {
    TTreesList* head = malloc(sizeof(struct TTreesList));
    assert(head != NULL);
    head->Frequency = frequency;
    head->Tree = tree;
    head->Next = *list;
    *list = head;
}

TTree* MakeLeaf(const unsigned char symbol) {
    TTree* leaf = malloc(sizeof(TTree));
    assert(leaf != NULL);
    leaf->Left = NULL;
    leaf->Right = NULL;
    leaf->Symbol = symbol;
    return leaf;
}

TTreesList* PopMin(TTreesList** list) {
    TTreesList* minNode = *list;
    for (TTreesList* node = *list; node != NULL; node = node->Next) {
        if (node->Frequency < minNode->Frequency) {
            minNode = node;
        }
    }
    if (minNode == *list) {
        *list = minNode->Next;
        return minNode;
    }
    for (TTreesList* node = *list; true; node = node->Next) {
        if (node->Next == minNode) {
            node->Next = minNode->Next;
            return minNode;
        }
    }
}

TTree* MakeInnerTree(TTree* left, TTree* right) {
    TTree* leaf = malloc(sizeof(TTree));
    assert(leaf != NULL);
    leaf->Left = left;
    leaf->Right = right;
    leaf->Symbol = 0;
    return leaf;
}

void DestroyTree(TTree** tree) {
    if (*tree == NULL) {
        return;
    }
    DestroyTree(&((*tree)->Left));
    DestroyTree(&((*tree)->Right));
    free(*tree);
    *tree = NULL;
}

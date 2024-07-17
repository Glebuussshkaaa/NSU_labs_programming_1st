#include "BTree.h"
#include <stdlib.h>
#include <string.h>

TNode CreateNode(const int degree, const bool leaf) {
    TNode newNode = (struct TNode*)malloc(sizeof(struct TNode));
    if (newNode == NULL) {
        return NULL;
    }

    newNode->Leaf = leaf;
    newNode->KeyCount = 0;

    newNode->Keys = (int*)malloc((2 * degree - 1) * sizeof(int));
    if (newNode->Keys == NULL) {
        free(newNode);
        newNode = NULL;
        return NULL;
    }

    newNode->Children = (struct TNode**)malloc((2 * degree) * sizeof(struct TNode*));
    if (newNode->Children == NULL) {
        free(newNode->Keys);
        newNode->Keys = NULL;
        free(newNode);
        newNode = NULL;
        return NULL;
    }

    return newNode;
}

void SplitChild(TNode parent, const int childIndex, TNode child, const int degree) {
    TNode newChild = CreateNode(degree, child->Leaf);
    newChild->KeyCount = degree - 1;

    for (int i = 0; i < degree - 1; ++i) {
        newChild->Keys[i] = child->Keys[i + degree];
    }
    if (child->Leaf == false) {
        for (int i = 0; i < degree; ++i) {
            newChild->Children[i] = child->Children[i + degree];
        }
    }
    child->KeyCount = degree - 1;

    for (int i = parent->KeyCount; i >= childIndex + 1; --i) {
        parent->Children[i + 1] = parent->Children[i];
    }
    parent->Children[childIndex + 1] = newChild;

    for (int i = parent->KeyCount - 1; i >= childIndex; --i) {
        parent->Keys[i + 1] = parent->Keys[i];
    }
    parent->Keys[childIndex] = child->Keys[degree - 1];
    ++parent->KeyCount;
}

int FindInsertionIndex(TNode node, const int key, const int currentLength) {
    if (key > node->Keys[currentLength]) {
        return node->KeyCount;
    }
    if (key < node->Keys[0]) {
        return 0;
    }

    int left = 0;
    int right = currentLength;
    int insertionIndex = 0;
    while (left <= right) {
        int mid = left + ((right - left) / 2);
        if (node->Keys[mid] < key) {
            insertionIndex = mid + 1;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return insertionIndex;
}

void InsertNonFull(TNode node, const int key, const int degree) {
    int currentLength = node->KeyCount - 1;

    if (node->Leaf == true) {
        int insertionIndex = FindInsertionIndex(node, key, currentLength);
        memmove(&node->Keys[insertionIndex + 1], &node->Keys[insertionIndex], (1 + currentLength - insertionIndex) * sizeof(int));
        node->Keys[insertionIndex] = key;
        node->KeyCount = node->KeyCount + 1;
    } else {
        int insertionIndex = FindInsertionIndex(node, key, currentLength);
        if (node->Children[insertionIndex]->KeyCount == 2 * degree - 1) {
            SplitChild(node, insertionIndex, node->Children[insertionIndex], degree);
            if (node->Keys[insertionIndex] < key) {
                ++insertionIndex;
            }
        }
        InsertNonFull(node->Children[insertionIndex], key, degree);
    }
}

TNode Insert(TNode tree, const int key, const int degree) {
    if (tree == NULL) {
        tree = CreateNode(degree, true);
        tree->Keys[0] = key;
        tree->KeyCount = 1;
        return tree;
    }

    if (tree->KeyCount == 2 * degree - 1) {
        TNode ParentNode = CreateNode(degree, false);
        ParentNode->Children[0] = tree;
        SplitChild(ParentNode, 0, ParentNode->Children[0], degree);

        if (ParentNode->Keys[0] < key) {
            InsertNonFull(ParentNode->Children[1], key, degree);
        } else {
            InsertNonFull(ParentNode->Children[0], key, degree);
        }
        tree = ParentNode;
    } else {
        InsertNonFull(tree, key, degree);
    }
    return tree;
}

int GetHeight(TNode tree) {
    int height = 1;
    while (tree->Leaf != true) {
        height = height + 1;
        tree = tree->Children[0];
    }
    return height;
}

void DestroyTree(TNode *tree) {
    if (*tree == NULL) {
        return;
    }

    if ((*tree)->Leaf == false) {
        for (int i = 0; i < (*tree)->KeyCount + 1; ++i) {
            DestroyTree(&(*tree)->Children[i]);
        }
    }

    free((*tree)->Keys);
    free((*tree)->Children);
    free(*tree);
    *tree = NULL;
}


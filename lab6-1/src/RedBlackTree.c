#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdbool.h>

TNode CreateNode(const int data, TNode nodePool) {
    TNode newNode = nodePool;
    newNode->Data = data;
    newNode->Color = Red;
    newNode->Left = NULL;
    newNode->Right = NULL;
    return newNode;
}

static TNode RotateRight(TNode node) {
    TNode newRoot = node->Left;
    node->Left = newRoot->Right;
    newRoot->Right = node;
    newRoot->Color = node->Color;
    node->Color = Red;
    return newRoot;
}

static TNode RotateLeft(TNode node) {
    TNode newRoot = node->Right;
    node->Right = newRoot->Left;
    newRoot->Left = node;
    newRoot->Color = node->Color;
    node->Color = Red;
    return newRoot;
}

static void SwapColors(TNode node) {
    node->Color = Red;
    node->Left->Color = Black;
    node->Right->Color = Black;
}

static bool IsRed(const TNode node) {
    if (node == NULL) {
        return false;
    }
    return node->Color == Red;
}

static TNode Balance(TNode node) {
    if (IsRed(node->Right) && !IsRed(node->Left)) {
        return RotateLeft(node);
    }

    if (IsRed(node->Right)) {
        if (IsRed(node->Left)) {
            if (IsRed(node->Right->Right) || IsRed(node->Right->Left)) {
                SwapColors(node);
                return node;
            }
        }
    }

    if (IsRed(node->Left)) {
        if (IsRed(node->Right)) {
            if (IsRed(node->Left->Left) || IsRed(node->Left->Right)) {
                SwapColors(node);
                return node;
            }
        } else if (IsRed(node->Left->Left)) {
            return RotateRight(node);
        }
    }

    return node;
}

TNode Insert(TNode node, const int data, TNode nodePool) {
    if (node == NULL) {
        return CreateNode(data, nodePool);
    }
    if (data > node->Data) {
        node->Right = Insert(node->Right, data, nodePool);
    } else {
        node->Left = Insert(node->Left, data, nodePool);
    }
    return Balance(node);
}

int GetHeight(const TNode node) {
    if (node == NULL) {
        return 1;
    }
    return (node->Color == Black) + GetHeight(node->Left);
}





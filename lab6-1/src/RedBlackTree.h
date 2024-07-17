#pragma once

enum COLOR {Red, Black};

typedef struct TNode {
    int Data;
    char Color;
    struct TNode* Left;
    struct TNode* Right;
} *TNode;

TNode CreateNode(const int data, TNode nodePool);
TNode Insert(TNode node, const int data, TNode nodePool);
int GetHeight(const TNode node);




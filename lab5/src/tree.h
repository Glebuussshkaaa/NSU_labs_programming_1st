#pragma once

#include <limits.h>

typedef struct TTree {
    unsigned char Symbol;
    struct TTree* Left;
    struct TTree* Right;
} TTree;

typedef int THist[UCHAR_MAX + 1];

typedef struct TTreesList {
    TTree* Tree;
    int Frequency;
    struct TTreesList* Next;
} TTreesList;

void Push(TTreesList** list, const int frequency, TTree* tree);
TTree* MakeLeaf(const unsigned char symbol);
TTreesList* PopMin(TTreesList** list);
TTree* MakeInnerTree(TTree* left, TTree* right);
void DestroyTree(TTree** tree);


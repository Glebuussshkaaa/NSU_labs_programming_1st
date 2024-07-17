#pragma once

#include <stdbool.h>

typedef struct TTree {
    char* Key;
    int KeyLength;
    bool IsWord;
    struct TTree* Link;
    struct TTree* Next;
} TTree;

int GetCommonLength(const char* keyA, const char* keyB);
TTree* InsertKey(TTree* tree, char* newKey, int newKeyLength);
void PrintHeight(const TTree* tree);
void DeleteTree(TTree* tree);

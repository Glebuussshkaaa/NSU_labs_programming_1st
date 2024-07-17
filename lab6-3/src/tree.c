#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

int GetCommonLength(const char* keyA, const char* keyB) {
    int commonLength = 0;
    while (keyA[commonLength] && keyB[commonLength] && keyA[commonLength] == keyB[commonLength]) {
        commonLength++;
    }
    return commonLength;
}

static TTree* CreateNode(const char* key, const int keyLength, const bool isWord) {
    TTree* newNode = malloc(sizeof(TTree));
    assert(newNode != NULL);

    newNode->Key = malloc((keyLength + 1) * sizeof(char));
    assert(newNode->Key != NULL);

    strncpy(newNode->Key, key, keyLength);
    newNode->Key[keyLength] = '\0';
    newNode->KeyLength = keyLength;
    newNode->IsWord = isWord;
    newNode->Link = NULL;
    newNode->Next = NULL;

    return newNode;

}

static void SplitNode(TTree* tree, const int splitLength, const bool IsWord) {
    TTree* newNode = CreateNode(tree->Key + splitLength, tree->KeyLength - splitLength, false);
    assert(newNode != NULL);

    char* newKey = malloc((splitLength + 1) * sizeof(char));
    assert(newKey != NULL);

    newNode->Link = tree->Link;
    tree->Link = newNode;

    strncpy(newKey, tree->Key, splitLength);
    newKey[splitLength] = '\0';
    free(tree->Key);
    tree->Key = newKey;
    tree->KeyLength = splitLength;
    newNode->IsWord = IsWord;
}

TTree* InsertKey(TTree* tree, char* newKey, const int newKeyLength) {
    if (tree == NULL) {
        return CreateNode(newKey, newKeyLength, true);
    }

    int commonLength = GetCommonLength(tree->Key, newKey);

    if (commonLength == 0) {
        tree->Next = InsertKey(tree->Next, newKey, newKeyLength);
    } else if (commonLength == newKeyLength && commonLength == tree->KeyLength) {
        tree->IsWord = true;
    } else if (commonLength == tree->KeyLength && commonLength < newKeyLength) {
        tree->Link = InsertKey(tree->Link, newKey + commonLength, newKeyLength - tree->KeyLength);
    } else if (commonLength == newKeyLength && commonLength < tree->KeyLength) {
        SplitNode(tree, commonLength, true);
    } else if (commonLength < newKeyLength && commonLength < tree->KeyLength){
        SplitNode(tree, commonLength, tree->IsWord);
        tree->IsWord = false;
        tree->Link = InsertKey(tree->Link, newKey + commonLength, newKeyLength - commonLength);
    }

    return tree;
}

static int GetNumNodes(const TTree* tree) {
    if (tree == NULL) {
        return 0;
    }
    return 1 + GetNumNodes(tree->Next) + GetNumNodes(tree->Link);
}

static int GetHeight(const TTree* tree) {
    if (tree->Next != NULL) {
        return 1 + GetNumNodes(tree);
    }
    return GetNumNodes(tree);
}

void PrintHeight(const TTree* tree) {
    int height = GetHeight(tree);
    printf("\n%d\n", height);
}

void DeleteTree(TTree* tree) {
    if (tree == NULL) {
        return;
    }

    DeleteTree(tree->Next);
    DeleteTree(tree->Link);

    free(tree->Key);
    free(tree);
}

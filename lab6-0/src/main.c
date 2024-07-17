#include <stdio.h>
#include <stdlib.h>

typedef struct TTree{
    int Value;
    unsigned int Height;
    struct TTree* Left;
    struct TTree* Right;
} *TTree;

TTree CreateNode(TTree nodePool, const int key);
TTree Insert(TTree node, const int key, TTree nodePool);
TTree Balance(TTree node);
TTree RotateRight(TTree node);
TTree RotateLeft(TTree node);
void CalculateHeight(TTree node);
int GetBalanceFactor(const TTree node);
unsigned int GetHeight(const TTree node);


int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        return 1;
    }

    TTree nodePool = malloc(N * sizeof(struct TTree));
    if (nodePool == NULL) {
        return 1;
    }
    TTree tree = NULL;

    for (int i = 0; i < N; ++i) {
        int key;
        if (scanf("%d", &key) != 1) {
            free(nodePool);
            return 1;
        }
        tree = Insert(tree, key, nodePool + i);
    }

    printf("%u\n", GetHeight(tree));

    free(nodePool);

    return 0;
}

TTree CreateNode(TTree nodePool, const int key) {
    TTree newNode = nodePool;
    newNode->Value = key;
    newNode->Height = 1;
    newNode->Left = NULL;
    newNode->Right = NULL;
    return newNode;
}

TTree Insert(TTree node, const int key, TTree nodePool) {
    if (node == NULL) {
        return CreateNode(nodePool,key);
    }
    if (key < node->Value) {
        node->Left = Insert(node->Left, key, nodePool);
    } else {
        node->Right = Insert(node->Right, key, nodePool);
    }
    return Balance(node);
}

TTree Balance(TTree node) {
    CalculateHeight(node);
    if (GetBalanceFactor(node) == 2) {
        if (GetBalanceFactor(node->Right) < 0) {
            node->Right = RotateRight(node->Right);
        }
        return RotateLeft(node);
    }
    if (GetBalanceFactor(node) == -2) {
        if (GetBalanceFactor(node->Left) > 0) {
            node->Left = RotateLeft(node->Left);
        }
        return RotateRight(node);
    }
    return node;
}

TTree RotateRight(TTree node) {
    TTree newRoot = node->Left;
    node->Left = newRoot->Right;
    newRoot->Right = node;
    CalculateHeight(node);
    CalculateHeight(newRoot);
    return newRoot;
}

TTree RotateLeft(TTree node) {
    TTree newRoot = node->Right;
    node->Right = newRoot->Left;
    newRoot->Left = node;
    CalculateHeight(node);
    CalculateHeight(newRoot);
    return newRoot;
}

void CalculateHeight(TTree node) {
    unsigned char leftHeight = GetHeight(node->Left);
    unsigned char rightHeight = GetHeight(node->Right);
    if (leftHeight > rightHeight) {
        node->Height = leftHeight + 1;
    } else {
        node->Height = rightHeight + 1;
    }
}

int GetBalanceFactor(const TTree node) {
    if (node == NULL) {
        return 0;
    }
    return GetHeight(node->Right)-GetHeight(node->Left);
}

unsigned int GetHeight(const TTree node) {
    if (node != NULL) {
        return node->Height;
    } else {
        return 0;
    }
}





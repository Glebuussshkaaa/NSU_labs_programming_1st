#include "decompress.h"
#include "bitStream.h"
#include "tree.h"
#include <stdio.h>
#include <assert.h>

static int ReadSize(const TBitStream* bitStream) {
    int size;
    if (fread(&size, sizeof(int), 1, bitStream->Stream) != 1) {
        return -1;
    }
    return size;
}

static TTree* ReadTree(TBitStream* bitStream, bool* readError) {
    bool bit = ReadBit(bitStream, readError);
    if (bit) {
        TTree* left = ReadTree(bitStream, readError);
        TTree* right = ReadTree(bitStream, readError);
        return MakeInnerTree(left, right);
    } else {
        unsigned char symbol = 0;
        for (size_t i = 0; i < 8; ++i) {
            symbol += (ReadBit(bitStream, readError) << i);
        }
        return MakeLeaf(symbol);
    }
}

static void CopyData(TBitStream* bitStream, FILE* outputFile, int size, TTree* tree, bool* readError) {
    TTree* node = tree;
    while (size > 0) {
        if (node->Left == NULL) {
            assert(node->Right == NULL);
            fputc(node->Symbol, outputFile);
            node = tree;
            --size;
        } else {
            bool bit = ReadBit(bitStream, readError);
            if (bit) {
                node = node->Right;
            } else {
                node = node->Left;
            }
        }
    }
}

void Decompress(FILE* inputFile, FILE* outputFile) {
    TBitStream bitStream = CreateInputBitStream(inputFile);
    int size = ReadSize(&bitStream);
    if (size < 1) {
        return;
    }
    bool readError = false;
    TTree* tree = ReadTree(&bitStream, &readError);
    CopyData(&bitStream, outputFile, size, tree, &readError);
    if (readError) {
        return;
    }
    DestroyTree(&tree);
}

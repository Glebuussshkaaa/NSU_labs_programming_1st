#include "compress.h"
#include "bitStream.h"
#include "tree.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

static void CalcFrequency(FILE* inputFile, THist hist) {
    fseek(inputFile, 1, SEEK_SET);
    memset(hist, 0, sizeof(THist));
    while (true) {
        unsigned char buffer;
        size_t count = fread(&buffer, sizeof(buffer), 1, inputFile);
        if (count != 1) {
            break;
        }
        hist[buffer] += 1;
    }
}

static int GetSize(const THist hist) {
    int size = 0;
    for (size_t i = 0; i < UCHAR_MAX + 1; ++i) {
        size += hist[i];
    }
    return size;
}

static void WriteSize(const int size, FILE* outputFile) {
    fwrite(&size, sizeof(size), 1, outputFile);
}

static TTree* CreateTree(const THist hist) {
    TTreesList* list = NULL;
    for (size_t i = 0; i < UCHAR_MAX + 1; ++i) {
        if (hist[i] > 0) {
            Push(&list, hist[i], MakeLeaf(i));
        }
    }
    assert(list != NULL);
    while (list->Next != NULL) {
        TTreesList* left = PopMin(&list);
        TTreesList* right = PopMin(&list);
        Push(&list, left->Frequency + right->Frequency, MakeInnerTree(left->Tree, right->Tree));
        free(left);
        free(right);
    }
    TTree* tree = list->Tree;
    free(list);
    return tree;
}

static void WriteTree(const TTree* tree, TBitStream* bitStream) {
    if (tree->Left == NULL) {
        assert(tree->Right == NULL);
        WriteBit(bitStream, 0);
        for (size_t i = 0; i < 8; ++i) {
            bool bit = (tree->Symbol >> i) & 1;
            WriteBit(bitStream, bit);
        }
    } else {
        WriteBit(bitStream, 1);
        WriteTree(tree->Left, bitStream);
        WriteTree(tree->Right, bitStream);
    }
}

static bool GetCode(const TTree* tree, const unsigned char symbol, unsigned char* code) {
    if (tree->Left == NULL) {
        assert(tree->Right == NULL);
        return tree->Symbol == symbol;
    }
    if (GetCode(tree->Left, symbol, code + 1)) {
        *code = '0';
        return true;
    }
    if (GetCode(tree->Right, symbol, code + 1)) {
        *code = '1';
        return true;
    }
    return false;
}

static void WriteData(FILE* inputFile, const TTree* tree, TBitStream* bitStream) {
    fseek(inputFile, 1, SEEK_SET);
    while (true) {
        unsigned char buffer;
        size_t count = fread(&buffer, sizeof(buffer), 1, inputFile);
        if (count != 1) {
            break;
        }
        unsigned char code[UCHAR_MAX] = {0};
        GetCode(tree, buffer, code);
        for (size_t i = 0; code[i] != 0; ++i) {
            assert(code[i] == '0' || code[i] == '1');
            WriteBit(bitStream, code[i] != '0');
        }
    }
}

void Compress(FILE* inputFile, FILE* outputFile) {
    THist SymbolFrequency;
    CalcFrequency(inputFile, SymbolFrequency);
    int size = GetSize(SymbolFrequency);
    if (size < 1) {
        return;
    }
    WriteSize(size, outputFile);
    TTree* tree = CreateTree(SymbolFrequency);
    TBitStream bitStream = CreateOutputBitStream(outputFile);
    WriteTree(tree, &bitStream);
    WriteData(inputFile, tree, &bitStream);
    FlushBits(&bitStream);
    DestroyTree(&tree);
}

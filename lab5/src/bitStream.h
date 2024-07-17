#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct TBitStream {
    FILE* Stream;
    unsigned char Buffer;
    int Count;
} TBitStream;

TBitStream CreateOutputBitStream(FILE* outputFile);
void WriteBit(TBitStream* bitStream, const bool bit);
void FlushBits(const TBitStream* bitStream);
TBitStream CreateInputBitStream(FILE* inputFile);
bool ReadBit(TBitStream* bitStream, bool* readError);


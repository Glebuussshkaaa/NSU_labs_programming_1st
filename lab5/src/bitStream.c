#include "bitStream.h"
#include <stdio.h>
#include <stdbool.h>

TBitStream CreateOutputBitStream(FILE* outputFile) {
    TBitStream bitStream = {outputFile, 0, 0};
    return bitStream;
}

void WriteBit(TBitStream* bitStream, const bool bit) {
    if (bitStream->Count == 8) {
        fwrite(&bitStream->Buffer, sizeof(bitStream->Buffer), 1, bitStream->Stream);
        bitStream->Buffer = 0;
        bitStream->Count = 0;
    }
    bitStream->Buffer += (bit << bitStream->Count);
    bitStream->Count += 1;
}

void FlushBits(const TBitStream* bitStream) {
    if (bitStream->Count > 0) {
        fwrite(&bitStream->Buffer, sizeof(bitStream->Buffer), 1, bitStream->Stream);
    }
}

TBitStream CreateInputBitStream(FILE* in) {
    TBitStream stream = {in, 0, 8};
    return stream;
}

bool ReadBit(TBitStream* bitStream, bool* readError) {
    if (bitStream->Count == 8) {
        if (fread(&bitStream->Buffer, sizeof(bitStream->Buffer), 1, bitStream->Stream) != 1) {
            *readError = true;
            return true;
        }
        bitStream->Count = 0;
    }
    bool bit = bitStream->Buffer & (1 << bitStream->Count);
    bitStream->Count += 1;
    return bit;
}


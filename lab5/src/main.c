#include "compress.h"
#include "decompress.h"
#include <stdio.h>

int main() {
    FILE* inputFile = fopen("in.txt", "rb");
    FILE* outputFile = fopen("out.txt", "wb");

    unsigned char mode = fgetc(inputFile);
    if (mode == 'c') {
        Compress(inputFile, outputFile);
    }
    if (mode == 'd') {
        Decompress(inputFile, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

#include "inout.h"
#include <stdio.h>
#include "error.h"

void InputSequence(char* sequence) {
    int i = 0;

    while (i < MAX_SIZE_SEQUENCE + 1) {

        char input = (char)getchar();

        if (input == '\n') {
            sequence[i] = '\0';
            break;
        }

        sequence[i] = input;
        ++i;
    }
}

void InputPermutationCount(int* permutationCount) {
    if (scanf("%d", permutationCount) != 1) {
        ErrorHandler();
    }
}

void PrintSequence(const char* sequence) {
    printf("%s\n", sequence);
}



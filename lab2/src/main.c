#include "inout.h"
#include "check.h"
#include "narayana.h"
#include "error.h"
#include <stdlib.h>

int main(void) {
    char sequence[MAX_SIZE_SEQUENCE + 1] = {0};
    InputSequence(sequence);

    if (!CheckInputSequence(sequence)) {
        BadInputError();
        return EXIT_SUCCESS;
    }

    int permutationCount;
    InputPermutationCount(&permutationCount);

    GenerateNextPermutation(sequence, permutationCount);

    return EXIT_SUCCESS;
}


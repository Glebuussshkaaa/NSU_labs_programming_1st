#include "check.h"

static bool NumberCheck(char symbol) {
    return symbol >= '0' && symbol <= '9';
}

bool CheckInputSequence(const char* sequence) {
    int counter[10] = {0};

    for (int i = 0; sequence[i] != '\0'; ++i) {
        if (NumberCheck(sequence[i]) && counter[sequence[i] -'0'] == 0) {
            ++counter[sequence[i] - '0'];
        }
        else {
            return false;
        }
    }
    return true;
}



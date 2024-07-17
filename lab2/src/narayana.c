#include "narayana.h"
#include "inout.h"

static void Swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}


static void ReverseSequence(int length, char* array) {
    int start = 0;
    int end = length - 1;

    while (start < end) {
        Swap(array + start, array + end);
        ++start;
        --end;
    }
}

static int CustomStrlen(const char* sequence) {
    int length = 0;
    while(sequence[length] != '\0') {
        length++;
    }
    return length;
}

void GenerateNextPermutation(char* sequence, int permutationCount) {
    int sequenceLength = CustomStrlen(sequence);

    for (int i = 0; i < permutationCount; ++i) {
        int index1 = 0;
        int index2 = 0;

        for (index1 = sequenceLength - 2; ; --index1) {
            if (index1 < 0) {
                return;
            }

            if (sequence[index1] < sequence[index1 + 1]) {
                break;
            }
        }

        for (index2 = sequenceLength - 1; index2 > index1; --index2) {
            if (sequence[index2] > sequence[index1]) {
                break;
            }
        }

        Swap(sequence + index1, sequence + index2);
        ReverseSequence(sequenceLength - 1 - index1, sequence + index1 + 1);
        PrintSequence(sequence);
    }
}


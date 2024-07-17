#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE_EXAMPLE 16
#define UNSIGNED_CHAR_EOF 255

void InputExample(unsigned char* example);

int CustomStrlen(const unsigned char* example);
int calculateHash(const unsigned char* example, const int exampleLength);
void shiftString(unsigned char* string, const int position, const int exampleLength);
bool HashComparison(const int firstHash,const int secondHash);
void RabinKarpAlgorithm(const unsigned char* example, const int exampleLength, const int hashValueExample);

int main() {
    unsigned char example[MAX_SIZE_EXAMPLE + 1];
    InputExample(example);

    int exampleLength = CustomStrlen(example);
    int hashValueExample = calculateHash(example, exampleLength);
    printf("%d ", hashValueExample);

    RabinKarpAlgorithm(example, exampleLength, hashValueExample);

    return 0;
}

void InputExample(unsigned char* example) {
    int i = 0;
    while (i < MAX_SIZE_EXAMPLE + 1) {
        char input = (char)getchar();
        if (input == '\n') {
            example[i] = '\0';
            break;
        }
        example[i] = input;
        ++i;
    }
}

int CustomStrlen(const unsigned char* example) {
    int length = 0;
    while(example[length] != '\0') {
        length++;
    }
    return length;
}

int calculateHash(const unsigned char* example, const int exampleLength) {
    int hashValue = 0;
    int pow = 1;
    for (int i = 0; i < exampleLength; ++i) {
        hashValue += (example[i] % 3) * pow;
        pow *= 3;
    }
    return hashValue;
}

void shiftString(unsigned char* string, const int position, const int exampleLength) {
    for (int i = 1; i < exampleLength; ++i) {
        string[i - 1] = string[i];
    }
    string[position] = getchar();
}

bool HashComparison(const int firstHash,const int secondHash) {
    return (firstHash == secondHash);
}

void RabinKarpAlgorithm(const unsigned char* example, const int exampleLength, const int hashValueExample) {
    unsigned char string[MAX_SIZE_EXAMPLE + 1] = {0};
    for (int i = 0; i < exampleLength; ++i) {
        string[i] = getchar();
    }

    int position = exampleLength - 1;
    int globalPosition = 0;

    int maxPowExample = (int)pow(3, exampleLength - 1);
    int hashValueString = calculateHash(string, exampleLength);

    while (string[position] != UNSIGNED_CHAR_EOF) {

        if (HashComparison(hashValueExample, hashValueString)) {

            for (int i = 0; i < exampleLength; ++i) {
                int index = i + globalPosition + 1;
                printf("%d ", index);
                if (example[i] != string[i])
                    break;
            }
        }

        hashValueString -= (string[0] % 3);
        hashValueString /= 3;

        shiftString(string, position, exampleLength);

        hashValueString += (string[position] % 3) * maxPowExample;
        globalPosition += 1;
    }
}


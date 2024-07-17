#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int BadInputError(void) {
    printf("bad input\n");
    return EXIT_SUCCESS;
}

int InputError(void) {
    printf("ошибка");
    return EXIT_SUCCESS;
}


void InputNumberSystem(int* systemBase) {
    if (scanf("%d", systemBase) != 1) {
        InputError();
    }
    
    if (*systemBase < 2 || *systemBase > 16) {
        BadInputError();
    }
}


void InputNumber(int count, char* number) {
    if (scanf("%13s", number) != 1) {
        InputError();
    }
    
    number[count] = '\0';
}


void OutputNumber(const char* number) {
    printf("%s\n", number);
}


const char* allSymbols = "0123456789abcdef";


int CharToInt(int systemBase, char symbol) {
    for (int i = 0; i < systemBase; ++i) {
        if (tolower(symbol) == allSymbols[i]) {
            return i;
        }
    }
    
    BadInputError();
    return EXIT_FAILURE;
}


int GetIntegerSize(const char* number)
{
    int numberLength = (int)strlen(number);
    int integerSize = 0;
    
    for (int i = 0; i < numberLength; ++i) {
        if (number[i] != '.') {
            ++integerSize;
        }
        else {
            break;
        }
    }

    if (integerSize == 0 || integerSize == numberLength - 1) {
        BadInputError();
        return EXIT_FAILURE;
    }
    
    return integerSize;
}


double ToDouble(int firstSystemBase, const char* number)
{
    int integerSize = GetIntegerSize(number);
    double sum = 0.0;

    for (int i = 0; i < integerSize; ++i) {
        sum += CharToInt(firstSystemBase, number[i]) * pow(firstSystemBase, integerSize - 1 - i);
    }

    int numberLength = (int)strlen(number);

    for (int i = integerSize + 1; i < numberLength; ++i) {
        sum += CharToInt(firstSystemBase, number[i]) * pow(firstSystemBase, integerSize - i);
    }
    
    double decimalNumber = sum;
    
    return decimalNumber;
}


void Reverse(char* newNumber, int index) {
    int start = 0;
    int end = index - 1;

    while (start < end) {
        char temp = newNumber[start];
        newNumber[start] = newNumber[end];
        newNumber[end] = temp;
        start++;
        end--;
    }
}


char* FromDouble(int secondSystemBase, double decimalNumber ) {
    int maxLength = 64;
    char* newNumber = (char*)malloc(maxLength);

    long long integer = (long long)decimalNumber;
    double fractional = decimalNumber  - integer;
    int index = 0;

    do {
        newNumber[index++] = allSymbols[integer % secondSystemBase];
        integer /= secondSystemBase;
    } while (integer > 0);
    
    Reverse(newNumber, index);
    newNumber[index++] = '.';

    for (int i = 0; i < 12; i++) {
        fractional *= secondSystemBase;
        newNumber[index++] = allSymbols[(int)fractional];
        fractional -= (int)fractional;
    }

    return newNumber;
}


char* ConversionNumber(int firstSystemBase, int secondSystemBase, const char* number) {
    double decimalNumber = ToDouble(firstSystemBase, number);
    char* newNumber = FromDouble(secondSystemBase, decimalNumber);
    return newNumber;
}


int main(void) {
    int firstSystemBase;
    int secondSystemBase;
    char number[14] = { 0 };

    InputNumberSystem(&firstSystemBase);
    InputNumberSystem(&secondSystemBase);
    InputNumber(13, number);
    
    char* convertedNumber = ConversionNumber(firstSystemBase, secondSystemBase, number);

    OutputNumber(convertedNumber);

    free(convertedNumber);

    return EXIT_SUCCESS;
}

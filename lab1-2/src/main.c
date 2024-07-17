#include <stdio.h>

#define MAX_SIZE_EXAMPLE 16
#define DATA_SIZE 101

typedef struct TFileView {
    FILE* File;
    char Data[DATA_SIZE];
    int Size;
} TFileView;

int CustomStrlen(const char* pattern);

TFileView CreateFileView(FILE* File);
void ViewShift(TFileView* view, const int shift);
void PrefixFunction(const int patternLength, const char* pattern, char* prefixTable);
void PrintPrefixTable(const int patternLength, const char* prefixTable);
void KMPSearch(TFileView* fileView, const char* pattern);


int main(void) {
    char pattern[MAX_SIZE_EXAMPLE + 2];
    if (fgets(pattern, MAX_SIZE_EXAMPLE + 2, stdin) == NULL) {
        printf("Ошибка при чтении патерна\n");
        return 1;
    }

    TFileView fileView = CreateFileView(stdin);

    KMPSearch(&fileView, pattern);

    return 0;
}

int CustomStrlen(const char* pattern) {
    int length = 0;
    while (pattern[length] != '\n') {
        length++;
    }
    return length;
}

TFileView CreateFileView(FILE* File) {
    TFileView view;
    view.File = File;
    view.Size = (int)fread(view.Data, sizeof(char), MAX_SIZE_EXAMPLE, view.File);
    return view;
}

void ViewShift(TFileView* fileView, const int shift) {
    for (int i = 0; i < fileView->Size - shift; ++i) {
        fileView->Data[i] = fileView->Data[i + shift];
    }

    int count = (int)fread(fileView->Data + fileView->Size - shift, sizeof(char), shift, fileView->File);
    fileView->Size += count - shift;
}

void PrefixFunction(const int patternLength, const char* pattern, char* prefixTable) {
    prefixTable[0] = 0;
    for (int i = 1; i < patternLength; ++i) {
        int j = prefixTable[i - 1];
        while ((j > 0) && (pattern[i] != pattern[j])) {
            j = prefixTable[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        prefixTable[i] = j;
    }
}

void PrintPrefixTable(const int patternLength, const char* prefixTable) {
    for (int i = 0; i < patternLength; ++i) {
        printf("%d ", prefixTable[i]);
    }
    printf("\n");
}

void KMPSearch(TFileView* fileView, const char* pattern) {
    int patternLength = CustomStrlen(pattern);

    char prefixTable[MAX_SIZE_EXAMPLE];
    PrefixFunction(patternLength, pattern, prefixTable);
    PrintPrefixTable(patternLength, prefixTable);

    int globalPosition = 0;
    int shift;

    while (fileView->Size >= patternLength) {
        int matchCount = 0;

        while (pattern[matchCount] == fileView->Data[matchCount]) {
            ++matchCount;
        }

        if (matchCount != 0) {
            printf("%d %d ", globalPosition + 1, matchCount);
            shift = matchCount - prefixTable[matchCount - 1];
        } else {
            shift = 1;
        }

        ViewShift(fileView, shift);
        globalPosition += shift;
    }
}



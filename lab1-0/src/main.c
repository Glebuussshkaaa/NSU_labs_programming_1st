#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE_EXAMPLE 16

typedef struct TFileView {
    FILE* File;
    char Data[MAX_SIZE_EXAMPLE];
    int Size;
} TFileView;

void InputExample(char* example);
TFileView CreateFileView(FILE* File);

int CustomStrlen(const char* example);
void ViewShift(TFileView* view, const int shift);
bool CompareLetters(char a, char b, const int globalPosition, const int position);
void UpdatePosition(TFileView* fileView, const char* example, int* globalPosition);
void BoyerMooreAlgorithm(TFileView* fileView, const char* example);

int main(void) {
    char example[MAX_SIZE_EXAMPLE + 1];
    InputExample(example);

    TFileView fileView = CreateFileView(stdin);

    BoyerMooreAlgorithm(&fileView, example);
    return 0;
}

void InputExample(char* example) {
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

TFileView CreateFileView(FILE* File) {
    TFileView view;
    view.File = File;
    view.Size = (int)fread(view.Data, sizeof(char), MAX_SIZE_EXAMPLE, view.File);
    return view;
}

int CustomStrlen(const char* example) {
    int length = 0;
    while(example[length] != '\0') {
        length++;
    }
    return length;
}


void ViewShift(TFileView* view, const int shift) {

    for (int i = 0; i < view->Size - shift; ++i) {
        view->Data[i] = view->Data[i + shift];
    }

    int count = (int)fread(view->Data + view->Size - shift, 1, shift, view->File);
    view->Size += count - shift;
}


bool CompareLetters(char a, char b, const int globalPosition, const int position) {
    printf("%d ", position + 1 + globalPosition);
    return (a == b);
}

void UpdatePosition(TFileView* fileView, const char* example, int* globalPosition) {
    int exampleLength = CustomStrlen(example);
    int position = exampleLength - 1;
    int shift = exampleLength;

    while (CompareLetters(fileView->Data[position], example[position], *globalPosition, position)) {
        for (int i = 0; i < position; ++i) {
            if (fileView->Data[position] == example[i]) {
                shift = position - i;
            }
        }
        if (position == 0) {
            shift = exampleLength;
            break;
        }
        position--;
    }

    for (int i = 0; i < position; i++) {
        if (fileView->Data[position] == example[i]) {
            shift = position - i;
        }
    }

    *globalPosition += shift;
    ViewShift(fileView, shift);
}


void BoyerMooreAlgorithm(TFileView* fileView, const char* example) {
    int globalPosition = 0;
    int exampleLength = CustomStrlen(example);
    while (fileView->Size >= exampleLength) {
        UpdatePosition(fileView, example, &globalPosition);
    }
}



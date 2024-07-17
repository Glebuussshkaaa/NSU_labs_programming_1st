#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int ErrorHandler(void);

void InputLength(int *length);
void InputArray(int array[], int Length);
void OutputSortedArray(int array[], int length);

void swap(int *a, int *b);
void QuickSort(int array[], int length);
void QuickSortRecursion(int array[], int low, int high);
int Partition(int array[], int low, int high);


int main(void) {
    int length;
    InputLength(&length);

    int* array = (int*)malloc(length * sizeof(int));
    if (array == NULL) {
        printf("Недостаточно памяти\n");
        return EXIT_FAILURE;
    }
    InputArray(array, length);

    QuickSort(array, length);

    OutputSortedArray(array, length);
    free(array);

    return EXIT_SUCCESS;
}


int ErrorHandler(void) {
    printf("Ошибка\n");
    return EXIT_SUCCESS;
}

void InputLength(int *length) {
    if (scanf("%d", length) != 1) {
        ErrorHandler();
    }
}

void InputArray(int array[], int Length) {
    for (int i = 0; i < Length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            ErrorHandler();
        }
    }
}

void OutputSortedArray(int array[], int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void QuickSort(int array[], int length) {
    QuickSortRecursion(array, 0, length - 1);
}


void QuickSortRecursion(int array[], int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(array, low, high);
        QuickSortRecursion(array, low, pivotIndex - 1);
        QuickSortRecursion(array, pivotIndex, high);
    }
}


int Partition(int array[], int low, int high) {
    int pivot = array[(low + high) / 2];

    while (low <= high) {
        while (array[low] < pivot) {
            low++;
        }

        while (array[high] > pivot) {
            high--;
        }

        if (low <= high) {
            swap(&array[low], &array[high]);
            low++;
            high--;
        }
    }
    
    return low;
}





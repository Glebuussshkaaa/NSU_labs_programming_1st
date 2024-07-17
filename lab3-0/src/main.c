#include <stdio.h>
#include <stdlib.h>

// функция для обработки ошибок
int ErrorInput(void) {
    printf("Ошибка\n");
    return EXIT_SUCCESS;
}

// функция для ввода длины массива
void InputLength(int* length) {
    if (scanf("%d", length) != 1) {
        ErrorInput();
    }
}

// функция для ввода значений элементов массива
void InputArray(int arr[], int length) {
    for (int i = 0; i < length; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            ErrorInput();
        }
    }
}

// функция для вывода ответа
void OutputSortedArray(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// функция для обмена значений двух элементов
void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// функция для преобразования массива в кучу
void TransformToHeap(int arr[], int length, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < length && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < length && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != index) {
        Swap(&arr[index], &arr[largest]);
        TransformToHeap(arr, length, largest);
    }
}

// HeapSort
void HeapSort(int arr[], int length) {
    for (int i = length / 2 - 1; i >= 0; --i) {
        TransformToHeap(arr, length, i);
    }
    
    for (int i = length - 1; i > 0; --i) {
        Swap(&arr[0], &arr[i]);
        TransformToHeap(arr, i, 0);
    }
}


int main(void) {
    int length;
    InputLength(&length);
    
    int arr[length];
    InputArray(arr, length);
    
    HeapSort(arr, length);
    OutputSortedArray(arr, length);
    
    return EXIT_SUCCESS;
}



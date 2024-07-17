#include "knapsack.h"
#include <stdio.h>
#include <stdlib.h>

static int Max(const int firstNumber, const int secondNumber) {
    if (firstNumber > secondNumber) {
        return firstNumber;
    }
    return secondNumber;
}

static void FreeKnapsackTable(int** table, const int numItems) {
    for (int i = 0; i < numItems + 1; ++i) {
        free(table[i]);
    }
    free(table);
}

static int** AllocateKnapsackTable(const int numItems, const int capacity) {
    int** table = malloc((numItems + 1) * sizeof(int *));
    if (table == NULL) {
        return NULL;
    }
    for (int i = 0; i < numItems + 1; i++) {
        table[i] = calloc(capacity + 1, sizeof(int));
        if (table[i] == NULL) {
            FreeKnapsackTable(table, i - 1);
            return NULL;
        }
    }
    return table;
}

static void printResult(const Item* items, const int** table, const int numItems, const int capacity) {
    int totalValue = table[numItems][capacity];
    printf("%d\n", totalValue);

    char* selectedItems = calloc(numItems, sizeof(int));
    if (selectedItems == NULL) {
        return;
    }
    int tmp = capacity;
    for (int i = numItems; i > 0; --i) {
        if (table[i][tmp] != table[i - 1][tmp]) {
            selectedItems[i - 1] = 1;
            tmp -= items[i - 1].Weight;
        }
    }

    for (int i = 0; i < numItems; ++i) {
        if (selectedItems[i] == 1) {
            printf("%d %d\n", items[i].Weight, items[i].Value);
        }
    }

    free(selectedItems);
}

void PackKnapsack(const int numItems, const int capacity, const Item* items) {
    int** table = AllocateKnapsackTable(numItems, capacity);
    if (table == NULL) {
        return;
    }

    for (int i = 1; i < numItems + 1; i++) {
        for (int w = 1; w < capacity + 1; w++) {
            if (items[i - 1].Weight <= w) {
                table[i][w] = Max(items[i - 1].Value + table[i - 1][w - items[i - 1].Weight], table[i - 1][w]);
            } else {
                table[i][w] = table[i - 1][w];
            }
        }
    }

    printResult(items, (const int**) table, numItems, capacity);

    FreeKnapsackTable(table, numItems);
}

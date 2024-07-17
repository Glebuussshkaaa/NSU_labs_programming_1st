#include "knapsack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int numItems, capacity;
    if (scanf("%d %d", &numItems, &capacity) != 2) {
        return 1;
    }

    Item* items = malloc(numItems * sizeof(struct item));
    if (items == NULL) {
        return 1;
    }
    for (int i = 0; i < numItems; ++i) {
        if (scanf("%d %d", &items[i].Weight, &items[i].Value) != 2) {
            free(items);
            return 1;
        }
    }

    PackKnapsack(numItems, capacity, items);
    free(items);
    return 0;
}

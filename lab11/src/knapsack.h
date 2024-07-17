#pragma once

typedef struct item {
    int Weight;
    int Value;
} Item;

void PackKnapsack(const int numItems, const int capacity, const Item* items);

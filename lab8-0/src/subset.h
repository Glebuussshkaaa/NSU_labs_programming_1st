#pragma once

typedef struct Subset {
    int Root;
    int Rank;
} TSubset;

int FindRootSubset(const TSubset* subsets, int index);
void UnionNodesSubset(TSubset* subsets, const int rootSrc, const int rootDest);


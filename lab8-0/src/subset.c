#include "subset.h"

int FindRootSubset(const TSubset* subsets, int index) {
    while ((subsets + index)->Root != index) {
        index = (subsets + index)->Root;
    }
    return index;
}

void UnionNodesSubset(TSubset* subsets, const int rootSrc, const int rootDest) {
    if ((subsets + rootSrc)->Rank < (subsets + rootDest)->Rank) {
        (subsets + rootSrc)->Root = rootDest;
    } else if ((subsets + rootSrc)->Rank > (subsets + rootDest)->Rank) {
        (subsets + rootDest)->Root = rootSrc;
    } else {
        (subsets + rootDest)->Root = rootSrc;
        (subsets + rootSrc)->Rank++;
    }
}

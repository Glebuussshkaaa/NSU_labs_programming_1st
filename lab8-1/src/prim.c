#include "prim.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ROOT 0

TGraph CreateGraph(const int numVertices) {
    TGraph graph = malloc(sizeof(struct Graph));
    if (graph == NULL) {
        return NULL;
    }

    graph->numVertices = numVertices;

    graph->GraphMatrix = calloc(numVertices * numVertices, sizeof(unsigned int));
    if (graph->GraphMatrix == NULL) {
        free(graph);
        return NULL;
    }

    return graph;
}

int CalcMin(int numVertices, const unsigned int* key, const char* setMST) {
    unsigned int min = UINT_MAX;
    int minIndex = 0;
    for (int v = 0; v < numVertices; ++v) {
        if (!setMST[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void Find(TGraph graph) {
    char* setMST = calloc(graph->numVertices, sizeof(char));
    if (setMST == NULL) {
        return;
    }

    int *parentMST = calloc(graph->numVertices, sizeof(int));
    if (parentMST == NULL) {
        free(setMST);
        return;
    }

    unsigned int *key = malloc(graph->numVertices * sizeof(unsigned int));
    if (key == NULL) {
        free(setMST);
        free(parentMST);
        return;
    }
    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = UINT_MAX;
    }

    key[0] = 0;
    parentMST[0] = ROOT;
    int numMSTNodes = 0;

    for (int count = 0; count < graph->numVertices; count++) {
        int u = CalcMin(graph->numVertices, key, setMST);
        numMSTNodes += !setMST[u];
        setMST[u] = 1;
        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->GraphMatrix[u * graph->numVertices + v]) {
                if (setMST[v] == 0 && graph->GraphMatrix[u * graph->numVertices + v] <= key[v]) {
                    parentMST[v] = u;
                    key[v] = graph->GraphMatrix[u * graph->numVertices + v];
                }
            }
        }
    }

    if (numMSTNodes != graph->numVertices) {
        printf("no spanning tree\n");
        free(setMST);
        free(parentMST);
        free(key);
        return;
    }

    for (int i = 1; i < graph->numVertices; i++) {
        printf("%d %d\n", parentMST[i] + 1, i + 1);
    }

    free(parentMST);
    free(key);
    free(setMST);
}


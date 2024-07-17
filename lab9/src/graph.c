#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

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

static int CalcMin(const int numVertices, const unsigned int* dist, const char* sptSet) {
    unsigned int min = UINT_MAX;
    int minIndex = 0;
    for (int v = 0; v < numVertices; ++v) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

static void PrintDistances(const int numVertices, const unsigned int* dist) {
    for (int i = 0; i < numVertices; i++) {
        if (dist[i] == UINT_MAX) {
            printf("oo ");
        } else if (dist[i] > INT_MAX) {
            printf("INT_MAX+ ");
        } else {
            printf("%u ", dist[i]);
        }
    }
    printf("\n");
}

static bool IsOverflow(const int numVertices, const unsigned int* dist, const int end) {
    int OverflowCount = 0;
    for (int i = 0; i < numVertices; i++) {
        if (i != end && dist[i] >= INT_MAX && dist[i] != UINT_MAX) {
            OverflowCount += 1;
        }
    }
    if (dist[end] > INT_MAX && OverflowCount >= 2) {
        return true;
    }
    return false;
}

static void PrintShortestPath(const int numVertices, const unsigned int* dist, const int* prevVertex, const int start, const int end) {
    if (dist[end] == UINT_MAX) {
        printf("no path\n");
        return;
    }
    if (IsOverflow(numVertices, dist, end)) {
        printf("overflow\n");
        return;
    }

    printf("%d ", end + 1);
    if (end == start) {
        return;
    }
    int currentVertex = end;
    while (prevVertex[currentVertex] != start) {
        printf("%d ", prevVertex[currentVertex] + 1);
        currentVertex = prevVertex[currentVertex];
    }
    printf("%d\n", start + 1);
}

void Find(TGraph graph, const int start, const int end) {
    char* sptSet = calloc(graph->numVertices, sizeof(char));
    if (sptSet == NULL) {
        return;
    }
    unsigned int *dist = malloc(graph->numVertices * sizeof(unsigned int));
    if (dist == NULL) {
        free(sptSet);
        return;
    }
    int* prevVertex = calloc(graph->numVertices, sizeof(int));
    if (prevVertex == NULL) {
        free(dist);
        free(sptSet);
        return;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = UINT_MAX;
    }
    dist[start] = 0;

    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u = CalcMin(graph->numVertices, dist, sptSet);
        sptSet[u] = 1;
        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->GraphMatrix[u * graph->numVertices + v]) {
                if (!sptSet[v] && dist[u] != UINT_MAX && dist[u] + graph->GraphMatrix[u * graph->numVertices + v] < dist[v]) {
                    dist[v] = dist[u] + graph->GraphMatrix[u * graph->numVertices + v];
                    prevVertex[v] = u;
                }
            }
        }
    }

    PrintDistances(graph->numVertices, dist);
    PrintShortestPath(graph->numVertices, dist, prevVertex, start, end);

    free(dist);
    free(sptSet);
    free(prevVertex);
}

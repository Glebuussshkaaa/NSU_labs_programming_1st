#include "graph.h"
#include "subset.h"
#include <stdio.h>
#include <stdlib.h>

TGraph CreateGraph(const int vertexCount, const int edgeCount) {
    TGraph graph = malloc(sizeof(struct Graph));
    if (graph == NULL) {
        return NULL;
    }

    graph->VertexCount = vertexCount;
    graph->EdgeCount = edgeCount;

    graph->Edges = malloc(graph->EdgeCount * sizeof(struct Edge));
    if (graph->Edges == NULL) {
        free(graph);
        return NULL;
    }

    return graph;
}

static void SortEdgesAscending(TGraph graph) {
    int edgeCount = graph->EdgeCount;
    TEdge* edges = graph->Edges;
    for (int currentIndex = 1; currentIndex < edgeCount; ++currentIndex) {
        TEdge currentEdge = edges[currentIndex];
        int previousIndex = currentIndex - 1;
        while (previousIndex >= 0 && edges[previousIndex].Weight > currentEdge.Weight) {
            edges[previousIndex + 1] = edges[previousIndex];
            previousIndex = previousIndex - 1;
        }
        edges[previousIndex + 1] = currentEdge;
    }
}

void FindMST(TGraph graph) {
    SortEdgesAscending(graph);
    TSubset* subsets = malloc(graph->VertexCount * sizeof(TSubset));
    if (subsets == NULL) {
        return;
    }
    for (int v = 0; v < graph->VertexCount; ++v) {
        (subsets + v)->Root = v;
        (subsets + v)->Rank = 0;
    }
    TEdge* result = malloc((graph->VertexCount - 1) * sizeof(struct Edge));
    if (result == NULL) {
        free(subsets);
        return;
    }
    int vertexCount = 0;
    for (int e = 0; vertexCount < graph->VertexCount - 1 && e < graph->EdgeCount; ++e) {
        TEdge CurrentEdge = graph->Edges[e];
        int rootSrc = FindRootSubset(subsets, CurrentEdge.Src);
        int rootDest = FindRootSubset(subsets, CurrentEdge.Dest);
        if (rootSrc != rootDest) {
            result[vertexCount++] = CurrentEdge;
            UnionNodesSubset(subsets, rootSrc, rootDest);
        }
    }
    if (vertexCount == graph->VertexCount - 1) {
        for (int i = 0; i < vertexCount; ++i) {
            printf("%d %d\n", result[i].Src + 1, result[i].Dest + 1);
        }
    } else {
        printf("no spanning tree\n");
    }
    free(result);
    free(subsets);
}


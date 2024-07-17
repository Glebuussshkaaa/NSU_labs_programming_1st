#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int vertexCount;
    if (!scanf("%d", &vertexCount)) {
        return 0;
    }
    int edgeCount;
    if (!scanf("%d", &edgeCount)) {
        return 0;
    }
    if (vertexCount < 0 || vertexCount > 5000) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (edgeCount < 0 || edgeCount > vertexCount * (vertexCount - 1) / 2) {
        printf("bad number of edges\n");
        return 0;
    }
    if (vertexCount == 0 && edgeCount == 0) {
        printf("no spanning tree\n");
        return 0;
    }

    TGraph graph = CreateGraph(vertexCount, edgeCount);
    if (graph == NULL) {
        return 1;
    }
    for (int i = 0; i < edgeCount; ++i) {
        int src, dest;
        long long weight;
        if (scanf("%d %d %lld", &src, &dest, &weight) != 3) {
            printf("bad number of lines\n");
            free(graph->Edges);
            free(graph);
            return 0;
        }
        if (src < 1 || src > vertexCount || dest < 1 || dest > vertexCount) {
            printf("bad vertex\n");
            free(graph->Edges);
            free(graph);
            return 0;
        }
        if ( weight < 0 || weight > INT_MAX) {
            printf("bad length\n");
            free(graph->Edges);
            free(graph);
            return 0;
        }
        graph->Edges[i].Src = src - 1;
        graph->Edges[i].Dest = dest - 1;
        graph->Edges[i].Weight = (int)weight;
    }

    FindMST(graph);

    free(graph->Edges);
    free(graph);
    return 0;
}



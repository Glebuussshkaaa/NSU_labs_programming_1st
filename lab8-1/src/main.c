#include "prim.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int numVertices;
    if (scanf("%d", &numVertices) != 1) {
        return 0;
    }
    if (numVertices < 0 || numVertices > 5000) {
        printf("bad number of vertices\n");
        return 0;
    }

    int numEdges;
    if (scanf("%d", &numEdges) != 1) {
        return 0;
    }
    if (numEdges < 0 || numEdges > numVertices * (numVertices - 1) / 2) {
        printf("bad number of edges\n");
        return 0;
    }

    if (numVertices == 0 && numEdges == 0) {
        printf("no spanning tree\n");
        return 0;
    }
    if (numVertices - 1 > numEdges) {
        printf("no spanning tree\n");
        return 0;
    }

    TGraph graph = CreateGraph(numVertices);
    if (graph == NULL) {
        return 1;
    }

    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        long long weight;
        if (scanf("%d %d %lld", &src, &dest, &weight) != 3) {
            printf("bad number of lines\n");
            free(graph->GraphMatrix);
            free(graph);
            return 0;
        }
        if (src < 1 || src > numVertices || dest < 1 || dest > numVertices) {
            printf("bad vertex\n");
            free(graph->GraphMatrix);
            free(graph);
            return 0;
        }
        if ( weight < 0 || weight > INT_MAX) {
            printf("bad length\n");
            free(graph->GraphMatrix);
            free(graph);
            return 0;
        }

        graph->GraphMatrix[(src - 1) * numVertices + dest - 1] = weight;
        graph->GraphMatrix[(dest - 1) * numVertices + src - 1] = weight;

    }

    Find(graph);

    free(graph->GraphMatrix);
    free(graph);
    return 0;
}


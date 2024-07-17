#include <stdio.h>
#include <stdlib.h>

void topologicalSort(int N, char** graphMatrix, int* indegree);

int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("bad number of lines\n");
        return 0;
    }
    if (N < 0 || N > 2000) {
        printf("bad number of vertices\n");
        return 0;
    }

    int M;
    if (scanf("%d", &M) != 1) {
        printf("bad number of lines\n");
        return 0;
    }
    if (M < 0 || M > N * (N - 1) / 2) {
        printf("bad number of edges\n");
        return 0;
    }

    char** graphMatrix = malloc(N * sizeof(char*));
    if (graphMatrix == NULL) {
        return 0;
    }
    for (int i = 0; i < N; ++i) {
        graphMatrix[i] = calloc(N, sizeof(char));
        if (graphMatrix[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(graphMatrix[j]);
            }
            free(graphMatrix);
            return 0;
        }
    }

    int* indegree = (int*)calloc(N, sizeof(int));
    if (indegree == NULL) {
        for (int i = 0; i < N; ++i) {
            free(graphMatrix[i]);
        }
        free(graphMatrix);
        return 0;
    }


    for (int i = 0; i < M; ++i) {
        int startNode, endNode;
        if (scanf("%d %d", &startNode, &endNode) != 2) {
            printf("bad number of lines\n");
            for (int i = 0; i < N; ++i) {
                free(graphMatrix[i]);
            }
            free(graphMatrix);
            free(indegree);
            return 0;
        }
        if (startNode < 1 || startNode > N || endNode < 1 || endNode > N) {
            printf("bad vertex\n");
            for (int i = 0; i < N; ++i) {
                free(graphMatrix[i]);
            }
            free(graphMatrix);
            free(indegree);
            return 0;
        }

        graphMatrix[startNode - 1][endNode - 1] = 1;
        ++indegree[endNode - 1];
    }

    topologicalSort(N, graphMatrix, indegree);

    for (int i = 0; i < N; ++i) {
        free(graphMatrix[i]);
    }
    free(graphMatrix);
    free(indegree);

    return 0;
}


void topologicalSort(int N, char** graphMatrix, int* indegree) {
    int* queue = calloc(N, sizeof(int));
    if (queue == NULL) {
        return;
    }
    int* sortedVertices = calloc(N, sizeof(int));
    if (sortedVertices == NULL) {
        free(queue);
        return;
    }

    int queueEnd = 0;
    for (int i = 0; i < N; ++i) {
        if (indegree[i] == 0) {
            queue[queueEnd++] = i;
        }
    }
    int vertexCount = 0;
    while (queueEnd != 0) {
        int currentNode = queue[--queueEnd];
        sortedVertices[vertexCount++] = currentNode;

        for (int adjacentNode = 0; adjacentNode < N; ++adjacentNode) {
            if (graphMatrix[currentNode][adjacentNode] == 1) {
                --indegree[adjacentNode];
                if (indegree[adjacentNode] == 0) {
                    queue[queueEnd++] = adjacentNode;
                }
            }
        }
    }

    if (vertexCount != N) {
        printf("impossible to sort\n");
    } else {
        for (int i = 0; i < N; ++i) {
            printf("%d ", sortedVertices[i] + 1);
        }
    }

    free(queue);
    free(sortedVertices);
}


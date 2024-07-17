#pragma once

typedef struct Graph {
    int numVertices;
    unsigned int* GraphMatrix;
} *TGraph;

TGraph CreateGraph(const int numVertices);
void Find(TGraph graph, const int start, const int end);

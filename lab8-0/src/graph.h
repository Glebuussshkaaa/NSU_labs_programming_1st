#pragma once

typedef struct Edge {
    int Src;
    int Dest;
    int Weight;
} TEdge;

typedef struct Graph {
    int VertexCount;
    int EdgeCount;
    TEdge* Edges;
} *TGraph;

TGraph CreateGraph(const int vertexCount, const int edgeCount);
void FindMST(TGraph graph);


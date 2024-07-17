#pragma once

typedef struct Point {
    int x, y;
} Point;

int ComputeConvexHull(Point* points,  const int N);

void PrintConvexHull(const Point* points, const int numVertices);

void FreePoints(Point* points);

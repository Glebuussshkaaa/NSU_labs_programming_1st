#include "convexHull.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_POINTS 0
#define MAX_POINTS 100000

int main() {
    int N;
    if (!scanf("%d", &N)) {
        return 1;
    }
    if (N < MIN_POINTS || N > MAX_POINTS) {
        printf("bad number of Points\n");
        return 0;
    }
    if (N == 0) {
        return 0;
    }

    Point* points = malloc(N * sizeof(struct Point));
    if (!points) {
        return 1;
    }
    for(int i = 0; i < N; ++i) {
        if (scanf(" %d %d",&points[i].x,&points[i].y) != 2) {
            printf("bad number of lines\n");
            FreePoints(points);
            return 0;
        }
    }

    int numVertices = ComputeConvexHull(points, N);
    PrintConvexHull(points, numVertices);

    FreePoints(points);

    return 0;
}

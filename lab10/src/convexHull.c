#include "convexHull.h"
#include <stdio.h>
#include <stdlib.h>

static void SwapPoints(Point* firstPoint, Point* secondPoint) {
    Point temp = *firstPoint;
    *firstPoint = *secondPoint;
    *secondPoint = temp;
}

static double CalcVectorLengthSquared(const Point end, const Point start) {
    return ((double)end.x - start.x) * ((double)end.x - start.x) +
           ((double)end.y - start.y) * ((double)end.y - start.y);
}

static double CalcVectorProduct(const Point start, const Point firstEnd, const Point secondEnd) {
    return ((double)firstEnd.x - start.x) * ((double)secondEnd.y - start.y) -
           ((double)secondEnd.x - start.x) * ((double)firstEnd.y - start.y);
}

static int ComparePoints(const void *A, const void *B, void *context) {
    Point* referencePoint = (Point*)context;
    Point* firstPoint = (Point*)A;
    Point* secondPoint = (Point*)B;

    double vectorProduct = CalcVectorProduct(*referencePoint, *firstPoint, *secondPoint);

    if (vectorProduct == 0.0) {
        if (CalcVectorLengthSquared(*referencePoint, *secondPoint) >= CalcVectorLengthSquared(*referencePoint, *firstPoint)) {
            return -1;
        } else {
            return 1;
        }
    } else if (vectorProduct > 0) {
        return -1;
    }
    return 1;
}

static int FindMinIndexByX(const Point* points, const int N) {
    Point minPoint = points[0];
    int minIndex = 0;

    for (int i = 1; i < N; ++i) {
        if ((points[i].x < minPoint.x) || ((points[i].x == minPoint.x) && (points[i].y < minPoint.y))) {
            minPoint = points[i];
            minIndex = i;
        }
    }

    return minIndex;
}

static void SortPoints(Point* points, const int N) {
    int minIndex = FindMinIndexByX(points, N);

    SwapPoints(&points[0], &points[minIndex]);
    qsort_r(&points[1], N - 1, sizeof(Point), ComparePoints, &points[0]);
}

static int CheckCollinearity(const Point start, const Point firstEnd, const Point secondEnd) {
    return CalcVectorProduct(start, firstEnd, secondEnd) == 0;
}

static int RemoveCollinearPoints(Point* points, const int N) {
    int countPoints = 1;

    for (int i = 1; i < N; ++i) {
        while (i < N - 1 && CheckCollinearity(points[0], points[i], points[i + 1])) {
            ++i;
        }
        points[countPoints++] = points[i];
    }

    return countPoints;
}

void PrintConvexHull(const Point* points, const int numVertices) {
    for(int i = 0; i < numVertices; ++i) {
        printf("%d %d\n", points[i].x, points[i].y);
    }
}

int ComputeConvexHull(Point* points,  const int N) {
    int numPoints = N;

    SortPoints(points, numPoints);
    numPoints = RemoveCollinearPoints(points, N); // delete all but the furthest point

    if (numPoints < 3) {
        return numPoints;
    }

    int stackTop = 2;
    for(int i = 3; i < numPoints; ++i) {
        while (stackTop >= 1 && CalcVectorProduct(points[stackTop - 1], points[stackTop], points[i]) <= 0) {
            --stackTop;
        }
        points[++stackTop] = points[i];
    }

    return stackTop + 1;
}

void FreePoints(Point* points) {
    free(points);
}

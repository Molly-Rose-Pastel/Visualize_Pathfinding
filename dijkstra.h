#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "pathfindingalgorithm.h"

class Dijkstra : public PathfindingAlgorithm
{
public:
    Dijkstra();
public slots:
    void startAlgorithm();
    void callAlgorithm();
};

#endif // DIJKSTRA_H

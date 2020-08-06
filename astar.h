#ifndef ASTAR_H
#define ASTAR_H

#include "pathfindingalgorithm.h"

class AStar:public PathfindingAlgorithm {

public:
    AStar();
public slots:
    void startAlgorithm();
    void callAlgorithm();
};

#endif // ASTAR_H

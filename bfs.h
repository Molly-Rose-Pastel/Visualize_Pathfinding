#ifndef BFS_H
#define BFS_H

#include "pathfindingalgorithm.h"

class BFS : public PathfindingAlgorithm
{
public:
    BFS();
public slots:
    void startAlgorithm();
    void callAlgorithm();
};

#endif // BFS_H

#ifndef DFS_H
#define DFS_H

#include "pathfindingalgorithm.h"

class DFS : public PathfindingAlgorithm
{
public:
    DFS();
public slots:
    void startAlgorithm();
    void callAlgorithm();
};

#endif // DFS_H

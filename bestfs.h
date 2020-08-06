#ifndef BESTFS_H
#define BESTFS_H

#include "pathfindingalgorithm.h"

class BestFS : public PathfindingAlgorithm
{
public:
    BestFS();
public slots:
    void startAlgorithm();
    void callAlgorithm();
};

#endif // BESTFS_H

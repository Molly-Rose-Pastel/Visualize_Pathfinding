#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <list>
#include <QRandomGenerator>

#include "node.h"

class MazeGenerator
{
public:
    MazeGenerator();

    struct NodeMatrix{
        Node *nodes[40][26];
    };

    std::list<NodeMatrix> mainRooms;
    std::list<NodeMatrix> newRooms;

    int n = 4;

    Node *holes[40][26];
    Node *maze[40][26];

    std::list<int> randomNumbers;

    bool isGeneratingMaze = false;

public slots:

    void generateMaze();
    void clearNodes();
};

#endif // MAZEGENERATOR_H

#ifndef NAVIGATIONDATA_H
#define NAVIGATIONDATA_H

/* Qt Libraries */
#include <QLinkedList>
#include <qiterator.h>
#include <QTimer>

/* STL */
#include <unordered_map>

/* Custom Libraries */
#include "node.h"


class NavigationData
{
public:
    NavigationData();

    /**
     * @brief nodes
     * Raw array that holds the node-objects the pathfinding
     * algorithms use to navigate.
     * First element is the column, second element the row.
     */
    Node *nodes[40][26];
    Node *start;
    Node *finish;

    int loopCount = 0;
    int timerSpeed = 15;

    /**
     * @brief blockedList
     * Contains the nodes that are blocked/unavailable
     */
    QList<Node*> blockedList;
    /**
     * @brief forestList
     * Contains the nodes that have a forest/weight on them.
     */
    QList<Node*> forestList;
    /**
     * @brief iter
     * Iterator to iterate over QLists of type Node*.
     */
    QList<Node*>::iterator iter;


public slots:
    void createNodes();
    void loadMaze();
};

#endif // NAVIGATIONDATA_H

#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

/* Qt Libraries */
#include <QTimer>
#include <QLinkedList>
#include <qiterator.h>
#include <QObject>
#include <QGraphicsView>

/* STL */
#include <unordered_map>

/* Custom Libraries */
#include "node.h"

class PathfindingAlgorithm: public QObject{
    Q_OBJECT
public:
    PathfindingAlgorithm();

    QTimer *animationTimer;
    /**
     * @brief timerSpeed
     * Timer intervall in ms.
     */
    int timerSpeed = 15;
    /**
     * @brief loopCount
     * Counter variable to decrease the execution speed of the pathfinding
     * algorithm.
     */
    int loopCount = 0;

    /**
     * @brief nodes
     * pointer to the array that contains the nodes the
     * algorithms naviagte on.
     */
    Node *(*nodes)[26];

    /**
     * @brief visited
     * Raw array that contains the nodes the current alogrithm has
     * already explored.
     */
    Node *visited[40][26];
    /**
     * @brief cameFrom
     * Raw array that contains the nodes the current algorithm has
     * come from.
     */
    Node *cameFrom[40][26];
    /**
     * @brief start
     * Pointer to the start (the green one) node.
     */
    Node *start;
    /**
     * @brief finish
     * Pointer to the finish (the red one) node.
     */
    Node *finish;
    /**
     * @brief current
     * Pointer to the node the current algorithm is currently
     * exploring.
     */
    Node *current;
    /**
     * @brief up
     * Pointer to the node that is above the current node.
     */
    Node *up;
    /**
     * @brief left
     * Pointer to the node that is left to the current node.
     */
    Node *left;
    /**
     * @brief down
     * Pointer to the node that is beneath the current node.
     */
    Node *down;
    /**
     * @brief right
     * Pointer to the node that is right to the current node.
     */
    Node *right;
    /**
     * @brief frontier
     * Contains the nodes that are in the frontier of the current
     * algorithm. Frontier are the nodes that still have to be
     * explored.
     */
    QList<Node*> frontier;
    /**
     * @brief pathway
     * Contains the nodes that form the pathway from start to
     * finish.
     */
    QList<Node*> pathway;
    /**
     * @brief cost_so_far
     * Holds the movement costs of the explored nodes for Dijkstra and A*.
     */
    /**
     * @brief iter
     * Iterator to iterate over QLists of type Node*.
     */
    QList<Node*>::iterator iter;
    /**
     * @brief cost_so_far
     * priority queue to add up the travel cost.
     */
    std::unordered_map<Node*, int> cost_so_far;
    /**
     * @brief lines
     * Contains the line-points of the drawed line.
     */
    QList<QGraphicsLineItem*> lines;
    /**
     * @brief lineIter
     * Iterator to iterate over QLists of type QGraphicsLineItem*.
     */
    QList<QGraphicsLineItem*>::iterator lineIter;

public slots:
    virtual void startAlgorithm()=0;
    virtual void callAlgorithm()=0;
    void drawPath();
    void clearPath();

};

#endif // PATHFINDINGALGORITHM_H

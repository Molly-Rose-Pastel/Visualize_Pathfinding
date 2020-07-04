#ifndef GAME_H
#define GAME_H

/* Qt Libraries */
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QObject>
#include <QDebug>
#include <QLinkedList>
#include <qiterator.h>
#include <QTimer>

/* STL */
#include <unordered_map>

/* Custom Libraries */
#include "menu.h"
#include "node.h"

class MainProgram: public QGraphicsView{
    Q_OBJECT
public:
    MainProgram(QWidget *parent=0);


    /* data structures */

    /**
     * @brief nodes
     * Raw array that holds the node-objects the pathfinding
     * algorithms use to navigate.
     * First element is the column, second element the row.
     */
    Node *nodes[40][26];
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

    /* Pathfinding */

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

    QTimer *DepthFirstSearch_animationTimer;
    QTimer *BreadthFirstSearch_animationTimer;
    QTimer *BestFirstSearch_animationTimer;
    QTimer *Dijkstra_animationTimer;
    QTimer *Astar_animationTimer;

    /**
     * @brief timerSpeed
     * Timer intervall in ms.
     */
    int timerSpeed = 15;
    /**
     * @brief loopCount
     * Counter variable to decrease the execution speed of the pathfinding
     * algorithms.
     */
    int loopCount = 0;

    /**
     * @brief cost_so_far
     * Holds the movement costs of the explored nodes for Dijkstra and A*.
     */
    std::unordered_map<Node*, int> cost_so_far;

    /* Miscellaneous */

    /**
     * @brief scene
     * QGraphicsScene that is used for the visual representation of
     * graphic objects.
     */
    QGraphicsScene * scene;
    /**
     * @brief menu
     * Pointer to the menu object.
     */
    Menu *menu;
    /**
     * @brief menuProxy
     * Pointer to a QGraphicsProxyWidget object.
     * A QGraphicsProxyWidget is needed to display non-QGraphics items in a
     * QGraphicsScene.
     */
    QGraphicsProxyWidget * menuProxy;
    /**
     * @brief moveStart
     * Flag to determine if the start-node is currently being moved.
     */
    bool moveStart = false;
    /**
     * @brief moveFinish
     * Flag to determine if the finish-node is currently being moved.
     */
    bool moveFinish = false;
    /**
     * @brief isSearching
     * Flag to determine if an algorithm is currently being exectued.
     */
    bool isSearching = false;

public slots:
    void resizeEvent(QResizeEvent *event);
    void createNodes();

    void start_DepthFirstSearch();
    void call_DepthFirstSearch();
    void start_BreadthFirstSearch();
    void call_BreadthFirstSearch();
    void start_BestFirstSearch();
    void call_BestFirstSearch();
    void start_Dijkstra();
    void call_Dijkstra();
    void start_Astar();
    void call_Astar();

    void drawPath();
    void loadMaze();
};

#endif // GAME_H

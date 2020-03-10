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

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent=0);


    /* data structures */

    Node *nodes[40][26];
    QList<Node*> blockedList;
    QList<Node*> forestList;

    QList<Node*>::iterator iter;
    QList<QGraphicsLineItem*> lines;
    QList<QGraphicsLineItem*>::iterator lineIter;

    /* Pathfinding */
    Node *visited[40][26];
    Node *cameFrom[40][26];
    Node *start;
    Node *finish;
    Node *current;
    Node *up;
    Node *left;
    Node *down;
    Node *right;
    QList<Node*> frontier;
    QList<Node*> pathway;

    QTimer *DepthFirstSearch_animationTimer;
    QTimer *BreadthFirstSearch_animationTimer;
    QTimer *BestFirstSearch_animationTimer;
    QTimer *Dijkstra_animationTimer;
    QTimer *Astar_animationTimer;

    int timerSpeed = 15;
    int loopCount = 0;

    std::unordered_map<Node*, int> cost_so_far;

    /* Miscellaneous */
    QGraphicsScene * scene;
    Menu *menu;
    QGraphicsProxyWidget * menuProxy;
    bool moveStart = false;
    bool moveFinish = false;
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

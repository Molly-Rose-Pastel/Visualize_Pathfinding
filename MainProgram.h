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
#include "navigationdata.h"
#include "dfs.h"
#include "bfs.h"
#include "bestfs.h"
#include "dijkstra.h"
#include "astar.h"
#include "mazegenerator.h"

class MainProgram: public QGraphicsView{
    Q_OBJECT
public:
    MainProgram(QWidget *parent=0);
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

    NavigationData * navigation;

    BFS * bfs;
    DFS * dfs;
    BestFS * best;
    Dijkstra * dijkstra;
    AStar * astar;

    MazeGenerator *mazeGen;

public slots:
    void resizeEvent(QResizeEvent *event);
    void createObjects();
};

#endif // GAME_H

#include "MainProgram.h"

/**
 * @brief MainProgram::MainProgram
 * The MainProgram instanciates all objects that are used in the Application.
 * @param QWidget
 * @return none
 */
MainProgram::MainProgram(QWidget*)
{
    scene = new QGraphicsScene;
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setStickyFocus(true);
    /* change this to a 16:9 resolution */
    scene->setSceneRect(QRect(-240,0,1920,1080));
    setScene(scene);

    setBackgroundBrush(QBrush(QColor(qRgba(240,248,255,255))));
    QGraphicsView::fitInView(scene->sceneRect(), Qt::KeepAspectRatio);



}

/**
 * @brief MainProgram::resizeEvent
 * When the window the program runs in receives a resize event, this function
 * will resize the QGraphicsView to fit the new window size while keeping
 * the aspect ratio the QGraphicsView and its elements where designed in.
 * @param event
 */
void MainProgram::resizeEvent(QResizeEvent *event)
{
    if(event->type() == QEvent::Resize){
        QGraphicsView::fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainProgram::createObjects()
{
    navigation = new NavigationData;
    navigation->createNodes();

    menu = new Menu();
    menuProxy = scene->addWidget(menu);
    menu->setMouseTracking(true);

    bfs = new BFS();
    dfs = new DFS();
    best = new BestFS();
    dijkstra = new Dijkstra();
    astar = new AStar();

    mazeGen = new MazeGenerator;

    navigation->loadMaze();

}

#include <QApplication>
#include "MainProgram.h"

MainProgram * pMainProgram;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pMainProgram = new MainProgram();
    pMainProgram->createObjects();
    pMainProgram->show();

    return a.exec();
}

/**
 * @mainpage
 * <h1>Visualize Pathfinding</h1><br>
 */

/**
 * @page page1 Project Description
 * This application illustrates graphically how different pathfinding algorithms
 * work:
 * <p>
 * <a href="https://en.wikipedia.org/wiki/Breadth-first_search" target="_blank">
 * Breadth-First-Search</a>
 * <p><a href="https://en.wikipedia.org/wiki/Best-first_search" target="_blank">
 * Best-First-Search</a>
 * <p><a href="https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm" target="_blank">
 * Dijkstra's</a>
 * <p><a href="https://en.wikipedia.org/wiki/A*_search_algorithm" target="_blank">
 * A-Star</a>
 * <p>On a fixed size field the user can freely move a start and a finish node.<br>
 * Walls cannot be traversed.<br>
 * Forests add a weight to the node ( only applies to Dijkstra and A* ).<br>
 * The execution speed of the algorithm can be changed with a speed-slider.<br>
 * Explored nodes will be represented in a color and the nodes that still have<br>
 * to be explored (frontier) will be represented in a different color.<br>
 * Once the path has been found, a black line from start to finish will be drawn.<br>
 *
 * <p><img src="screenshot.png">
 *
 */


/**
 * @page page2 Class Diagram
 * <img src="PathfindingClassDiagram.png">
 */

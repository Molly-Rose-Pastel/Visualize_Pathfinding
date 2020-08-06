#include "pathfindingalgorithm.h"
#include "MainProgram.h"

extern MainProgram *pMainProgram;

PathfindingAlgorithm::PathfindingAlgorithm()
{

    animationTimer = new QTimer();
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(callAlgorithm()));
    animationTimer->setSingleShot(true);

    nodes = pMainProgram->navigation->nodes;

    start = pMainProgram->navigation->start;
    finish = pMainProgram->navigation->finish;
}

/**
 * @brief PathfindingAlgorithm::drawPath
 * Draws a black line from start to finish through the center of each node on
 * the current path
 */
void PathfindingAlgorithm::drawPath()
{
    current = finish;

    while(current != start){

        if(cameFrom[current->col][current->row] != nullptr){

            pathway.prepend(current);
            current = cameFrom[current->col][current->row];
            if(current == start){
                pathway.prepend(current);
            }

        }else{
            // tell the user that no pathway exists

            // set current to nullptr
            current = nullptr;
            break;
        }
    }


    /* draw line from center to center of each node*/
    if(!pathway.empty()){

        int x1, x2, y1, y2;

        iter = pathway.begin();
        while(iter != pathway.end()){

            x1 = 36*(*iter)->col + 18;
            y1 = 100 + 36*(*iter)->row + 18;

            ++iter;

            if(iter != pathway.end()){

                x2 = 36*(*iter)->col + 18;
                y2 = 100 + 36*(*iter)->row + 18;

                QGraphicsLineItem * line = new QGraphicsLineItem;
                pMainProgram->scene->addItem(line);
                line->setLine(x1,y1,x2,y2);
                line->setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                lines.append(line);

            }
        }
    }

}

void PathfindingAlgorithm::clearPath()
{
    /* clear pathway list */
    if(!pathway.empty()){
        pathway.clear();
    }

    /* clear frontier list */
    if(!frontier.empty()){
        frontier.clear();
    }

    /* reset cameFrom Matrix */
    for(int col = 0; col < 40; col++){
        for(int row = 0; row < 26; row++){
            cameFrom[col][row] = nullptr;
        }
    }

    /* set visited to NULL */
    for(int cols = 0; cols < 40; cols++){
        for(int rows = 0; rows < 26; rows++){
            visited[cols][rows] = nullptr;
        }
    }

    /* clear cost_so_far */
    cost_so_far.clear();

    /* destroy and clear lines */
    lineIter = lines.begin();
    while(lineIter != lines.end()){
        QGraphicsLineItem *pHelp = lines.first();
        delete pHelp;
        lineIter = lines.erase(lineIter);
    }
    lines.clear();

}

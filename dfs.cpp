#include "dfs.h"
#include "MainProgram.h"

extern MainProgram *pMainProgram;

DFS::DFS()
{

}

void DFS::startAlgorithm()
{
    start = nodes[pMainProgram->menu->lastStartCol][pMainProgram->menu->lastStartRow];
    finish = nodes[pMainProgram->menu->lastFinishCol][pMainProgram->menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);
    cost_so_far.insert({start, start->priority});

    pMainProgram->isSearching = true;

    callAlgorithm();
}

void DFS::callAlgorithm()
{
    ++loopCount;

    /* break the loop, if we either reached finish or the frontier-list is
     * empty */
    if(current == finish || frontier.empty()){
        animationTimer->stop();
        drawPath();
        pMainProgram->isSearching = false;
        return;
    }

    /* draw the current node as explored */
    if(current != start && current != finish &&
            current != nullptr && !current->isBlocked && !current->isForest){

        current->setExplored();
    }

    current = frontier.takeFirst();

    /* draw the current node as frontier */
    if(current != start && current != finish &&
            !current->isBlocked && !current->isForest){

        current->setFrontier();
    }

    visited[current->col][current->row] = current;

    /* now add all valid and unvisited adjacent nodes of current to the frontier */

    /* up */
    // check if it wasn't visited
    if(visited[current->col][current->row -1] == nullptr &&
            //check if it is within the matrix of all nodes
            (current->row - 1) >= 0 &&
            //check if it is unblocked
            !current->isBlocked ){

        frontier.prepend(nodes[current->col][current->row -1]);
        cameFrom[current->col][current->row -1] = current;

    }

    /* right */
    // check if it wasn't visited
    if(visited[current->col+1][current->row] == nullptr &&
            //check if it is within the matrix of all nodes
            (current->col+1) < 40 &&
            //check if it is unblocked
            !current->isBlocked ){

        frontier.prepend(nodes[current->col+1][current->row]);
        cameFrom[current->col+1][current->row] = current;

    }

    /* down */
    // check if it wasn't visited
    if(visited[current->col][current->row +1] == nullptr &&
            //check if it is within the matrix of all nodes
            (current->row + 1) < 26 &&
            //check if it is unblocked
            !current->isBlocked ){

        frontier.prepend(nodes[current->col][current->row +1]);
        cameFrom[current->col][current->row +1] = current;

    }

    /* left */
    // check if it wasn't visited
    if(visited[current->col-1][current->row] == nullptr &&
            //check if it is within the matrix of all nodes
            (current->col-1) >= 0 &&
            //check if it is unblocked
            !current->isBlocked ){

        frontier.prepend(nodes[current->col-1][current->row]);
        cameFrom[current->col-1][current->row] = current;

    }

    if(timerSpeed == 0 || loopCount%2 == 0){

        callAlgorithm();

    }else if(timerSpeed != 0){

        animationTimer->start(timerSpeed);
    }

}

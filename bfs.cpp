#include "bfs.h"
#include "MainProgram.h"

extern MainProgram *pMainProgram;

BFS::BFS()
{

}


void BFS::startAlgorithm()
{
    start = nodes[pMainProgram->menu->lastStartCol][pMainProgram->menu->lastStartRow];
    finish = nodes[pMainProgram->menu->lastFinishCol][pMainProgram->menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);
    cost_so_far.insert({start, start->priority});

    pMainProgram->isSearching = true;

    callAlgorithm();
}

void BFS::callAlgorithm()
{++loopCount;

    if(current == finish || frontier.isEmpty()){
        animationTimer->stop();
        drawPath();
        pMainProgram->isSearching = false;
        return;
    }

    /* take first node */
    current = frontier.takeFirst();
    if(current != start && current != finish &&
            !current->isBlocked && !current->isForest){

        current->setExplored();
    }

    /* check neighbours
     * for this we need to check if the neighbouring nodes are valid!
     * they could either be outside the area (meaning they dont exist)
     * or they could be blocked */


    /* up means row - 1*/
    // check if it wasn't visited
    if(visited[current->col][current->row -1] == nullptr &&
            //check if it is within the matrix of all nodes
            (current->row - 1) >= 0 &&
            //check if it is unblocked
            !current->isBlocked ){

        up = nodes[current->col][current->row-1];

        // add the just checked node to the visited Array and set its origin
        visited[current->col][current->row-1] = up;
        cameFrom[current->col][current->row-1] = current;


        // and append it to the frontier
        frontier.append(up);

        /* draw it as frontier if it is not blocked, not a forest and neither
         * start nor finish */
        if(up != start && up != finish && !up->isBlocked && !up->isForest){

            frontier.last()->setFrontier();
        }

    }

    /* right means col + 1*/
    // check if it wasn't visited
    if(visited[current->col + 1][current->row] == nullptr &&
            //check if it is within the matrix of all nodes
            (current->col + 1) < 40 &&
            //check if it is unblocked
            !current->isBlocked ){

        right = nodes[current->col+1][current->row];

        // add the just checked node to the visited Array
        visited[current->col+1][current->row] = right;
        cameFrom[current->col+1][current->row] = current;

        // and append it to the frontier
        frontier.append(nodes[current->col+1][current->row]);

        /* draw it as frontier if it is not blocked, not a forest and neither
         * start nor finish */
        if(right != start && right != finish && !right->isBlocked &&
                !right->isForest){

            right->setFrontier();
        }

    }

    /* down means row + 1*/

    // check if it wasn't visited
    if(visited[current->col][current->row +1] == nullptr &&
            //check if it is within the matrix of all nodes
            (current->row + 1) < 26 &&
            //check if it is unblocked
            !current->isBlocked ){

        down = nodes[current->col][current->row+1];

        // add the just checked node to the visited Array
        visited[current->col][current->row+1] = down;
        cameFrom[current->col][current->row+1] = current;

        // and append it to the frontier
        frontier.append(nodes[current->col][current->row+1]);

        /* draw it as frontier if it is not blocked, not a forest and neither
         * start nor finish */
        if(down != start && down != finish &&!down->isBlocked &&
                !down->isForest){

            down->setFrontier();
        }

    }

    /* left means col - 1*/

    // check if it wasn't visited
    if(visited[current->col - 1][current->row] == nullptr &&
            //check if it is within the matrix of all nodes
            (current->col - 1) >= 0 &&
            //check if it is unblocked
            !current->isBlocked ){

        left = nodes[current->col-1][current->row];

        // add the just checked node to the visited Array
        visited[current->col-1][current->row] = left;
        cameFrom[current->col-1][current->row] = current;

        // and append it to the frontier
        frontier.append(nodes[current->col-1][current->row]);

        /* draw it as frontier if it is not blocked, not a forest and neither
         * start nor finish */
        if(left != start && left != finish && !left->isBlocked &&
                !left->isForest){

            left->setFrontier();
        }

    }

    if(timerSpeed == 0 || loopCount%2 == 0){

        callAlgorithm();

    }else if(timerSpeed != 0){

        animationTimer->start(timerSpeed);
    }

}

#include "astar.h"
#include "MainProgram.h"

extern MainProgram *pMainProgram;

AStar::AStar()
{

}

void AStar::startAlgorithm()
{
    start = nodes[pMainProgram->menu->lastStartCol][pMainProgram->menu->lastStartRow];
    finish = nodes[pMainProgram->menu->lastFinishCol][pMainProgram->menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);
    cost_so_far.insert({start, start->priority});

    pMainProgram->isSearching = true;

    callAlgorithm();
}

void AStar::callAlgorithm()
{
    ++loopCount;

    if(current == finish || frontier.empty()){
        animationTimer->stop();
        drawPath();
        pMainProgram->isSearching = false;
        return;
    }
    current = frontier.takeFirst();

    if(current != start && current != finish &&
            current != nullptr && !current->isBlocked && !current->isForest){

        current->setExplored();
    }
    /* up */
    //check if it exists
    if(current->row-1 >= 0 &&
            //check if it is not blocked
            !nodes[current->col][current->row-1]->isBlocked){

        up = nodes[current->col][current->row -1];

        auto search = cost_so_far.find(current);
        int newCost = search->second + abs(current->col - up->col) +
                abs(current->row - up->row) + up->weight;
        search = cost_so_far.find(up);

        if(search == cost_so_far.end()){

            up->priority = newCost + abs(finish->col - up->col) +
                    abs(finish->row - up->row);

            cost_so_far.insert({up, newCost});

            cameFrom[up->col][up->row] = current;
            frontier.prepend(up);
            if(up != start && up != finish && !up->isForest){

                up->setFrontier();
            }

        }else if(newCost < search->second){

            search->second = newCost;
            up->priority = newCost+ abs(finish->col - up->col) +
                    abs(finish->row - up->row);
            cameFrom[up->col][up->row] = current;
            frontier.prepend(up);
            if(up != start && up != finish && !up->isForest){

                up->setFrontier();
            }
        }

    }

    /* right */
    //check if it exists
    if(current->col+1 < 40 &&
            //check if it is not blocked
            !nodes[current->col+1][current->row]->isBlocked){

        right = nodes[current->col+1][current->row];

        auto search = cost_so_far.find(current);
        int newCost = search->second + abs(current->col - right->col) +
                abs(current->row - right->row) + right->weight;
        search = cost_so_far.find(right);

        if(search == cost_so_far.end()){

            right->priority = newCost + abs(right->col - finish->col)+
                    abs(right->row - finish->row);
            cost_so_far.insert({right, newCost});
            cameFrom[right->col][right->row] = current;
            frontier.prepend(right);
            if(right != start && right != finish && !right->isForest){

                right->setFrontier();
            }

        }else if(newCost < search->second){

            search->second = newCost;
            right->priority = newCost+ abs(right->col - finish->col)+
                    abs(right->row - finish->row);
            cameFrom[right->col][right->row] = current;
            frontier.prepend(right);
            if(right != start && right != finish && !right->isForest){

                right->setFrontier();
            }
        }
    }

    /* down */
    //check if it exists
    if(current->row+1 < 26 &&
            //check if it is not blocked
            !nodes[current->col][current->row+1]->isBlocked){

        down = nodes[current->col][current->row+1];

        auto search = cost_so_far.find(current);
        int newCost = search->second + abs(current->col - down->col) +
                abs(current->row - down->row) + down->weight;
        search = cost_so_far.find(down);

        if(search == cost_so_far.end()){

            down->priority = newCost + abs(down->col - finish->col)+
                    abs(down->row - finish->row);
            cost_so_far.insert({down, newCost});
            cameFrom[down->col][down->row] = current;
            frontier.prepend(down);
            if(down != start && down != finish && !down->isForest){

                down->setFrontier();
            }

        }else if(newCost < search->second){

            search->second = newCost;
            down->priority = newCost+ abs(down->col - finish->col)+
                    abs(down->row - finish->row);
            cameFrom[down->col][down->row] = current;
            frontier.prepend(down);
            if(down != start && down != finish && !down->isForest){

                down->setFrontier();
            }
        }
    }

    /* left */
    //check if it exists
    if(current->col-1 >= 0 &&
            //check if it is not blocked
            !nodes[current->col-1][current->row]->isBlocked){

        left = nodes[current->col-1][current->row];

        auto search = cost_so_far.find(current);
        int newCost = search->second + abs(current->col - left->col) +
                abs(current->row - left->row) + left->weight;
        search = cost_so_far.find(left);

        if(search == cost_so_far.end()){

            left->priority = newCost + abs(left->col - finish->col)+
                    abs(left->row - finish->row);
            cost_so_far.insert({left, newCost});
            cameFrom[left->col][left->row] = current;
            frontier.prepend(left);
            if(left != start && left != finish && !left->isForest){

                left->setFrontier();
            }

        }else if(newCost < search->second){

            search->second = newCost;
            left->priority = newCost+ abs(left->col - finish->col)+
                    abs(left->row - finish->row);
            cameFrom[left->col][left->row] = current;
            frontier.prepend(left);
            if(left != start && left != finish && !left->isForest){

                left->setFrontier();
            }
        }
    }

    std::stable_sort(std::begin(frontier), std::end(frontier),
                     [](const Node *a, const Node *b){

        return a->priority < b->priority;
    });

    if(timerSpeed == 0 || loopCount%2 == 0){
        callAlgorithm();
    }else if(timerSpeed != 0){
        animationTimer->start(timerSpeed);
    }


}

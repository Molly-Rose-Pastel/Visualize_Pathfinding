#include "dijkstra.h"
#include "MainProgram.h"

extern MainProgram *pMainProgram;

Dijkstra::Dijkstra()
{

}

void Dijkstra::startAlgorithm()
{
    start = nodes[pMainProgram->menu->lastStartCol][pMainProgram->menu->lastStartRow];
    finish = nodes[pMainProgram->menu->lastFinishCol][pMainProgram->menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);
    cost_so_far.insert({start, start->priority});

    pMainProgram->isSearching = true;

    callAlgorithm();
}

void Dijkstra::callAlgorithm()
{
    ++loopCount;

    /* we add valid nodes ( = they exist and are not blocked ) when
     * the new path to finish is better than the previous path*/

    current = frontier.first();

    if(current == finish || frontier.empty()){
        animationTimer->stop();
        drawPath();
        pMainProgram->isSearching = false;
        return;
    }
    frontier.pop_front();

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

            cost_so_far.insert({up, newCost});
            up->priority = newCost;
            cameFrom[up->col][up->row] = current;
            frontier.prepend(up);
            if(up != start && up != finish && !up->isForest){

                up->setFrontier();
            }

        }else if(newCost < search->second){

            search->second = newCost;
            up->priority = newCost;
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

            cost_so_far.insert({right, newCost});
            right->priority = newCost;
            cameFrom[right->col][right->row] = current;
            frontier.prepend(right);
            if(right != start && right != finish && !right->isForest){

                right->setFrontier();
            }

        }else if(newCost < search->second){

            search->second = newCost;
            right->priority = newCost;
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

            cost_so_far.insert({down, newCost});
            down->priority = newCost;
            cameFrom[down->col][down->row] = current;
            frontier.prepend(down);
            if(down != start && down != finish && !down->isForest){

                down->setFrontier();
            }

        }else if(newCost < search->second){

            search->second = newCost;
            down->priority = newCost;
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

            cost_so_far.insert({left, newCost});
            left->priority = newCost;
            cameFrom[left->col][left->row] = current;
            frontier.prepend(left);
            if(left != start && left != finish && !left->isForest){

                left->setFrontier();
            }

        }else if(newCost < search->second){

            search->second = newCost;
            left->priority = newCost;
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

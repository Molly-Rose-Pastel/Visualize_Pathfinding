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
    scene->setSceneRect(QRect(0,0,1440,1080));
    setScene(scene);

    setBackgroundBrush(QBrush(QColor(qRgba(255,255,255,255))));
    QGraphicsView::fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    menu = new Menu();
    menuProxy = scene->addWidget(menu);
    menu->setMouseTracking(true);


    DepthFirstSearch_animationTimer = new QTimer(this);
    connect(DepthFirstSearch_animationTimer, SIGNAL(timeout()), this,
            SLOT(call_DepthFirstSearch()));
    DepthFirstSearch_animationTimer->setSingleShot(true);

    BreadthFirstSearch_animationTimer = new QTimer(this);
    connect(BreadthFirstSearch_animationTimer, SIGNAL(timeout()), this,
            SLOT(call_BreadthFirstSearch()));
    BreadthFirstSearch_animationTimer->setSingleShot(true);

    BestFirstSearch_animationTimer = new QTimer(this);
    connect(BestFirstSearch_animationTimer, SIGNAL(timeout()), this,
            SLOT(call_BestFirstSearch()));
    BestFirstSearch_animationTimer->setSingleShot(true);

    Dijkstra_animationTimer = new QTimer(this);
    connect(Dijkstra_animationTimer, SIGNAL(timeout()), this,
            SLOT(call_Dijkstra()));
    Dijkstra_animationTimer->setSingleShot(true);

    Astar_animationTimer = new QTimer(this);
    connect(Astar_animationTimer, SIGNAL(timeout()), this,
            SLOT(call_Astar()));
    Astar_animationTimer->setSingleShot(true);

    createNodes();
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

/**
 * @brief MainProgram::createNodes
 * Creates the grid of nodes the pathfinding algorithms use to navigate.
 * Also loads a preset of walls and forests.
 */
void MainProgram::createNodes()
{
    /* this loop creates the visual representations of the nodes, adds them to
     * the scene and puts them into a data structure */
    for(int cols=0; cols < 40; cols++){
        for(int rows=0; rows < 26; rows++){
            Node * node = new Node();
            node->col = cols;
            node->row = rows;
            node->setRect(36*cols,100 + 36*rows,36,36);
            scene->addItem(node);
            nodes[cols][rows] = node;
        }
    }



    loadMaze();

}

/**
 * @brief MainProgram::start_DepthFirstSearch
 * Sets the start and finish node for the DFS algorithm and then starts the
 * timer that controls each iteration of the algorithm.
 */
void MainProgram::start_DepthFirstSearch()
{
    start = nodes[menu->lastStartCol][menu->lastStartRow];
    finish = nodes[menu->lastFinishCol][menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);

    isSearching = true;

    call_DepthFirstSearch();
}

/**
 * @brief MainProgram::call_DepthFirstSearch
 * Contains the DFS-algorithm.
 * Calling this once executes one iteration of the algorithm.
 * Counts up the calls and only executes every other call.
 * This is to slow down the execution speed of the algorithm because
 * in the webassembly deployment of the program the timer Intervalls
 * lose precision and are executed faster than they should be.
  */
void MainProgram::call_DepthFirstSearch()
{
    ++loopCount;

    /* break the loop, if we either reached finish or the frontier-list is
     * empty */
    if(current == finish || frontier.empty()){
        BreadthFirstSearch_animationTimer->stop();
        drawPath();
        isSearching = false;
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

        call_DepthFirstSearch();

    }else if(timerSpeed != 0){

        DepthFirstSearch_animationTimer->start(timerSpeed);
    }
}

/**
 * @brief MainProgram::start_BreadthFirstSearch
 * Sets the start and finish node for the BFS algorithm and then starts the
 * timer that controls each iteration of the algorithm.
 */
void MainProgram::start_BreadthFirstSearch()
{
    start = nodes[menu->lastStartCol][menu->lastStartRow];
    finish = nodes[menu->lastFinishCol][menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);

    isSearching = true;

    call_BreadthFirstSearch();
}

/**
 * @brief MainProgram::call_BreadthFirstSearch
 * Contains the BFS-algorithm.
 * Calling this once executes one iteration of the algorithm.
 * Counts up the calls and only executes every other call.
 * This is to slow down the execution speed of the algorithm because
 * in the webassembly deployment of the program the timer Intervalls
 * lose precision and are executed faster than they should be.
 */
void MainProgram::call_BreadthFirstSearch()
{
    ++loopCount;

    if(current == finish || frontier.isEmpty()){
        BreadthFirstSearch_animationTimer->stop();
        drawPath();
        isSearching = false;
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

        call_BreadthFirstSearch();

    }else if(timerSpeed != 0){

        BreadthFirstSearch_animationTimer->start(timerSpeed);
    }

}

/**
 * @brief MainProgram::start_BestFirstSearch
 * Sets the start and finish node for the BestFS algorithm and then starts the
 * timer that controls each iteration of the algorithm.
 */
void MainProgram::start_BestFirstSearch()
{
    start = nodes[menu->lastStartCol][menu->lastStartRow];
    finish = nodes[menu->lastFinishCol][menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);

    isSearching = true;

    call_BestFirstSearch();
}

/**
 * @brief MainProgram::call_BestFirstSearch
 * Contains the BestFS-algorithm.
 * Calling this once executes one iteration of the algorithm.
 * Counts up the calls and only executes every other call.
 * This is to slow down the execution speed of the algorithm because
 * in the webassembly deployment of the program the timer Intervalls
 * lose precision and are executed faster than they should be.
 */
void MainProgram::call_BestFirstSearch()
{
    ++loopCount;

    if(current == finish || frontier.isEmpty()){
        BestFirstSearch_animationTimer->stop();
        drawPath();
        isSearching = false;
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

        // add the just checked node to the visited Array
        visited[current->col][current->row-1] = up;
        cameFrom[current->col][current->row-1] = current;

        /* set priority */
        up->priority = abs(up->col - finish->col) +
                abs(up->row - finish->row);

        // and append it to the frontier
        frontier.append(nodes[current->col][current->row-1]);

        /* draw it as frontier if it is not blocked, not a forest and neither
         * start nor finish */
        if(up != start && up != finish &&
                !up->isBlocked && !up->isForest){

            up->setFrontier();
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

        /* set priority */
        right->priority = abs(right->col - finish->col) +
                abs(right->row - finish->row);

        // and append it to the frontier
        frontier.append(nodes[current->col+1][current->row]);

        /* draw it as frontier if it is not blocked, not a forest and neither
         * start nor finish */
        if(right != start && right != finish &&
                !right->isBlocked && !right->isForest){

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

        /* set priority */
        down->priority = abs(down->col - finish->col) +
                abs(down->row - finish->row);

        // and append it to the frontier
        frontier.append(nodes[current->col][current->row+1]);

        /* draw it as frontier if it is not blocked, not a forest and neither
         * start nor finish */
        if(down != start && down != finish &&
                !down->isBlocked && !down->isForest){

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

        left->priority = abs(left->col - finish->col) +
                abs(left->row - finish->row);

        // and append it to the frontier
        frontier.append(nodes[current->col-1][current->row]);


        /* draw it as frontier if it is not blocked, not a forest and neither
         * start nor finish */
        if(left != start && left != finish &&
                !left->isBlocked && !left->isForest){

            left->setFrontier();
        }

    }

    std::stable_sort(std::begin(frontier), std::end(frontier),
                     [](const Node *a, const Node *b){

        return a->priority < b->priority;
    });

    if(timerSpeed == 0 || loopCount%2 == 0){

        call_BestFirstSearch();

    }else if(timerSpeed != 0){

        BestFirstSearch_animationTimer->start(timerSpeed);
    }
}

/**
 * @brief MainProgram::start_Dijkstra
 * Sets the start and finish node for the Dijkstra algorithm and then starts
 * the timer that controls each iteration of the algorithm.
 */
void MainProgram::start_Dijkstra()
{
    start = nodes[menu->lastStartCol][menu->lastStartRow];
    finish = nodes[menu->lastFinishCol][menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);
    cost_so_far.insert({start, start->priority});

    isSearching = true;

    call_Dijkstra();
}

/**
 * @brief MainProgram::call_Dijkstra
 * Contains the Dijkstra-algorithm.
 * Calling this once executes one iteration of the algorithm.
 * Counts up the calls and only executes every other call.
 * This is to slow down the execution speed of the algorithm because
 * in the webassembly deployment of the program the timer Intervalls
 * lose precision and are executed faster than they should be.
 */
void MainProgram::call_Dijkstra()
{
    ++loopCount;

    /* we add valid nodes ( = they exist and are not blocked ) when
     * the new path to finish is better than the previous path*/

    current = frontier.first();

    if(current == finish || frontier.empty()){
        Dijkstra_animationTimer->stop();
        drawPath();
        isSearching = false;
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

        call_Dijkstra();
    }else if(timerSpeed != 0){

        Dijkstra_animationTimer->start(timerSpeed);
    }

}

/**
 * @brief MainProgram::start_Astar
 * Sets the start and finish node for the AStar algorithm and then starts
 * the timer that controls each iteration of the algorithm.
 */
void MainProgram::start_Astar()
{
    start = nodes[menu->lastStartCol][menu->lastStartRow];
    finish = nodes[menu->lastFinishCol][menu->lastFinishRow];

    visited[start->col][start->row] = start;
    frontier.append(start);
    cost_so_far.insert({start, start->priority});

    isSearching = true;

    call_Astar();
}

/**
 * @brief MainProgram::call_Astar
 * Contains the AStar-algorithm.
 * Calling this once executes one iteration of the algorithm.
 * Counts up the calls and only executes every other call.
 * This is to slow down the execution speed of the algorithm because
 * in the webassembly deployment of the program the timer Intervalls
 * lose precision and are executed faster than they should be.
 */
void MainProgram::call_Astar()
{
    ++loopCount;

    if(current == finish || frontier.empty()){
        Astar_animationTimer->stop();
        drawPath();
        isSearching = false;
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
        call_Astar();
    }else if(timerSpeed != 0){
        Astar_animationTimer->start(timerSpeed);
    }

}

/**
 * @brief MainProgram::drawPath
 * Draws a black line from start to finish through the center of each node on
 * the current path
 */
void MainProgram::drawPath()
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
                scene->addItem(line);
                line->setLine(x1,y1,x2,y2);
                line->setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                lines.append(line);

            }
        }
    }

}

/**
 * @brief MainProgram::loadMaze
 * loads a predefined configuration of walls, forests, start and finish.
 * Initially the idea was to have .txt files that contain different mazes but
 * in the webassembly deployment loading files from the server did not work
 * so a predefined maze is copy and pasted into a string variable.
 * toDo: investiagte the problem
 */
void MainProgram::loadMaze()
{
    //    QFile file("maze.txt");
    //    file.open(QIODevice::ReadOnly | QIODevice::Text);
    //    QString data;
    //    QTextStream stream(&file);
    //    data.append(stream.readAll());
    //    file.close();

    /* An issue in webassembly was that the .txt file would not be read, to overcome
     * this, the maze.txt is copy and pasted into a QString variable and then
     * parsed */

    QString maze = "clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,start,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,blocked,forest,clear,clear,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,blocked,forest,forest,clear,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,clear,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,finish,clear,clear,clear,clear,clear,clear,clear,blocked,clear,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,forest,blocked,forest,forest,forest,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,forest,blocked,forest,forest,clear,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,forest,blocked,forest,clear,clear,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,blocked,clear,clear,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,blocked,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,clear,";

    QString words[40][26];
    int col = 0, row = 0;
    QString word = "";
    for(int i=0; i<maze.size()-1; i++){

        if(maze[i] != ','){
            word += maze[i];

        }else if(maze[i] == ','){

            words[col][row] = word;
            word.clear();
            ++row;

            if(row >= 26){

                row = 0;
                ++col;
            }
        }
    }

    for(int cols = 0; cols < 40; cols++){
        for(int rows = 0; rows < 26; rows++){

            if(words[cols][rows] == "clear"){

                nodes[cols][rows]->unsetBlocked();

            }else if(words[cols][rows] == "finish"){

                finish = nodes[cols][rows];
                finish->setFinish();
                menu->lastFinishCol = cols;
                menu->lastFinishRow = rows;


            }else if(words[cols][rows] == "start"){

                start = nodes[cols][rows];
                start->setStart();
                menu->lastStartCol = cols;
                menu->lastStartRow = rows;

            }else if(words[cols][rows] == "forest"){

                nodes[cols][rows]->setForest();
                forestList.append(nodes[cols][rows]);

            }else if(words[cols][rows] == "blocked"){

                nodes[cols][rows]->setBlocked();
                blockedList.append(nodes[cols][rows]);
            }

        }
    }
}

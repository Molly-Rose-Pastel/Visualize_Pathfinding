#include "mazegenerator.h"
#include "MainProgram.h"

extern MainProgram *pMainProgram;

MazeGenerator::MazeGenerator()
{


}

void MazeGenerator::generateMaze()
{
    isGeneratingMaze = true;

label1:

    clearNodes();

    NodeMatrix firstRoom;

    for(int col=0; col<40;col++){
        for(int row=0; row<26;row++){
            firstRoom.nodes[col][row] =
                    pMainProgram->navigation->nodes[col][row];

            holes[col][row] = nullptr;
        }
    }

    mainRooms.push_back(firstRoom);

    /* we do the recursive division n-times */
    for(int count=0; count<n; count++){

        int whileCounter = 0;
        /* for each node-array in the mainRooms-list */
        auto iter = mainRooms.begin();

        while( (unsigned int) std::distance(mainRooms.begin(), iter) <
               mainRooms.size() ){

            randomNumbers.clear();
            whileCounter += 1;

            /* we want to divide this room, so we first must check the
             * cols to row - ration */


            /* count the columns in the current room */
            int cols = 0;
            int startCol = -1;
            for(int row=0; row<26; row++){
                for(int col=0; col<40; col++){

                    if( (*iter).nodes[col][row] != nullptr ){
                        if(startCol == -1){
                            startCol = col;
                        }
                        ++cols;
                    }
                }
                if (cols > 0){
                    break;
                }
            }

            /* count the rows in the current room */
            int rows = 0;
            int startRow = -1;
            for(int col=0; col<40; col++){
                for(int row=0; row<26; row++){

                    if( (*iter).nodes[col][row] != nullptr ){
                        if(startRow == -1){
                            startRow = row;
                        }
                        ++rows;
                    }
                }
                if (rows > 0){
                    break;
                }
            }

            iter++;

            /* variables for wall, room and hole creation */
            int randomCol = -1;
            int randomRow = -1;
            int randomHole = -1;
            bool flag = false;

            /* create vertical wall */
            if (cols > rows){

                std::uniform_int_distribution<unsigned int>
                        distribution;

                /* to get more evenly distributed rooms, the first iteration
                 * of walls should be closer to the center of the room they divide
                 * */
                if( count < 7 ){

                    distribution =
                            std::uniform_int_distribution<unsigned int>
                            (startCol + (int)(cols/2-1),
                             startCol + (int)((cols/2)));

                }else{

                    distribution =
                            std::uniform_int_distribution<unsigned int>
                            (startCol + (int)(cols/3),
                             startCol + (int)((cols/3)*2));
                }

                /* get a valid random column number to place the wall on */
                while(!flag){

                    randomCol =
                            (int)distribution(*QRandomGenerator::global());

                    auto iter = std::find(randomNumbers.begin(), randomNumbers.end(), randomCol);

                    /* we generated a random number and now we want to check
                     * our datastructure if it contains that number
                     * if it doesnt, we add it and move on
                     * if it does we generate random numbers until we have one
                     * that is not in that list */
                    while( iter != randomNumbers.end() and
                           randomNumbers.size() < (distribution.b() - distribution.a())){

                        randomCol =
                                (int)distribution(*QRandomGenerator::global());
                        iter = std::find(randomNumbers.begin(), randomNumbers.end(), randomCol);
                    }

                    randomNumbers.push_back(randomCol);


                    /* if the list size is greater than the possible amount of
                     * numbers within the parameters then we cannot generate
                     * a wall */

                    /* 2 possible approaches to solving this:
                     * - ditch the current wall and continue with what we have
                     * resulting in less rooms
                     * - restart the whole algorithm, hoping we wont reach this
                     * impass ( tried and it works kinda ok ... up to 500ms in
                     * worst cases )
                     */
                    if (randomNumbers.size() > (distribution.b() - distribution.a())){

                        mainRooms.clear();
                        newRooms.clear();
                        randomNumbers.clear();
                        goto label1;
                        //                        goto label2;
                    }

                    bool startFinishFlag = false;
                    bool holeFlag = false;
                    /* now we want to make sure that the wall we create is not
                     * created over the start or finish */
                    for( int r=startRow; r<startRow+rows; r++){

                        if ( pMainProgram->navigation->nodes[randomCol][r]->isStart or
                             pMainProgram->navigation->nodes[randomCol][r]->isFinish ){
                            startFinishFlag = false;
                            break;
                        }
                        startFinishFlag = true;
                    }

                    /* make sure the wall does not start or end on a hole in another wall */
                    bool prevHoleFlag = false;
                    bool nextHoleFlag = false;

                    if( startRow-1 >= 0 ){

                        if (holes[randomCol][startRow-1] != nullptr){

                            prevHoleFlag = false;
                        }else{

                            prevHoleFlag = true;
                        }

                    }else{

                        prevHoleFlag = true;
                    }

                    if( startRow+rows < 26 ){

                        if( holes[randomCol][startRow+rows] != nullptr){

                            nextHoleFlag = false;
                        }else{

                            nextHoleFlag = true;
                        }

                    }else{

                        nextHoleFlag = true;
                    }

                    if (prevHoleFlag and nextHoleFlag){

                        holeFlag = true;

                    }else{

                        holeFlag = false;
                    }


                    if( startFinishFlag and holeFlag ){

                        flag = true;

                    }else{

                        flag = false;
                    }
                }

                /* create hole in the wall */
                distribution =
                        std::uniform_int_distribution<unsigned int>(startRow ,
                                                                    startRow + rows-1);

                randomHole = (int)distribution(*QRandomGenerator::global());

                if( count < 3 ){

                    while( (randomHole == (startRow + (int)(rows)/2-1)) or
                           (randomHole == (startRow + (int)(rows)/2)) ){
                        randomHole = (int)distribution(*QRandomGenerator::global());
                    }

                }else{

                    if ( randomHole < (startRow + rows)/2 ) {

                        randomHole = startRow;

                    }else{

                        randomHole = startRow + rows - 1;
                    }
                }

                holes[randomCol][randomHole] =
                        pMainProgram->navigation->nodes[randomCol][randomHole];

            }
            /* create horizontal wall */
            else {

                std::uniform_int_distribution<unsigned int>
                        distribution;

                if( count < 7 ){

                    distribution =
                            std::uniform_int_distribution<unsigned int>
                            (startRow + (int)(rows/2-1),
                             startRow + (int)((rows/2)));

                }else{

                    distribution =
                            std::uniform_int_distribution<unsigned int>
                            (startRow + (int)(rows/3),
                             startRow + (int)((rows/3)*2));
                }

                while(!flag){

                    randomRow =
                            (int)distribution(*QRandomGenerator::global());

                    auto iter = std::find(randomNumbers.begin(), randomNumbers.end(), randomRow);


                    while( iter != randomNumbers.end() and
                           randomNumbers.size() < (distribution.b() - distribution.a())){

                        randomRow =
                                (int)distribution(*QRandomGenerator::global());
                        iter = std::find(randomNumbers.begin(), randomNumbers.end(), randomRow);
                    }

                    randomNumbers.push_back(randomRow);

                    /* if the numbers exists and the datastructure contains the
                     * exact amount of possible numbers within the distribution
                     * range it means we cannot find a number and have to start
                     * all over at the beginning of the algorithm */
                    if (randomNumbers.size() > (distribution.b() - distribution.a())){

                        mainRooms.clear();
                        newRooms.clear();
                        randomNumbers.clear();
                        goto label1;
                        //                        goto label2;

                    }

                    bool startFinishFlag = false;
                    bool holeFlag = false;

                    /* now we want to make sure that the wall we create is not
                     * created over the start or finish */
                    for( int c=startCol; c<startCol+cols; c++){

                        if ( pMainProgram->navigation->nodes[c][randomRow]->isStart or
                             pMainProgram->navigation->nodes[c][randomRow]->isFinish ){
                            startFinishFlag = false;
                            break;
                        }
                        startFinishFlag = true;
                    }

                    /* make sure the wall does not start or end on a hole in another wall */
                    bool prevHoleFlag = false;
                    bool nextHoleFlag = false;

                    if( startCol-1 >= 0 ){

                        if (holes[startCol-1][randomRow] != nullptr){

                            prevHoleFlag = false;
                        }else{

                            prevHoleFlag = true;
                        }

                    }else{

                        prevHoleFlag = true;
                    }

                    if( startCol+cols < 40 ){

                        if( holes[startCol+cols][randomRow] != nullptr){

                            nextHoleFlag = false;
                        }else{

                            nextHoleFlag = true;
                        }

                    }else{

                        nextHoleFlag = true;
                    }

                    if (prevHoleFlag and nextHoleFlag){

                        holeFlag = true;

                    }else{

                        holeFlag = false;
                    }


                    if( startFinishFlag and holeFlag ){

                        flag = true;

                    }else{

                        flag = false;
                    }

                }

                /* create hole in the wall */
                distribution =
                        std::uniform_int_distribution<unsigned int>(startCol,
                                                                    startCol + cols-1);

                randomHole = (int)distribution(*QRandomGenerator::global());

                if ( count < 3 ){

                    while ( (randomHole == (startCol + (int)(cols)/2-1)) or
                            (randomHole == (startCol + (int)(cols)/2)) ){
                        randomHole = (int)distribution(*QRandomGenerator::global());
                    }

                }else{

                    if ( randomHole < (startCol + cols)/2 ) {

                        randomHole = startCol;

                    }else{

                        randomHole = startCol + cols - 1;
                    }
                }

                holes[randomHole][randomRow] =
                        pMainProgram->navigation->nodes[randomHole][randomRow];
            }

            /* create new rooms */
            NodeMatrix room1;
            NodeMatrix room2;
            for(int c=0; c<40; c++){
                for(int r=0; r<26; r++){
                    room1.nodes[c][r] = nullptr;
                    room2.nodes[c][r] = nullptr;
                }
            }

            /* 2 rooms divided by a vertical wall */
            if (randomCol > -1){

                for(int c=startCol; c<randomCol; c++){
                    for(int r=startRow; r<startRow+rows; r++){

                        room1.nodes[c][r] = pMainProgram->navigation->nodes[c][r];
                    }
                }

                for(int c=randomCol+1; c<startCol+cols; c++){
                    for(int r=startRow; r<startRow+rows; r++){

                        room2.nodes[c][r] = pMainProgram->navigation->nodes[c][r];
                    }
                }
            }
            /* 2 rooms divided by a horizontal wall */
            else if(randomRow > -1){

                for(int c=startCol; c<startCol+cols; c++){
                    for(int r=startRow; r<randomRow; r++){

                        room1.nodes[c][r] = pMainProgram->navigation->nodes[c][r];
                    }
                }

                for(int c=startCol; c<startCol+cols; c++){
                    for(int r=randomRow+1; r<startRow+rows; r++){

                        room2.nodes[c][r] = pMainProgram->navigation->nodes[c][r];
                    }
                }

            }

            newRooms.push_back(room1);
            newRooms.push_back(room2);
        }

        mainRooms.clear();

label2:
        auto spliceIter = mainRooms.begin();
        mainRooms.splice(spliceIter, newRooms);

    }

    /* setup the maze with nullptr */
    for(int col=0; col<40; col++){
        for(int row=0; row<26; row++){

            maze[col][row] = nullptr;
        }
    }

    /* add rooms to the maze */
    auto mainIter = mainRooms.begin();
    while( (unsigned int) std::distance(mainRooms.begin(), mainIter) < mainRooms.size() ){
        for(int col=0; col<40; col++){
            for(int row=0; row<26; row++){

                if ( (*mainIter).nodes[col][row] != nullptr){
                    maze[col][row] = (*mainIter).nodes[col][row];
                }
            }
        }
        ++mainIter;
    }
    mainRooms.clear();

    /* add walls to the maze
     * the maze contains the nodes that are not walls
     * so all nodes in the maze-matrix that are nullptr are walls */
    for(int col=0; col<40; col++){
        for(int row=0; row<26; row++){

            if (maze[col][row] == nullptr){
                maze[col][row] = pMainProgram->navigation->nodes[col][row];
                maze[col][row]->setBlocked();
                pMainProgram->navigation->blockedList.append(maze[col][row]);
            }
        }
    }

    /* and finally add the holes to the walls */
    for(int col=0; col<40; col++){
        for(int row=0; row<26; row++){

            if(holes[col][row] != nullptr){

                maze[col][row]->unsetBlocked();
                pMainProgram->navigation->blockedList.removeOne(maze[col][row]);
            }
        }
    }

    isGeneratingMaze = false;
}

void MazeGenerator::clearNodes()
{
    for(int col=0; col<40; col++){
        for(int row=0; row<26; row++){
            if (!pMainProgram->navigation->nodes[col][row]->isStart and
                    !pMainProgram->navigation->nodes[col][row]->isFinish)

                pMainProgram->navigation->nodes[col][row]->unsetBlocked();
        }
    }

    pMainProgram->navigation->blockedList.clear();
    pMainProgram->navigation->forestList.clear();

    randomNumbers.clear();

}

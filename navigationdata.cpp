#include "navigationdata.h"
#include "MainProgram.h"

extern MainProgram *pMainProgram;

NavigationData::NavigationData()
{

}

void NavigationData::createNodes()
{
    /* this loop creates the visual representations of the nodes, adds them to
     * the scene and puts them into a data structure */
    for(int cols=0; cols < 40; cols++){
        for(int rows=0; rows < 26; rows++){
            Node * node = new Node();
            node->col = cols;
            node->row = rows;
            node->setRect(36*cols,100 + 36*rows,36,36);
            pMainProgram->scene->addItem(node);
            nodes[cols][rows] = node;
        }
    }
}

void NavigationData::loadMaze()
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
                pMainProgram->menu->lastFinishCol = cols;
                pMainProgram->menu->lastFinishRow = rows;
                pMainProgram->menu->finishNode = finish;


            }else if(words[cols][rows] == "start"){

                start = nodes[cols][rows];
                start->setStart();
                pMainProgram->menu->lastStartCol = cols;
                pMainProgram->menu->lastStartRow = rows;
                pMainProgram->menu->startNode = start;

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

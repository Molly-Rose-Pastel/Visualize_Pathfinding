#include "menu.h"
#include "ui_menu.h"
#include "MainProgram.h"
#include <QDebug>

extern MainProgram * pMainProgram;

/**
 * @brief Menu::Menu
 * Contains the buttons to select the algorithm, switch drawing of walls
 * and forests, a slider to change the speed with which the algorithms run
 * and clear buttons.
 * @param parent MainProgram
 */
Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setMouseTracking(true);
    setStyleSheet("background-color:rgba(0,0,0,0);");
    ui->bfsButton->click();
    ui->wallsCheckbox->click();

    QString buttonStyle("QPushButton {"
                        " border: 2px solid #8f8f91;"
                        "border-radius: 6px;"
                        "background-color: "
                        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                        "stop: 0 #daa520, stop: 1 #fff8dc);"
                        "min-width: 80px;"
                        "}"
                        "QPushButton:pressed {"
                        "background-color: "
                        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                        "stop: 0 #fff8dc, stop: 1 #daa520);"
                        "}"
                        "QPushButton:flat {"
                        "border: none;"
                        "}"
                        "QPushButton:default {"
                        "border-color: navy;"
                        "}");

    ui->startButton->setStyleSheet(buttonStyle);
    ui->wallsButton->setStyleSheet(buttonStyle);
    ui->forestButton->setStyleSheet(buttonStyle);
    ui->pathButton->setStyleSheet(buttonStyle);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::mousePressEvent(QMouseEvent *event)
{
    if(!pMainProgram->isSearching){


        /* clear the current path */
        on_pathButton_clicked();

        QPointF point;
        point.setX(event->localPos().x());
        point.setY(event->localPos().y());
        int col = point.x() / 36;
        int row = (point.y() - 100) / 36;

        if(col < 0 || col > 39 || row < 0 || row > 25){
            return;

        }else{

            switch(mouseState){
            case wall:
                if(event->buttons() & Qt::LeftButton){

                    if( pMainProgram->nodes[col][row]->isStart ){
                        mouseState = start;
                        return;

                    }else if( pMainProgram->nodes[col][row]->isFinish ){
                        mouseState = finish;
                        return;

                    }else if(pMainProgram->nodes[col][row]->isForest){

                        return;

                    }else if( !pMainProgram->nodes[col][row]->isBlocked ) {

                        pMainProgram->nodes[col][row]->setBlocked();
                        pMainProgram->blockedList.append(pMainProgram->nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( pMainProgram->nodes[col][row]->isStart ){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isFinish ){

                        return;

                    }else if(pMainProgram->nodes[col][row]->isForest){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isBlocked ) {

                        pMainProgram->nodes[col][row]->unsetBlocked();
                        pMainProgram->blockedList.removeOne(pMainProgram->nodes[col][row]);

                    }

                }
                break;

            case forest:
                if(event->buttons() & Qt::LeftButton){

                    if( pMainProgram->nodes[col][row]->isStart ){
                        mouseState = start;
                        return;

                    }else if( pMainProgram->nodes[col][row]->isFinish ){
                        mouseState = finish;
                        return;

                    }else if( !pMainProgram->nodes[col][row]->isBlocked ) {

                        pMainProgram->nodes[col][row]->setForest();
                        pMainProgram->forestList.append(pMainProgram->nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( pMainProgram->nodes[col][row]->isStart ){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isFinish ){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isBlocked ) {

                        return;

                    }else if( pMainProgram->nodes[col][row]->isForest ) {

                        pMainProgram->nodes[col][row]->unsetForest();
                        pMainProgram->forestList.removeOne(pMainProgram->nodes[col][row]);

                    }

                }
                break;

            case start:
                /* these do not exist, because to be in state start/finish
             * we have to hold the mouse button pressed. Thats why
             * we cannot perform a mousclick in state start/finish */
                break;

            case finish:
                /* these do not exist, because to be in state start/finish
             * we have to hold the mouse button pressed. Thats why
             * we cannot perform a mousclick in state start/finish */
                break;

            default:break;
            }

        }

    }

}

void Menu::mouseReleaseEvent(QMouseEvent *event)
{
    if(ui->forestCheckbox->checkState() & Qt::Checked){

        mouseState = forest;

    }else if(ui->wallsCheckbox->checkState() & Qt::Checked){

        mouseState = wall;

    }
}

void Menu::mouseMoveEvent(QMouseEvent *event)
{
    if(!pMainProgram->isSearching){

        QPointF point;
        point.setX(event->localPos().x());
        point.setY(event->localPos().y());
        int col = point.x() / 36;
        int row = (point.y() - 100) / 36;

        if(col < 0 || col > 39 || row < 0 || row > 25){
            return;

        }else{

            switch(mouseState){
            case wall:
                if(event->buttons() & Qt::LeftButton){

                    if( pMainProgram->nodes[col][row]->isStart ){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isFinish ){

                        return;

                    }else if(pMainProgram->nodes[col][row]->isForest){

                        return;

                    }else if( !pMainProgram->nodes[col][row]->isBlocked ) {

                        pMainProgram->nodes[col][row]->setBlocked();
                        pMainProgram->blockedList.append(pMainProgram->nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( pMainProgram->nodes[col][row]->isStart ){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isFinish ){

                        return;

                    }else if(pMainProgram->nodes[col][row]->isForest){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isBlocked ) {

                        pMainProgram->nodes[col][row]->unsetBlocked();
                        pMainProgram->blockedList.removeOne(pMainProgram->nodes[col][row]);

                    }

                }
                break;

            case forest:
                if(event->buttons() & Qt::LeftButton){

                    if( pMainProgram->nodes[col][row]->isStart ){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isFinish ){

                        return;

                    }else if( !pMainProgram->nodes[col][row]->isBlocked ) {

                        pMainProgram->nodes[col][row]->setForest();
                        pMainProgram->forestList.append(pMainProgram->nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( pMainProgram->nodes[col][row]->isStart ){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isFinish ){

                        return;

                    }else if( pMainProgram->nodes[col][row]->isBlocked ) {

                        return;

                    }else if( pMainProgram->nodes[col][row]->isForest ) {

                        pMainProgram->nodes[col][row]->unsetForest();
                        pMainProgram->forestList.removeOne(pMainProgram->nodes[col][row]);

                    }

                }
                break;

            case start:

                if( !pMainProgram->nodes[col][row]->isBlocked &&
                        !pMainProgram->nodes[col][row]->isFinish &&
                        !pMainProgram->nodes[col][row]->isForest){

                    pMainProgram->nodes[lastStartCol][lastStartRow]->unsetStart();
                    pMainProgram->nodes[col][row]->setStart();
                    lastStartCol = col;
                    lastStartRow = row;
                    pMainProgram->start = pMainProgram->nodes[col][row];

                }

                break;

            case finish:

                if( !pMainProgram->nodes[col][row]->isBlocked &&
                        !pMainProgram->nodes[col][row]->isStart &&
                        !pMainProgram->nodes[col][row]->isForest){

                    pMainProgram->nodes[lastFinishCol][lastFinishRow]->unsetFinish();
                    pMainProgram->nodes[col][row]->setFinish();
                    lastFinishCol = col;
                    lastFinishRow = row;
                    pMainProgram->finish = pMainProgram->nodes[col][row];

                }

                break;

            default:break;
            }

        }
    }
}

void Menu::on_dijkstraButton_clicked()
{

    selectedAlgorithm = dijkstra;

}

void Menu::on_astarButton_clicked()
{

    selectedAlgorithm = astar;

}

void Menu::on_bfsButton_clicked()
{

    selectedAlgorithm = bfs;

}

void Menu::on_bestfsButton_clicked()
{

    selectedAlgorithm = best;

}

void Menu::on_dfsButton_clicked()
{

    selectedAlgorithm = dfs;

}

void Menu::on_startButton_clicked()
{
    if(!pMainProgram->isSearching){

        pMainProgram->loopCount = 0;
        on_pathButton_clicked();

        switch(selectedAlgorithm){
        case bfs:
            pMainProgram->start_BreadthFirstSearch();
            break;
        case dfs:
            pMainProgram->start_DepthFirstSearch();;
            break;
        case best:
            pMainProgram->start_BestFirstSearch();
            break;
        case dijkstra:
            pMainProgram->start_Dijkstra();
            break;
        case astar:
            pMainProgram->start_Astar();
            break;

        default:break;
        }

    }
}

void Menu::on_wallsButton_clicked()
{
    if(!pMainProgram->isSearching){

        on_pathButton_clicked();

        pMainProgram->iter = pMainProgram->blockedList.begin();
        while(pMainProgram->iter != pMainProgram->blockedList.end()){

            (*pMainProgram->iter)->unsetBlocked();
            ++pMainProgram->iter;

        }
        pMainProgram->blockedList.clear();

    }
}

void Menu::on_forestButton_clicked()
{
    if(!pMainProgram->isSearching){

        on_pathButton_clicked();

        pMainProgram->iter = pMainProgram->forestList.begin();
        while(pMainProgram->iter != pMainProgram->forestList.end()){

            (*pMainProgram->iter)->unsetForest();
            ++pMainProgram->iter;

        }
        pMainProgram->forestList.clear();

    }
}

void Menu::on_pathButton_clicked()
{
    if(!pMainProgram->isSearching){

        /* clear pathway list */
        if(!pMainProgram->pathway.empty()){
            pMainProgram->pathway.clear();
        }

        /* clear frontier list */
        if(!pMainProgram->frontier.empty()){
            pMainProgram->frontier.clear();
        }

        /* reset colors of nodes */
        for(int col = 0; col < 40; col++){
            for(int row = 0; row < 26; row++){
                if(pMainProgram->nodes[col][row] != pMainProgram->start &&
                        pMainProgram->nodes[col][row] != pMainProgram->finish &&
                        !pMainProgram->nodes[col][row]->isBlocked &&
                        !pMainProgram->nodes[col][row]->isForest){

                    pMainProgram->nodes[col][row]->unsetBlocked();

                }
            }
        }

        /* reset cameFrom Matrix */
        for(int col = 0; col < 40; col++){
            for(int row = 0; row < 26; row++){
                pMainProgram->cameFrom[col][row] = nullptr;
            }
        }

        /* set visited to NULL */
        for(int cols = 0; cols < 40; cols++){
            for(int rows = 0; rows < 26; rows++){
                pMainProgram->visited[cols][rows] = nullptr;
            }
        }

        /* clear cost_so_far */
        pMainProgram->cost_so_far.clear();

        /* destroy and clear lines */
        pMainProgram->lineIter = pMainProgram->lines.begin();
        while(pMainProgram->lineIter != pMainProgram->lines.end()){
            QGraphicsLineItem *pHelp = pMainProgram->lines.first();
            delete pHelp;
            pMainProgram->lineIter = pMainProgram->lines.erase(pMainProgram->lineIter);
        }
        pMainProgram->lines.clear();
    }

}

void Menu::on_animationSpeedSlider_valueChanged(int value)
{
    if(value == 100){
        pMainProgram->timerSpeed = 0;
    }else{
        pMainProgram->timerSpeed = (int)100/value;
    }
}

void Menu::on_wallsCheckbox_stateChanged(int arg1)
{
    if(arg1 & Qt::Checked){
        mouseState = wall;
        ui->forestCheckbox->setChecked(false);
    }
}

void Menu::on_forestCheckbox_stateChanged(int arg1)
{
    if(arg1 & Qt::Checked){
        mouseState = forest;
        ui->wallsCheckbox->setChecked(false);
    }
}

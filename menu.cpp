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
    ui->mazeButton->setStyleSheet(buttonStyle);

    ui->roomsLabel->hide();
    ui->mazeIncrement->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->mazeDecrement->setAttribute(Qt::WA_TransparentForMouseEvents);

    nodes = pMainProgram->navigation->nodes;

    blockedList = &pMainProgram->navigation->blockedList;
    forestList = &pMainProgram->navigation->forestList;

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

                    if( nodes[col][row]->isStart ){
                        mouseState = start;
                        return;

                    }else if( nodes[col][row]->isFinish ){
                        mouseState = finish;
                        return;

                    }else if(nodes[col][row]->isForest){

                        return;

                    }else if( !nodes[col][row]->isBlocked ) {

                        nodes[col][row]->setBlocked();
                        blockedList->append(nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( nodes[col][row]->isStart ){

                        return;

                    }else if( nodes[col][row]->isFinish ){

                        return;

                    }else if(nodes[col][row]->isForest){

                        return;

                    }else if( nodes[col][row]->isBlocked ) {

                        nodes[col][row]->unsetBlocked();
                        blockedList->removeOne(nodes[col][row]);

                    }

                }
                break;

            case forest:
                if(event->buttons() & Qt::LeftButton){

                    if( nodes[col][row]->isStart ){
                        mouseState = start;
                        return;

                    }else if( nodes[col][row]->isFinish ){
                        mouseState = finish;
                        return;

                    }else if( !nodes[col][row]->isBlocked ) {

                        nodes[col][row]->setForest();
                        forestList->append(nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( nodes[col][row]->isStart ){

                        return;

                    }else if( nodes[col][row]->isFinish ){

                        return;

                    }else if( nodes[col][row]->isBlocked ) {

                        return;

                    }else if( nodes[col][row]->isForest ) {

                        nodes[col][row]->unsetForest();
                        forestList->removeOne(nodes[col][row]);

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

                    if( nodes[col][row]->isStart ){

                        return;

                    }else if( nodes[col][row]->isFinish ){

                        return;

                    }else if(nodes[col][row]->isForest){

                        return;

                    }else if( !nodes[col][row]->isBlocked ) {

                        nodes[col][row]->setBlocked();
                        blockedList->append(nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( nodes[col][row]->isStart ){

                        return;

                    }else if( nodes[col][row]->isFinish ){

                        return;

                    }else if(nodes[col][row]->isForest){

                        return;

                    }else if( nodes[col][row]->isBlocked ) {

                        nodes[col][row]->unsetBlocked();
                        blockedList->removeOne(nodes[col][row]);

                    }

                }
                break;

            case forest:
                if(event->buttons() & Qt::LeftButton){

                    if( nodes[col][row]->isStart ){

                        return;

                    }else if( nodes[col][row]->isFinish ){

                        return;

                    }else if( !nodes[col][row]->isBlocked ) {

                        nodes[col][row]->setForest();
                        forestList->append(nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( nodes[col][row]->isStart ){

                        return;

                    }else if( nodes[col][row]->isFinish ){

                        return;

                    }else if( nodes[col][row]->isBlocked ) {

                        return;

                    }else if( nodes[col][row]->isForest ) {

                        nodes[col][row]->unsetForest();
                        forestList->removeOne(nodes[col][row]);

                    }

                }
                break;

            case start:

                if( !nodes[col][row]->isBlocked &&
                        !nodes[col][row]->isFinish &&
                        !nodes[col][row]->isForest){

                    nodes[lastStartCol][lastStartRow]->unsetStart();
                    nodes[col][row]->setStart();
                    lastStartCol = col;
                    lastStartRow = row;
                    startNode = nodes[col][row];

                }

                break;

            case finish:

                if( !nodes[col][row]->isBlocked &&
                        !nodes[col][row]->isStart &&
                        !nodes[col][row]->isForest){

                    nodes[lastFinishCol][lastFinishRow]->unsetFinish();
                    nodes[col][row]->setFinish();
                    lastFinishCol = col;
                    lastFinishRow = row;
                    finishNode = nodes[col][row];

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

        pMainProgram->bfs->loopCount = 0;
        pMainProgram->dfs->loopCount = 0;
        pMainProgram->best->loopCount = 0;
        pMainProgram->dijkstra->loopCount = 0;
        pMainProgram->astar->loopCount = 0;

        on_pathButton_clicked();

        switch(selectedAlgorithm){
        case bfs:
            pMainProgram->bfs->startAlgorithm();
            break;
        case dfs:
            pMainProgram->dfs->startAlgorithm();;
            break;
        case best:
            pMainProgram->best->startAlgorithm();
            break;
        case dijkstra:
            pMainProgram->dijkstra->startAlgorithm();
            break;
        case astar:
            pMainProgram->astar->startAlgorithm();
            break;

        default:break;
        }

    }
}

void Menu::on_wallsButton_clicked()
{


    if(!pMainProgram->isSearching){

        on_pathButton_clicked();

        iter = blockedList->begin();
        while(iter != blockedList->end()){

            (*iter)->unsetBlocked();
            ++iter;

        }
        blockedList->clear();

    }
}

void Menu::on_forestButton_clicked()
{
    if(!pMainProgram->isSearching){

        on_pathButton_clicked();

        iter = forestList->begin();
        while(iter != forestList->end()){

            (*iter)->unsetForest();
            ++iter;

        }
        forestList->clear();

    }
}

void Menu::on_pathButton_clicked()
{
    if(!pMainProgram->isSearching){

        /* reset colors of nodes */
        for(int col = 0; col < 40; col++){
            for(int row = 0; row < 26; row++){
                if(nodes[col][row] != startNode &&
                        nodes[col][row] != finishNode &&
                        !nodes[col][row]->isBlocked &&
                        !nodes[col][row]->isForest){

                    nodes[col][row]->unsetBlocked();

                }
            }
        }

        /* clear path */

        pMainProgram->bfs->clearPath();
        pMainProgram->dfs->clearPath();;
        pMainProgram->best->clearPath();
        pMainProgram->dijkstra->clearPath();
        pMainProgram->astar->clearPath();


    }

}

void Menu::on_animationSpeedSlider_valueChanged(int value)
{
    if(value == 100){
        pMainProgram->bfs->timerSpeed = 0;
        pMainProgram->dfs->timerSpeed = 0;
        pMainProgram->best->timerSpeed = 0;
        pMainProgram->dijkstra->timerSpeed = 0;
        pMainProgram->astar->timerSpeed = 0;
    }else{
        pMainProgram->bfs->timerSpeed = (int)100/value;
        pMainProgram->dfs->timerSpeed = (int)100/value;
        pMainProgram->best->timerSpeed = (int)100/value;
        pMainProgram->dijkstra->timerSpeed = (int)100/value;
        pMainProgram->astar->timerSpeed = (int)100/value;
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

void Menu::on_mazeButton_clicked()
{
    if(!pMainProgram->isSearching and !pMainProgram->mazeGen->isGeneratingMaze){

        on_pathButton_clicked();
        pMainProgram->mazeGen->generateMaze();

    }
}

void Menu::on_mazeSlider_valueChanged(int value)
{
    pMainProgram->mazeGen->n = value;
    ui->roomsLabel->setText("rooms<br>" + QString::number(pow(2,value)));
}

void Menu::on_mazeSlider_sliderPressed()
{

    ui->roomsLabel->show();
}

void Menu::on_mazeSlider_sliderReleased()
{
    ui->roomsLabel->hide();
}

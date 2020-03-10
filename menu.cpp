#include "menu.h"
#include "ui_menu.h"
#include "game.h"
#include <QDebug>

extern Game * game;

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
    if(!game->isSearching){

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

                    if( game->nodes[col][row]->isStart ){
                        mouseState = start;
                        return;

                    }else if( game->nodes[col][row]->isFinish ){
                        mouseState = finish;
                        return;

                    }else if(game->nodes[col][row]->isForest){

                        return;

                    }else if( !game->nodes[col][row]->isBlocked ) {

                        game->nodes[col][row]->setBlocked();
                        game->blockedList.append(game->nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( game->nodes[col][row]->isStart ){

                        return;

                    }else if( game->nodes[col][row]->isFinish ){

                        return;

                    }else if(game->nodes[col][row]->isForest){

                        return;

                    }else if( game->nodes[col][row]->isBlocked ) {

                        game->nodes[col][row]->unsetBlocked();
                        game->blockedList.removeOne(game->nodes[col][row]);

                    }

                }
                break;

            case forest:
                if(event->buttons() & Qt::LeftButton){

                    if( game->nodes[col][row]->isStart ){
                        mouseState = start;
                        return;

                    }else if( game->nodes[col][row]->isFinish ){
                        mouseState = finish;
                        return;

                    }else if( !game->nodes[col][row]->isBlocked ) {

                        game->nodes[col][row]->setForest();
                        game->forestList.append(game->nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( game->nodes[col][row]->isStart ){

                        return;

                    }else if( game->nodes[col][row]->isFinish ){

                        return;

                    }else if( game->nodes[col][row]->isBlocked ) {

                        return;

                    }else if( game->nodes[col][row]->isForest ) {

                        game->nodes[col][row]->unsetForest();
                        game->forestList.removeOne(game->nodes[col][row]);

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
    if(!game->isSearching){

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

                    if( game->nodes[col][row]->isStart ){

                        return;

                    }else if( game->nodes[col][row]->isFinish ){

                        return;

                    }else if(game->nodes[col][row]->isForest){

                        return;

                    }else if( !game->nodes[col][row]->isBlocked ) {

                        game->nodes[col][row]->setBlocked();
                        game->blockedList.append(game->nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( game->nodes[col][row]->isStart ){

                        return;

                    }else if( game->nodes[col][row]->isFinish ){

                        return;

                    }else if(game->nodes[col][row]->isForest){

                        return;

                    }else if( game->nodes[col][row]->isBlocked ) {

                        game->nodes[col][row]->unsetBlocked();
                        game->blockedList.removeOne(game->nodes[col][row]);

                    }

                }
                break;

            case forest:
                if(event->buttons() & Qt::LeftButton){

                    if( game->nodes[col][row]->isStart ){

                        return;

                    }else if( game->nodes[col][row]->isFinish ){

                        return;

                    }else if( !game->nodes[col][row]->isBlocked ) {

                        game->nodes[col][row]->setForest();
                        game->forestList.append(game->nodes[col][row]);

                    }

                }else if(event->buttons() & Qt::RightButton){

                    if( game->nodes[col][row]->isStart ){

                        return;

                    }else if( game->nodes[col][row]->isFinish ){

                        return;

                    }else if( game->nodes[col][row]->isBlocked ) {

                        return;

                    }else if( game->nodes[col][row]->isForest ) {

                        game->nodes[col][row]->unsetForest();
                        game->forestList.removeOne(game->nodes[col][row]);

                    }

                }
                break;

            case start:

                if( !game->nodes[col][row]->isBlocked &&
                        !game->nodes[col][row]->isFinish &&
                        !game->nodes[col][row]->isForest){

                    game->nodes[lastStartCol][lastStartRow]->unsetStart();
                    game->nodes[col][row]->setStart();
                    lastStartCol = col;
                    lastStartRow = row;
                    game->start = game->nodes[col][row];

                }

                break;

            case finish:

                if( !game->nodes[col][row]->isBlocked &&
                        !game->nodes[col][row]->isStart &&
                        !game->nodes[col][row]->isForest){

                    game->nodes[lastFinishCol][lastFinishRow]->unsetFinish();
                    game->nodes[col][row]->setFinish();
                    lastFinishCol = col;
                    lastFinishRow = row;
                    game->finish = game->nodes[col][row];

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
    if(!game->isSearching){

        game->loopCount = 0;
        on_pathButton_clicked();

        switch(selectedAlgorithm){
        case bfs:
            game->start_BreadthFirstSearch();
            break;
        case dfs:
            game->start_DepthFirstSearch();;
            break;
        case best:
            game->start_BestFirstSearch();
            break;
        case dijkstra:
            game->start_Dijkstra();
            break;
        case astar:
            game->start_Astar();
            break;

        default:break;
        }

    }
}

void Menu::on_wallsButton_clicked()
{
    if(!game->isSearching){

        on_pathButton_clicked();

        game->iter = game->blockedList.begin();
        while(game->iter != game->blockedList.end()){

            (*game->iter)->unsetBlocked();
            ++game->iter;

        }
        game->blockedList.clear();

    }
}

void Menu::on_forestButton_clicked()
{
    if(!game->isSearching){

        on_pathButton_clicked();

        game->iter = game->forestList.begin();
        while(game->iter != game->forestList.end()){

            (*game->iter)->unsetForest();
            ++game->iter;

        }
        game->forestList.clear();

    }
}

void Menu::on_pathButton_clicked()
{
    if(!game->isSearching){

        /* clear pathway list */
        if(!game->pathway.empty()){
            game->pathway.clear();
        }

        /* clear frontier list */
        if(!game->frontier.empty()){
            game->frontier.clear();
        }

        /* reset colors of nodes */
        for(int col = 0; col < 40; col++){
            for(int row = 0; row < 26; row++){
                if(game->nodes[col][row] != game->start &&
                        game->nodes[col][row] != game->finish &&
                        !game->nodes[col][row]->isBlocked &&
                        !game->nodes[col][row]->isForest){

                    game->nodes[col][row]->unsetBlocked();

                }
            }
        }

        /* reset cameFrom Matrix */
        for(int col = 0; col < 40; col++){
            for(int row = 0; row < 26; row++){
                game->cameFrom[col][row] = nullptr;
            }
        }

        /* set visited to NULL */
        for(int cols = 0; cols < 40; cols++){
            for(int rows = 0; rows < 26; rows++){
                game->visited[cols][rows] = nullptr;
            }
        }

        /* clear cost_so_far */
        game->cost_so_far.clear();

        /* destroy and clear lines */
        game->lineIter = game->lines.begin();
        while(game->lineIter != game->lines.end()){
            QGraphicsLineItem *pHelp = game->lines.first();
            delete pHelp;
            game->lineIter = game->lines.erase(game->lineIter);
        }
        game->lines.clear();
    }

}

void Menu::on_animationSpeedSlider_valueChanged(int value)
{
    if(value == 100){
        game->timerSpeed = 0;
    }else{
        game->timerSpeed = (int)100/value;
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

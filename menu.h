#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QElapsedTimer>
#include <QMouseEvent>

#include "node.h"

namespace Ui {
class Menu;
}

enum mouseCursorState { wall, forest, start, finish };
enum algorithmState { dfs, bfs, best, dijkstra, astar };

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    QElapsedTimer timer;
    mouseCursorState mouseState;
    algorithmState selectedAlgorithm;

    Node *(*nodes)[26];
    Node *startNode;
    Node *finishNode;
    QList<Node*> *blockedList;
    QList<Node*> *forestList;
    QList<Node*>::iterator iter;

    int lastStartCol = 0;
    int lastStartRow = 0;
    int lastFinishCol = 0;
    int lastFinishRow = 0;

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void on_dijkstraButton_clicked();
    void on_astarButton_clicked();
    void on_bfsButton_clicked();
    void on_bestfsButton_clicked();
    void on_dfsButton_clicked();
    void on_startButton_clicked();
    void on_wallsButton_clicked();
    void on_forestButton_clicked();
    void on_pathButton_clicked();
    void on_animationSpeedSlider_valueChanged(int value);
    void on_wallsCheckbox_stateChanged(int arg1);
    void on_forestCheckbox_stateChanged(int arg1);

    void on_mazeButton_clicked();

    void on_mazeSlider_valueChanged(int value);

    void on_mazeSlider_sliderPressed();

    void on_mazeSlider_sliderReleased();

private:
    Ui::Menu *ui;
};

#endif // MENU_H

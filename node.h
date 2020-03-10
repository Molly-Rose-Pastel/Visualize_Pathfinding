#ifndef NODE_H
#define NODE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>


class Node: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Node(QGraphicsItem *parent = 0);
    bool isBlocked = false;
    bool isStart = false;
    bool isFinish = false;
    bool isForest = false;

    int col = 0;
    int row = 0;
    int priority = 0;
    int weight = 0;

public slots:
    void setColor(Qt::GlobalColor color);
    void setStart();
    void unsetStart();
    void setFinish();
    void unsetFinish();
    void setBlocked();
    void unsetBlocked();
    void setForest();
    void unsetForest();
    void setExplored();
    void setFrontier();
    QString getState();
};

#endif // NODE_H

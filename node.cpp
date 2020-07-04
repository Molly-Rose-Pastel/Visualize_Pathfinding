#include "node.h"
//#include "game.h"

//extern Game * game;

Node::Node(QGraphicsItem *parent)
{
    setBrush(QBrush(Qt::lightGray));
}

void Node::setColor(Qt::GlobalColor color)
{
    setBrush(QBrush(color));
}

void Node::setStart()
{
    isBlocked = false;
    isStart = true;
    isFinish = false;
    isForest = false;
    weight = 0;
    setColor(Qt::green);
}

void Node::unsetStart()
{
    isBlocked = false;
    isStart = false;
    isFinish = false;
    isForest = false;
    weight = 0;
    setColor(Qt::lightGray);
}

void Node::setFinish()
{
    isBlocked = false;
    isStart = false;
    isFinish = true;
    isForest = false;
    weight = 0;
    setColor(Qt::red);
}

void Node::unsetFinish()
{
    isBlocked = false;
    isStart = false;
    isFinish = false;
    isForest = false;
    weight = 0;
    setColor(Qt::lightGray);
}

void Node::setBlocked()
{
    isBlocked = true;
    isStart = false;
    isFinish = false;
    isForest = false;
    weight = 0;
    setBrush(QBrush(QColor(qRgba(47,47,47,255))));
}

void Node::unsetBlocked()
{
    isBlocked = false;
    isStart = false;
    isFinish = false;
    isForest = false;
    weight = 0;
    setColor(Qt::lightGray);
}

void Node::setForest()
{
    isBlocked = false;
    isStart = false;
    isFinish = false;
    isForest = true;
    setColor(Qt::darkGreen);
    weight = 10;
}

void Node::unsetForest()
{
    isBlocked = false;
    isStart = false;
    isFinish = false;
    isForest = false;
    weight = 0;
    setColor(Qt::lightGray);
}

void Node::setExplored()
{
    setBrush(QBrush(QColor(qRgba(238,232,170,255))));
}

void Node::setFrontier()
{
    setBrush(QBrush(QColor(qRgba(189,186,107,255))));

}

QString Node::getState()
{
    if(isBlocked){

        return "blocked";

    }else if(isForest){

        return "forest";

    }else if(isStart){

        return "start";

    }else if(isFinish){

        return "finish";

    }else {

        return "clear";

    }
}


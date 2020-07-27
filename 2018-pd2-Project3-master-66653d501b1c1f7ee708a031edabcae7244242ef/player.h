#ifndef PLAYER_H
#define PLAYER_H
#include "chara.h"

class player:public chara
{
public:
    player();
    virtual ~player();
    virtual void mode(QGraphicsScene *scene);
    virtual void dead();
    virtual void start();
};

#endif // PLAYER_H

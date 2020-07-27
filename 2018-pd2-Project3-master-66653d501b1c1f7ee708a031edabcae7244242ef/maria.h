#ifndef MARIA_H
#define MARIA_H
#include "chara.h"

class maria:public chara
{
public:
    maria();
    virtual ~maria();
    virtual void mode(QGraphicsScene *scene);
    virtual void dead();
    void attack_time();
    void rest_time();
    void five_star(bullet *bin,QGraphicsScene *scene);
    void moving();
    void flower_card(bullet *bin,QGraphicsScene *scene);
    void wing(QGraphicsScene *scene);
    void reflect(QGraphicsScene *scene);
    virtual void final_skill();
    virtual void start();
    QTimer *rest=new QTimer;
    QTimer *attack=new QTimer;
    int i=0;
    QPixmap boss[6];
    QPixmap arm[6];

};

#endif // MARIA_H

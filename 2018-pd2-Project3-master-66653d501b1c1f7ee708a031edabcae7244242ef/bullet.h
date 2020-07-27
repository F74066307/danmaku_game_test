#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include<QTimer>
#include <cmath>
#include<cstdlib>

class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet();
    QTimer *t1,*t2,*ctrl1,*ctrl2;
    int t=0,i=1;
    int ref=0;
    int now=0;
    int code=0;
    float r;
    int time;
    float theta,angle,flyangle;
public slots:
    void clear();
    void fly_down();
    void fly_up();
    void fly_r();
    void fly_l();
    void specialmove();
    void fly2();
    void fly22();
    void fly23();
    void fly24();
    void fly_angle();
    void fly_star();
    void fly_unstar();
    void fly_ref();
    void t1_start();
    void t2_start();
    void change_angle();
signals:
    void ready(int x=100);
};

#endif // BULLET_H

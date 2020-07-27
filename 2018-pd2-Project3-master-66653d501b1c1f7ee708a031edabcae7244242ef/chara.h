#ifndef CHARA_H
#define CHARA_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include<QPixmap>
#include <QTimer>
#include<bullet.h>
#include<cstdlib>
#include<ctime>

class chara: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    chara();
    virtual ~chara();
    int bullet_mode=0;
    int hp,maxhp;
    int t=0;
    int times=0;
    int stage=0;
    bullet *b1,*b2;
    bullet *life=new bullet;
    QTimer *shoot_time;
    QTimer *move =new QTimer;
    virtual void mode(QGraphicsScene *scene)=0;
    virtual void level_up();
    virtual void dead(){}
    virtual void start(){}
signals:
    void mode_up();
    void clear();
};

#endif // CHARA_H

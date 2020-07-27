#include "player.h"

player::player()
{
    hp=6;
    life->setObjectName("player");
    this->setPixmap(QPixmap(":/chara/shirabe2.png").scaled(50,80,Qt::KeepAspectRatio));
    life->setPixmap(QPixmap(":/bullet/pink.png").scaled(5,5));
    shoot_time=new QTimer;
    b1=new bullet;
    b1->setPixmap(QPixmap(":/bullet/s_bullet2.png").scaled(25,25,Qt::KeepAspectRatio));
    b2=new bullet;
    b2->setPixmap(QPixmap(":/bullet/s_bullet22.png").scaled(25,25,Qt::KeepAspectRatio));
    connect(this,&player::mode_up,this,&player::level_up);
}

void player::start(){
    hp=6;
    shoot_time->start(100);
    bullet_mode=0;
}

void player::mode(QGraphicsScene *scene){
    switch (bullet_mode) {
    case 2:
    {
            bullet *b=new bullet;
            b->code=1;
            b->r=5;
            b->theta=-90*M_PI/180;
            b->setPixmap(life->pixmap().scaled(8,8));
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            b->setPos(this->b1->x(),this->b1->y());
            scene->addItem(static_cast<QGraphicsItem *>(b));
            b->t1->start(10);
            bullet *b1=new bullet;
            b1->code=1;
            b1->setPixmap(life->pixmap().scaled(8,8));
            b1->setPos(b2->x(),b2->y());
            scene->addItem(static_cast<QGraphicsItem *>(b1));
            b1->r=5;
            b1->theta=-90*M_PI/180;
            connect(b1->t1,&QTimer::timeout,b1,&bullet::fly2);
            b1->t1->start(10);
            connect(this,&player::clear,b1,&bullet::clear);
    }
    case 1:
    {
        for(int i=0;i<2;++i){
            bullet *b1=new bullet;
            b1->code=1;
            b1->setPixmap(life->pixmap().scaled(8,8));
            b1->setPos(x()+5+i*30,this->y());
            scene->addItem(static_cast<QGraphicsItem *>(b1));
            b1->r=5;
            b1->theta=-90*M_PI/180;
            connect(b1->t1,&QTimer::timeout,b1,&bullet::fly2);
            b1->t1->start(10);
            connect(this,&player::clear,b1,&bullet::clear);
        }
    }
    case 0:
    {
        bullet *b=new bullet;
        b->code=1;
        b->setPixmap(life->pixmap().scaled(8,8));
        b->setPos(life->x()-10,this->y());
        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->r=5;
        b->theta=-90*M_PI/180;
        connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
        b->t1->start(10);
        connect(this,&player::clear,b,&bullet::clear);
        break;
    }
    default:
        break;
    }
}
void player::dead(){
    shoot_time->stop();
    this->move->stop();
    emit clear();

}
player::~player(){
    delete this;
}

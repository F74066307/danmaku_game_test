#include "maria.h"

maria::maria()
{
    boss[0].load(":/boss/boss4.png");
    boss[1].load(":/boss/boss5.png");
    boss[2].load(":/boss/boss6.png");
    boss[3].load(":/boss/boss2.png");
    boss[4].load(":/boss/boss3.png");
    boss[5].load(":/boss/boss1.png");
    arm[0].load(":/bullet/ag1.png");
    arm[1].load(":/bullet/star_g.png");
    arm[2].load(":/bullet/s_bullet2.png");
    arm[3].load(":/bullet/knife_b.png");
    arm[4].load(":/bullet/red.png");
    arm[5].load(":/bullet/orange.png");
    maxhp=50000;
    srand(time(NULL));
    hp=maxhp;
    life->theta=(rand()%360+1)*M_PI/180;
    life->setObjectName("life");
    connect(move,&QTimer::timeout,life,&bullet::fly2);
    connect(move,&QTimer::timeout,this,&maria::moving);
    this->setPixmap(boss[0].scaled(150,200,Qt::KeepAspectRatio));
    life->setPixmap(QPixmap(":/bullet/silver.png").scaled(12,12));
    shoot_time=new QTimer;
    b1=new bullet;
    b1->setPixmap(QPixmap(":/bullet/ag1.png").scaled(20,30,Qt::KeepAspectRatio));
    b2=new bullet;
    b2->setPixmap(QPixmap(":/bullet/ag1.png").scaled(20,30,Qt::KeepAspectRatio));


    connect(b1->ctrl1,&QTimer::timeout,b1->ctrl1,&QTimer::stop);
    connect(b1->ctrl2,&QTimer::timeout,b1->ctrl2,&QTimer::stop);
    connect(rest,&QTimer::timeout,this,&maria::attack_time);
    connect(attack,&QTimer::timeout,this,&maria::rest_time);
}

void maria::start(){
    this->setPixmap(boss[stage].scaled(150,200,Qt::KeepAspectRatio));
    life->setPixmap(arm[stage].scaled(12,12));
    b1->setPixmap(arm[stage].scaled(20,30,Qt::KeepAspectRatio));
    b2->setPixmap(arm[stage].scaled(20,30,Qt::KeepAspectRatio));
    bullet_mode=0;
    hp=maxhp;
    shoot_time->start(50);
    rest->start(2000);
    this->setPos(400,-50);
    life->setPos(250,10);
    move->start(30);
    life->ctrl1->start(3000);
}

void maria::moving(){
    this->setPos(life->x()-50,life->y()-60);

}

void maria::rest_time(){
     life->theta=(rand()%360+1)*M_PI/180;
    move->start(30);
    rest->start(3000);
    attack->stop();
    if(b1->scene()==NULL||bullet_mode!=10){
        shoot_time->stop();
    }

}
void maria::attack_time(){
    if(bullet_mode!=10){
        bullet_mode=rand()%3;
    }
 move->stop();
 rest->stop();
 attack->start(3000);
 shoot_time->start(50);
 if(b1->scene()!=NULL){
     bullet_mode=rand()%2+10*(stage+1);
     if(bullet_mode==10){
         shoot_time->start(10);
     }
     else if(bullet_mode/10==4){
         shoot_time->start(120);
     }
     else if(bullet_mode/10==6){
         shoot_time->start(100);
     }
     else{
         shoot_time->start(50);
     }
     b1->ctrl1->start(2500);
     b1->ctrl2->start(2700);
     b1->t1->start(10);
     b1->t2->start(10);
     b2->t1->start(10);
 }
}
void maria::mode(QGraphicsScene *scene){
    switch (bullet_mode) {
    case 0:
    {
        for(int i=0;i<4;i++){
            bullet *bin=new bullet;
            bin->setPixmap(life->pixmap());
            scene->addItem(static_cast<QGraphicsItem *>(bin));
            bin->setPos(life->x()+life->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),life->y()+life->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
            bin->theta=(t+i*45)*M_PI/90;
            connect(bin->t1,&QTimer::timeout,bin,&bullet::fly2);
            bin->time=30;
            bin->r=8;
            bin->t1_start();
            connect(this,&maria::clear,bin,&bullet::clear);
        }
        t++;
        break;
    }
    case 1:
    {
        for(int i=1;i<=3;++i){
            bullet *b=new bullet;
            b->theta=t*M_PI/20;
            b->setPixmap(b1->pixmap().transformed(QMatrix().rotate(180+(t*9-90))));
            b->r=3*i;
            scene->addItem(static_cast<QGraphicsItem *>(b));
            b->setPos(life->x()+15*i*cos(b->theta),life->y()+15*i*sin(b->theta));
            b->time=30;
            connect(attack,&QTimer::timeout,b,&bullet::t1_start);
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            connect(this,&maria::clear,b,&bullet::clear);
        }
        t++;
    }
        break;
    case 2:
    {
        for(int i=0;i<4;i++){
            bullet *bin=new bullet;
            bin->setPixmap(life->pixmap());
            scene->addItem(static_cast<QGraphicsItem *>(bin));
            bin->setPos(life->x()+life->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),life->y()+life->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
            bin->theta=(t+i*45)*M_PI/90;
            connect(bin->t1,&QTimer::timeout,bin,&bullet::fly22);
            bin->time=30;
            bin->r=8;
            bin->t1_start();
            connect(this,&maria::clear,bin,&bullet::clear);
        }
        t++;
        break;
    }
    case 10:
    {
        five_star(b1,scene);
        five_star(b2,scene);
        t--;
        times++;
        if(times>=50){
            t=0;
            times=0;
        }
    }
        break;
    case 11:
    {
            bullet *b3=new bullet;
            b3->theta=t*M_PI/20;
            b3->setPixmap(b1->pixmap().transformed(QMatrix().rotate(180+(t*9-90))));
            b3->r=6;
            scene->addItem(static_cast<QGraphicsItem *>(b3));
            b3->setPos(b1->x()+15*i*cos(b3->theta),b1->y()+15*i*sin(b3->theta));
            b3->time=30;
            connect(attack,&QTimer::timeout,b3,&bullet::t1_start);
            connect(b3->t1,&QTimer::timeout,b3,&bullet::fly2);
            connect(b3->t1,&QTimer::timeout,b3,&bullet::fly2);
            connect(this,&maria::clear,b3,&bullet::clear);
            bullet *b=new bullet;
            b->theta=t*M_PI/20;
            b->setPixmap(b1->pixmap().transformed(QMatrix().rotate(180+(t*9-90))));
            b->r=6;
            scene->addItem(static_cast<QGraphicsItem *>(b));
            b->setPos(b2->x()+15*cos(b->theta),b2->y()+15*sin(b->theta));
            b->time=30;
            connect(attack,&QTimer::timeout,b,&bullet::t1_start);
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            connect(this,&maria::clear,b,&bullet::clear);

        t++;
    }
        break;
    case 20:
    case 30:
    {
        for(int i=0;i<3;i++){
            bullet *bin=new bullet;
            bin->setPixmap(life->pixmap());
            scene->addItem(static_cast<QGraphicsItem *>(bin));
            bin->setPos(life->x()+life->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),life->y()+life->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
            bin->theta=(t+i*60)*M_PI/90;
            connect(bin->t1,&QTimer::timeout,bin,&bullet::fly22);
            bin->time=30;
            bin->r=8;
            bin->t1_start();
            connect(this,&maria::clear,bin,&bullet::clear);
        }
        for(int i=0;i<3;i++){
            bullet *bin=new bullet;
            bin->setPixmap(life->pixmap());
            scene->addItem(static_cast<QGraphicsItem *>(bin));
            bin->setPos(life->x()+life->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),life->y()+life->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
            bin->theta=(t+i*60)*M_PI/90;
            connect(bin->t1,&QTimer::timeout,bin,&bullet::fly2);
            bin->time=30;
            bin->r=8;
            bin->t1_start();
            connect(this,&maria::clear,bin,&bullet::clear);
        }
        t++;
    }
        break;
    case 21:
    {
        for(int i=0;i<3;i++){
            bullet *bin=new bullet;
            bin->setPixmap(life->pixmap());
            scene->addItem(static_cast<QGraphicsItem *>(bin));
            bin->setPos(b1->x()+b1->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),b1->y()+b1->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
            bin->theta=(t+i*60)*M_PI/90;
            connect(bin->t1,&QTimer::timeout,bin,&bullet::fly22);
            bin->time=30;
            bin->r=8;
            bin->t1_start();
            connect(this,&maria::clear,bin,&bullet::clear);
        }
        for(int i=0;i<3;i++){
            bullet *bin=new bullet;
            bin->setPixmap(life->pixmap());
            scene->addItem(static_cast<QGraphicsItem *>(bin));
            bin->setPos(b2->x()+b2->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),b2->y()+b2->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
            bin->theta=(t+i*60)*M_PI/90;
            connect(bin->t1,&QTimer::timeout,bin,&bullet::fly2);
            bin->time=30;
            bin->r=8;
            bin->t1_start();
            connect(this,&maria::clear,bin,&bullet::clear);
        }
        t++;
    }
        break;
    case 31:
    {
        for(int i=1;i<=2;++i){
            bullet *b=new bullet;
            b->theta=t*M_PI/20;
            b->setPixmap(b1->pixmap().transformed(QMatrix().rotate(180+(t*9-90))));
            b->r=3*i;
            scene->addItem(static_cast<QGraphicsItem *>(b));
            b->setPos(life->x()+15*i*cos(b->theta),life->y()+15*i*sin(b->theta));
            b->time=30;
            connect(attack,&QTimer::timeout,b,&bullet::t1_start);
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            connect(this,&maria::clear,b,&bullet::clear);
        }
        bullet *b=new bullet;
        b->theta=t*M_PI/20;
        b->setPixmap(b1->pixmap().transformed(QMatrix().rotate(180+(t*9-90))));
        b->r=3;
        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(b1->x()+15*cos(b->theta),b1->y()+15*sin(b->theta));
        b->time=30;
        connect(attack,&QTimer::timeout,b,&bullet::t1_start);
        connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
        connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
        connect(this,&maria::clear,b,&bullet::clear);
        bullet *b2=new bullet;
        b2->theta=t*M_PI/20;
        b2->setPixmap(b1->pixmap().transformed(QMatrix().rotate(180+(t*9-90))));
        b2->r=3;
        scene->addItem(static_cast<QGraphicsItem *>(b2));
        b2->setPos(b2->x()+15*cos(b2->theta),b2->y()+15*sin(b2->theta));
        b2->time=30;
        connect(attack,&QTimer::timeout,b2,&bullet::t1_start);
        connect(b2->t1,&QTimer::timeout,b2,&bullet::fly2);
        connect(b2->t1,&QTimer::timeout,b2,&bullet::fly2);
        connect(this,&maria::clear,b2,&bullet::clear);
        t++;
    }
        break;
    case 40:
    case 41:
    {
        wing(scene);
    }
        break;
    case 50:
    case 51:
    {
        reflect(scene);
    }
        break;
    case 60:
    {
        for(int i=0;i<3;i++){
            bullet *bin=new bullet;
            bin->setPixmap(life->pixmap());
            scene->addItem(static_cast<QGraphicsItem *>(bin));
            bin->setPos(life->x()+life->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),life->y()+life->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
            bin->theta=(t+i*60)*M_PI/90;
            connect(bin->t1,&QTimer::timeout,bin,&bullet::fly22);
            bin->time=30;
            bin->r=8;
            bin->t1_start();
            connect(this,&maria::clear,bin,&bullet::clear);
        }
        for(int i=0;i<3;i++){
            bullet *bin=new bullet;
            bin->setPixmap(life->pixmap());
            scene->addItem(static_cast<QGraphicsItem *>(bin));
            bin->setPos(life->x()+life->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),life->y()+life->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
            bin->theta=(t+i*60)*M_PI/90;
            connect(bin->t1,&QTimer::timeout,bin,&bullet::fly2);
            bin->time=30;
            bin->r=8;
            bin->t1_start();
            connect(this,&maria::clear,bin,&bullet::clear);
        }
        t++;
        flower_card(b1,scene);
        flower_card(b2,scene);
    }
        break;
    case 61:
    {
        for(int i=1;i<=2;++i){
            bullet *b=new bullet;
            b->theta=t*M_PI/20;
            b->setPixmap(b1->pixmap().transformed(QMatrix().rotate(180+(t*9-90))));
            b->r=3*i;
            scene->addItem(static_cast<QGraphicsItem *>(b));
            b->setPos(life->x()+15*i*cos(b->theta),life->y()+15*i*sin(b->theta));
            b->time=30;
            connect(attack,&QTimer::timeout,b,&bullet::t1_start);
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
            connect(this,&maria::clear,b,&bullet::clear);
        }
        t++;
        flower_card(b1,scene);
        flower_card(b2,scene);
    }
        break;
    default:
        break;
}
}

void maria::dead(){
    if(stage==0){
        disconnect(b1->t1,&QTimer::timeout,b1,&bullet::fly_star);
        disconnect(b2->t1,&QTimer::timeout,b2,&bullet::fly_unstar);
    }
    this->scene()->removeItem(this);
    this->move->stop();
    this->shoot_time->stop();
    this->b1->t1->stop();
    this->b1->t2->stop();
    this->b2->t2->stop();
    this->b2->t1->stop();
    this->attack->stop();
    this->rest->stop();
    emit clear();
}

void maria::final_skill(){
    shoot_time->start(50);
    if(stage==0){
        connect(b1->t1,&QTimer::timeout,b1,&bullet::fly_star);
        connect(b2->t1,&QTimer::timeout,b2,&bullet::fly_unstar);
        b1->t1->start(10);
        b1->t2->start(10);
        b2->t1->start(10);
        b1->ctrl1->start(2500);
        b1->ctrl2->start(2700);
        shoot_time->start(10);
    }

    t=0;
    bullet_mode=10*stage+10;
    b1->setPos(300,50);
    b2->setPos(500,50);
    if(stage==5){
        b1->setPos(200,150);
        b2->setPos(400,150);
    }

}

void maria::five_star(bullet *bin, QGraphicsScene *scene){
        bullet *b=new bullet;
        b->time=10;
        b->r=8;
        b->angle=72*M_PI/180;
        connect(b1->ctrl1,&QTimer::timeout,b,&bullet::t2_start);
        connect(b->t2,&QTimer::timeout,b,&bullet::fly_angle);
        connect(b1->ctrl2,&QTimer::timeout,b,&bullet::t1_start);
        connect(b1->ctrl2,&QTimer::timeout,b1->ctrl1,&QTimer::stop);
        connect(b1->ctrl2,&QTimer::timeout,b->t2,&QTimer::stop);
        b->setPixmap(QPixmap(":/bullet/silver.png").scaled(12,12));
        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(bin->x()+bin->pixmap().width()/2,bin->y()+bin->pixmap().height()/2);
        b->theta=t*M_PI/25;
        connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
        connect(this,&maria::clear,b,&bullet::clear);
}

void maria::flower_card(bullet *bin, QGraphicsScene *scene){
    for(int i=0;i<5;++i){
        bullet *b=new bullet;
        b->theta=(-90+72*i)*M_PI/180;
        b->angle=(-72+72*i)*M_PI/180;
        b->flyangle=M_PI/100;
        b->setPixmap(QPixmap(":/bullet/card_r.png"));
        b->setPos(bin->x()+100*cos(b->theta),bin->y()+100*sin(b->theta)+10);
        scene->addItem(static_cast<QGraphicsItem *>(b));
        connect(b->t1,&QTimer::timeout,b,&bullet::fly_angle);
        connect(b->t1,&QTimer::timeout,b,&bullet::change_angle);
        b->r=2;
        b->t1->start(15);
        connect(b->ctrl1,&QTimer::timeout,b,&bullet::clear);
        b->ctrl1->start(2300);
    }
}

void maria::wing(QGraphicsScene *scene){
    for(int i=0;i<10;++i){
        bullet *b=new bullet;
        b->theta=(-30-15*i)*M_PI/180;
        if(i>=5){
            b->angle=-M_PI/90;
            b->setPixmap(QPixmap(":/bullet/knife_b.png").transformed(QMatrix().rotate((b->theta-120)*180/M_PI)));
        }
        else{
            b->angle=M_PI/90;
            b->setPixmap(QPixmap(":/bullet/knife_r.png").transformed(QMatrix().rotate((b->theta-90)*180/M_PI)));
        }
        b->r=5;
        b->setPos(life->x()+10*cos((-100-5*i)*M_PI/180),life->y()+10*sin((-100-5*i)*M_PI/180));

        scene->addItem(static_cast<QGraphicsItem*>(b));
        connect(b->t1,&QTimer::timeout,b,&bullet::fly24);
        connect(this,&maria::clear,b,&bullet::clear);
        b->t1->start(30);
    }
}

void maria::reflect(QGraphicsScene *scene){
    bullet *b=new bullet;
    connect(this,&maria::clear,b,&bullet::clear);
    b->theta=t*M_PI/60;
    b->setPixmap(QPixmap(":/bullet/laser.png").transformed(QMatrix().rotate(3*t)));
    scene->addItem(static_cast<QGraphicsItem *>(b));
    b->setPos(b1->x()+b1->pixmap().width()/2,b1->y()+b1->pixmap().height()/2);
    b->t1->start(20);
    connect(b->t1,&QTimer::timeout,b,&bullet::fly_ref);
    t--;
}


maria::~maria(){
    delete this;
}

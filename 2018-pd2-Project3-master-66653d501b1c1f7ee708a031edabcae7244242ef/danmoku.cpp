#include "danmoku.h"
#include "ui_danmoku.h"

danmoku::danmoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::danmoku),
    scene(new QGraphicsScene(0,0,900,1000)),
    graphicsview(new QGraphicsView(scene,this))
{
    ui->setupUi(this);
    graphicsview->setGeometry(200,0,1000,1200);
    bpng[0].load(":/bullet/b1.png");
    bpng[1].load(":/bullet/blue.png");
    bpng[2].load(":/bullet/red.png");
    bpng[3].load(":/bullet/green.png");
    for(int i=0;i<4;++i){
        bpng[i]=bpng[i].scaled(15,15);
       }
    b1->setPos(400,200);
    b1->setPixmap(bpng[1]);
    b2->setPixmap(bpng[2]);

    QLabel *help=new QLabel(this);
    help->setGeometry(0,0,150,400);
    help->setText("這裡是示範彈幕的模式，收錄了遊戲中用的所有彈幕，以及遊戲中「不能用」的彈幕（笑），按旁側的按鈕即可產生彈幕。PS：其中幾個彈幕是參照東方某些角色做出來的,不知是否有人認的出來呢");
    help->setWordWrap(true);
    help->show();
    QPushButton *flower=new QPushButton(this);
    flower->setText("flower");
    flower->setGeometry(1200,0,80,25);
    connect(flower,&QPushButton::clicked,this,&danmoku::use_flower);

    QPushButton *star=new QPushButton(this);
    star->setText("five star");
    star->setGeometry(1200,35,80,25);
    connect(star,&QPushButton::clicked,this,&danmoku::use_star);

    QPushButton *wind=new QPushButton(this);
    wind->setText("wind");
    wind->setGeometry(1200,70,80,25);
    connect(wind,&QPushButton::clicked,this,&danmoku::use_wind);

    QPushButton *ring=new QPushButton(this);
    ring->setText("ring");
    ring->setGeometry(1200,105,80,25);
    connect(ring,&QPushButton::clicked,this,&danmoku::use_ring);

    QPushButton *laser=new QPushButton(this);
    laser->setText("laser");
    laser->setGeometry(1200,140,80,25);
    connect(laser,&QPushButton::clicked,this,&danmoku::use_laser);

    QPushButton *wing=new QPushButton(this);
    wing->setText("wing");
    wing->setGeometry(1200,175,80,25);
    connect(wing,&QPushButton::clicked,this,&danmoku::use_wing);

    QPushButton *c=new QPushButton(this);
    c->setText("Clear bullet");
    c->setGeometry(1200,210,105,25);
    connect(c,&QPushButton::clicked,this,&danmoku::to_clear);

}

void danmoku::to_clear(){
    emit clearall();
}

void danmoku::clear(){
    switch (type) {
    case 'f':
    {
        t=0;
        disconnect(b1->t2,&QTimer::timeout,this,&danmoku::skill_flower);
        disconnect(b1->ctrl1,&QTimer::timeout,this,&danmoku::flower_cardp2);
        disconnect(b1->ctrl2,&QTimer::timeout,this,&danmoku::flower_cardp3);
        disconnect(b1->ctrl1,&QTimer::timeout,b1->ctrl1,&QTimer::stop);
        disconnect(b1->ctrl2,&QTimer::timeout,b1->ctrl2,&QTimer::stop);
        disconnect(end,&QTimer::timeout,b1->t2,&QTimer::stop);
        disconnect(end,&QTimer::timeout,this,&danmoku::clear);
        break;
    }
    case 's':
    {
        b1->setPos(400,200);
        t=0;
        b1->r=5;
        b2->r=5;
        end->stop();
        disconnect(b1->ctrl2,&QTimer::timeout,this,&danmoku::clear);
        disconnect(b1->t1,&QTimer::timeout,b1,&bullet::fly_star);
        disconnect(b2->t1,&QTimer::timeout,b2,&bullet::fly_unstar);
        disconnect(b1->t2,&QTimer::timeout,this,&danmoku::skill_star);
        disconnect(b1->ctrl2,&QTimer::timeout,b1->ctrl1,&QTimer::stop);
        disconnect(b1->ctrl2,&QTimer::timeout,b1->ctrl2,&QTimer::stop);
    }
        break;
    default:
        break;
    }
}

void danmoku::use_wing(){
    b1->t1->start(80);
    b1->setPos(400,100);
    switch(mode) {
    case 0:
        connect(b1->t1,&QTimer::timeout,this,&danmoku::wing);
        mode++;
        break;
    case 1:
        disconnect(b1->t1,&QTimer::timeout,this,&danmoku::wing);
        mode=0;
        break;
    default:
        break;
    }
}

void danmoku::wing(){
    for(int i=0;i<10;++i){
        bullet *b=new bullet;
        connect(this,&danmoku::clearall,b,&bullet::clear);
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
        b->setPos(b1->x()+10*cos((-100-5*i)*M_PI/180),b1->y()+10*sin((-100-5*i)*M_PI/180));

        scene->addItem(static_cast<QGraphicsItem*>(b));
        connect(b->t1,&QTimer::timeout,b,&bullet::fly24);
        b->t1->start(30);
    }
    times++;
    if(times>=50){
        b1->t1->stop();
        times=0;
    }
}

void danmoku::use_flower(){
    type='f';
    flower_card();
    connect(b1->ctrl1,&QTimer::timeout,this,&danmoku::flower_cardp2);
    connect(b1->ctrl2,&QTimer::timeout,this,&danmoku::flower_cardp3);
    connect(b1->ctrl1,&QTimer::timeout,b1->ctrl1,&QTimer::stop);
    connect(b1->ctrl2,&QTimer::timeout,b1->ctrl2,&QTimer::stop);
    connect(end,&QTimer::timeout,b1->t2,&QTimer::stop);
    connect(end,&QTimer::timeout,this,&danmoku::clear);
    connect(end,&QTimer::timeout,end,&QTimer::stop);
    b1->ctrl1->start(1500);
    b1->ctrl2->start(3000);
    end->start(5700);
    b1->t2->start(20);
}

void danmoku::use_star(){
    type='s';
    b1->setPos(300,50);
    b1->r=8;
    b2->r=8;
    b2->setPos(300,300);
    connect(b1->t1,&QTimer::timeout,b1,&bullet::fly_star);
    connect(b2->t1,&QTimer::timeout,b2,&bullet::fly_unstar);
    connect(b1->t2,&QTimer::timeout,this,&danmoku::skill_star);
    connect(b1->ctrl2,&QTimer::timeout,b1->ctrl1,&QTimer::stop);
    connect(b1->ctrl2,&QTimer::timeout,b1->ctrl2,&QTimer::stop);
    connect(b1->ctrl2,&QTimer::timeout,this,&danmoku::clear);
    b1->t1->start(10);
    b1->t2->start(10);
    b2->t1->start(10);
    b1->ctrl1->start(2000);
    b1->ctrl2->start(3400);
}

void danmoku::use_wind(){
    b1->t1->start(50);
    switch (mode) {
    case 0:
    {
        connect(b1->t1,&QTimer::timeout,this,&danmoku::wind);
        mode++;
    }
        break;
    case 1:
    {
        disconnect(b1->t1,&QTimer::timeout,this,&danmoku::wind);
        connect(b1->t1,&QTimer::timeout,this,&danmoku::windm);

        mode++;
    }
        break;
    case 2:
    {
        disconnect(b1->t1,&QTimer::timeout,this,&danmoku::windm);
        mode=0;
    }
        break;
    default:
        break;
    }
}

void danmoku::use_ring(){
    switch (mode) {
    case 0:
    {
        connect(b1->t1,&QTimer::timeout,this,&danmoku::ring);
        b1->t1->start(20);
        b1->ctrl1->start(3000);
        mode++;
    }
        break;
    case 1:
    {
        disconnect(b1->t1,&QTimer::timeout,this,&danmoku::ring);
        mode=0;
    }
        break;
    default:
        break;
    }
}

void danmoku::use_laser(){
    switch (mode) {
    case 0:
    {
        connect(b1->t1,&QTimer::timeout,this,&danmoku::reflect);
        b1->t1->start(20);
        mode++;
    }
        break;
    case 1:
    {
        disconnect(b1->t1,&QTimer::timeout,this,&danmoku::reflect);
        mode=0;
    }
        break;
    default:
        break;
    }
}

void danmoku::reflect(){
    bullet *b=new bullet;
    b->theta=t*M_PI/360;
    connect(this,&danmoku::clearall,b,&bullet::clear);
    b->setPixmap(QPixmap(":/bullet/laser.png").transformed(QMatrix().rotate(t/2)));
    scene->addItem(static_cast<QGraphicsItem *>(b));
    b->setPos(b1->x()+b1->pixmap().width()/2,b1->y()+b1->pixmap().height()/2);
    b->t1->start(20);
    connect(b->t1,&QTimer::timeout,b,&bullet::fly_ref);
    t++;
}

void danmoku::skill_star(){
    five_star(b1);
    five_star(b2);
    t--;
    times++;
    if(times>=50){
        t=0;
        times=0;
    }
}

void danmoku::skill_flower(){
    for(int i=0;i<5;++i){
        flower_wave(b[i]);
    }
}

void danmoku::circle(){
    bullet *b=new bullet;
    connect(this,&danmoku::clearall,b,&bullet::clear);
    b->setPixmap(bpng[1]);
    b->theta=t*M_PI/8;
    scene->addItem(static_cast<QGraphicsItem *>(b));
    b->setPos(b1->x()+b1->pixmap().width()/2+10*cos(b->theta),b1->y()+b1->pixmap().height()/2+10*sin(b->theta));
    b->theta=t*M_PI/8;
    b->time=50;
    connect(b1->ctrl1,&QTimer::timeout,b,&bullet::t1_start);
    connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
    //b->t1_start();
    t++;
}

void danmoku::ring(){
        bullet *b=new bullet;
        connect(this,&danmoku::clearall,b,&bullet::clear);
        b->setPixmap(bpng[1]);
        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(b1->x()+b1->pixmap().width()/2,b1->y()+b1->pixmap().height()/2);
        b->theta=t*M_PI/20;
        b->time=50;
        connect(b1->ctrl1,&QTimer::timeout,b,&bullet::t1_start);
        connect(b->t1,&QTimer::timeout,b,&bullet::fly23);

        bullet *b2=new bullet;
        connect(this,&danmoku::clearall,b2,&bullet::clear);
        b2->setPixmap(bpng[3]);
        scene->addItem(static_cast<QGraphicsItem *>(b2));
        b2->setPos(b1->x()+b1->pixmap().width()/2,b1->y()+b1->pixmap().height()/2);
        b2->theta=t*M_PI/20;
        b2->angle=-M_PI/180;
        b2->r=4.5;
        b2->time=50;
        connect(b1->ctrl1,&QTimer::timeout,b2,&bullet::t1_start);
        connect(b2->t1,&QTimer::timeout,b2,&bullet::fly23);

        bullet *b3=new bullet;
        connect(this,&danmoku::clearall,b3,&bullet::clear);
        b3->setPixmap(bpng[2]);
        b3->r=4;
        scene->addItem(static_cast<QGraphicsItem *>(b3));
        b3->setPos(b1->x()+b1->pixmap().width()/2,b1->y()+b1->pixmap().height()/2);
        b3->theta=t*M_PI/20;
        b3->time=50;
        connect(b1->ctrl1,&QTimer::timeout,b3,&bullet::t1_start);
        connect(b3->t1,&QTimer::timeout,b3,&bullet::fly23);

        t++;
}

void danmoku::wave(bullet *bin){
        bullet *b=new bullet;
        connect(this,&danmoku::clearall,b,&bullet::clear);
        QPixmap p;
        p=bin->pixmap();
        p=p.scaled(15,15);
        b->time=30;
        b->r=3;
        connect(bin->ctrl1,&QTimer::timeout,b,&bullet::t1_start);

        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(bin->x()+bin->pixmap().width()/2,bin->y()+bin->pixmap().height()/2);
        b->theta=t*M_PI/45;
        QMatrix m;
        m.rotate(bin->angle*180/M_PI);
        p=p.transformed(m,Qt::SmoothTransformation);
        b->setPixmap(p);
        connect(b->t1,&QTimer::timeout,b,&bullet::fly2);

        /*bullet *b2=new bullet;
        b2->time=80;
        b2->r=10;
        connect(b1->ctrl1,&QTimer::timeout,b2,&bullet::t1_start);
        b2->setPixmap(bpng[2]);
        scene->addItem(static_cast<QGraphicsItem *>(b2));
        b2->setPos(bin->x()+bin->pixmap().width()/2,bin->y()+bin->pixmap().height()/2);
        b2->theta=(t+180)*M_PI/25;
        connect(b2->t1,&QTimer::timeout,b2,&bullet::fly2);*/
t--;
}

void danmoku::flower_wave(bullet *bin){
        bullet *b=new bullet;
        connect(this,&danmoku::clearall,b,&bullet::clear);
        QPixmap p;
        p=bin->pixmap();
        p=p.scaled(15,15);
        b->time=30;
        b->r=3;
        connect(bin->ctrl1,&QTimer::timeout,b,&bullet::t1_start);

        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(bin->x()+bin->pixmap().width()/2,bin->y()+bin->pixmap().height()/2);
        b->theta=t*M_PI/45;
        QMatrix m;
        m.rotate(bin->angle*180/M_PI);
        p=p.transformed(m,Qt::SmoothTransformation);
        b->setPixmap(p);
        connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
t--;
}

void danmoku::flower(){
        bullet *b=new bullet;
        connect(this,&danmoku::clearall,b,&bullet::clear);
        //b->ctrl1->start(500);
        b->setPixmap(bpng[t%2+1]);
        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(b1->x()+b1->pixmap().width()/2+20*cos(t*M_PI/10),b1->y()+b1->pixmap().height()/2+20*sin(t*M_PI/10));
        if(cos(t*M_PI/10)!=0){
                b->theta=t*M_PI/60;
                connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
                connect(b1->ctrl1,&QTimer::timeout,b,&bullet::t1_start);
        }
        t++;
}

void danmoku::wind(){
    for(int i=0;i<4;++i){
        bullet *b=new bullet;
        connect(this,&danmoku::clearall,b,&bullet::clear);
        b->setPixmap(bpng[3-i]);
        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(b1->x()+b1->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),b1->y()+b1->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
        if(cos(t*M_PI/10)!=0){
                b->theta=(t+i*45)*M_PI/90;
                connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
                b->time=30;
                b->r=8;
                b->t1_start();
        }
    }
        t++;
}

void danmoku::windm(){
    for(int i=0;i<4;++i){
        bullet *b=new bullet;
        connect(this,&danmoku::clearall,b,&bullet::clear);
        b->setPixmap(bpng[i]);
        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(b1->x()+b1->pixmap().width()/2+10*cos((t+i*45)*M_PI/90),b1->y()+b1->pixmap().height()/2+10*sin((t+i*45)*M_PI/90));
        if(cos(t*M_PI/10)!=0){
                b->theta=(t+i*45)*M_PI/90;
                connect(b->t1,&QTimer::timeout,b,&bullet::fly22);
                b->time=30;
                b->r=8;
                b->t1_start();
                //connect(b1->ctrl1,&QTimer::timeout,b,&bullet::t1_start);
        }
    }
t++;
}

void danmoku::five_star(bullet *bin){
    for(int i=0;i<5;++i){
        bullet *b=new bullet;
        connect(this,&danmoku::clearall,b,&bullet::clear);
        b->time=10;
        b->angle=72*i*M_PI/180;
        connect(b1->ctrl1,&QTimer::timeout,b,&bullet::t2_start);
        connect(b->t2,&QTimer::timeout,b,&bullet::fly_angle);
        connect(b1->ctrl2,&QTimer::timeout,b,&bullet::t1_start);
        connect(b1->ctrl2,&QTimer::timeout,b->t2,&QTimer::stop);
        b->setPixmap(bin->pixmap().scaled(12,12));
        scene->addItem(static_cast<QGraphicsItem *>(b));
        b->setPos(bin->x()+bin->pixmap().width()/2,bin->y()+bin->pixmap().height()/2);
        b->theta=t*M_PI/25;
        connect(b->t1,&QTimer::timeout,b,&bullet::fly2);
    }

}

void danmoku::flower_card(){
    connect(b1->t2,&QTimer::timeout,this,&danmoku::skill_flower);
    for(int i=0;i<5;++i){
        this->b[i]=new bullet;
        b[i]->theta=(-90+72*i)*M_PI/180;
        b[i]->angle=(-72+72*i)*M_PI/180;
        b[i]->flyangle=M_PI/100;
        b[i]->setPixmap(QPixmap(":/bullet/card_r.png"));
        b[i]->setPos(b1->x()+50*cos(b[i]->theta),b1->y()+50*sin(b[i]->theta)+10);
        scene->addItem(static_cast<QGraphicsItem *>(b[i]));
        connect(b[i]->t1,&QTimer::timeout,b[i],&bullet::fly_angle);
        connect(b[i]->t1,&QTimer::timeout,b[i],&bullet::change_angle);

        b[i]->r=2;
        b[i]->t2->start(50);
        b[i]->t1->start(8);
        b[i]->ctrl1->start(3000);
    }
}

void danmoku::flower_cardp2(){
    for(int i=0;i<5;++i){
        this->b[i]=new bullet;
        b[i]->theta=(-90+72*i)*M_PI/180;
        b[i]->angle=(-72+72*i)*M_PI/180;
        b[i]->flyangle=M_PI/130;
        b[i]->setPixmap(QPixmap(":/bullet/card_p.png"));
        b[i]->setPos(b1->x()+150*cos(b[i]->theta),b1->y()+150*sin(b[i]->theta)+10);
        scene->addItem(static_cast<QGraphicsItem *>(b[i]));
        connect(b[i]->t1,&QTimer::timeout,b[i],&bullet::fly_angle);
        connect(b[i]->t1,&QTimer::timeout,b[i],&bullet::change_angle);
        b[i]->r=2;
        b[i]->t2->start(50);
        b[i]->t1->start(8);
        b[i]->ctrl1->start(5000);
    }
}

void danmoku::flower_cardp3(){
    for(int i=0;i<5;++i){
        this->b[i]=new bullet;
        b[i]->theta=(90+72*i)*M_PI/180;
        b[i]->angle=(120+72*i)*M_PI/180;
        b[i]->flyangle=M_PI/145;
        b[i]->setPixmap(QPixmap(":/bullet/card_g.png"));
        b[i]->setPos(b1->x()+250*cos(b[i]->theta),b1->y()+250*sin(b[i]->theta)+10);
        scene->addItem(static_cast<QGraphicsItem *>(b[i]));
        connect(b[i]->t1,&QTimer::timeout,b[i],&bullet::fly_angle);
        connect(b[i]->t1,&QTimer::timeout,b[i],&bullet::change_angle);
        b[i]->r=3;
        b[i]->t2->start(50);
        b[i]->t1->start(8);
        b[i]->ctrl1->start(6500);
    }
}

danmoku::~danmoku()
{
    delete ui;
}

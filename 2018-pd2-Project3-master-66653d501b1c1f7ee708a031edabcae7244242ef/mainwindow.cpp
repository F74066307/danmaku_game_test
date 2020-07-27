#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0,0,750,2000)),
    graphicsview(new QGraphicsView(scene,this))
{
    ui->setupUi(this);
    srand(time(NULL));
    p=new player;
    boss=new maria;
    banner=new QGraphicsScene(1000,0,200,300);
    info=new QGraphicsView(banner,this);
    info->setGeometry(1000,0,300,1000);
    graphicsview->setGeometry(200,0,800,2300);
    graphicsview->setObjectName("view");
    graphicsview->setStyleSheet("#view{border-image:url(:/background/bg1.jpg)}");

    result=new QGraphicsPixmapItem;

    score=new QLabel(this);
    score->setNum(grade);
    score->setAlignment(Qt::AlignRight);
    QFont f;
    f.setPointSize(24);
    QGraphicsTextItem *t=banner->addText("Boss HP:");
    t->setPos(950,-160);
    t->setFont(f);
    QGraphicsTextItem *t2=banner->addText("Score:");
    t2->setPos(950,-240);
    t2->setFont(f);
    QGraphicsTextItem *t3=banner->addText("Player Left:");
    t3->setPos(950,-50);
    t3->setFont(f);
    QGraphicsTextItem *t4=banner->addText("Skill(press P):");
    t4->setPos(950,50);
    t4->setFont(f);
    score->setFont(f);
    score->setGeometry(1100,140,100,30);
    bosshp=new QLabel(this);
    bosshp->setNum(boss->hp);
    bosshp->setFont(f);
    bosshp->setGeometry(1100,240,100,30);
    bosshp->setAlignment(Qt::AlignRight);

    connect(scoreup,&QTimer::timeout,this,&MainWindow::score_up);

    for(int i=0;i<6;++i){
        lp[i]=new QGraphicsPixmapItem;
        lp[i]->setPixmap(QPixmap(":/bullet/lp.png").scaled(30,30));
        lp[i]->setPos(1000+i*35,0);
        banner->addItem(lp[i]);
    }
    for(int i=0;i<5;++i){
        skill_time[i]=new QGraphicsPixmapItem;
        skill_time[i]->setPixmap(QPixmap(":/bullet/skill.png").scaled(30,30));
        skill_time[i]->setPos(1000+i*35,100);
        banner->addItem(skill_time[i]);
    }

    protect->setPixmap(QPixmap(":/bullet/s_bullet2.png").scaled(100,100));
    protect->setObjectName("p");
    protect->theta=-90*M_PI/180;
    connect(protect->t1,&QTimer::timeout,protect,&bullet::fly2);
    connect(protect->t1,&QTimer::timeout,this,&MainWindow::use_skill);
    this->setFocusPolicy(Qt::StrongFocus);
    connect(move,&QTimer::timeout,p->life,&bullet::fly2);
    connect(move,&QTimer::timeout,this,&MainWindow::playermove);
    connect(p->shoot_time,&QTimer::timeout,this,&MainWindow::shoot);
    hitcheck=new QTimer;
    connect(hitcheck,&QTimer::timeout,this,&MainWindow::hit);

    connect(p->shoot_time,&QTimer::timeout,this,&MainWindow::shoot);
    connect(boss->shoot_time,&QTimer::timeout,this,&MainWindow::attack);
    close=new QPushButton(this);
    close->setGeometry(100,500,60,50);
    close->setText("close");
    connect(close,&QPushButton::clicked,this,&MainWindow::closed);
    connect(levelup,&QTimer::timeout,this,&MainWindow::exp);
    levelup->start(3000);
}

void MainWindow::closed(){
    hitcheck->stop();
    scoreup->stop();
    grade=0;
    score->setNum(grade);
    skill_left=5;
    for(int i=0;i<6;++i){
        if(lp[i]->scene()==NULL){
            banner->addItem(lp[i]);
        }

    }
    for(int i=5;i>=0;--i){
        if(skill_time[i]->scene()==NULL){
            banner->addItem(skill_time[i]);
        }
    }
    boss->hp=boss->maxhp;
    bosshp->setNum(boss->hp);
    p->hp=6;
    if(p->b1->scene()!=NULL){
       scene->removeItem(static_cast<QGraphicsItem *>(p->b1));
       scene->removeItem(static_cast<QGraphicsItem *>(p->b2));
    }
    if(boss->b1->scene()!=NULL){
       scene->removeItem(static_cast<QGraphicsItem *>(boss->b1));
       scene->removeItem(static_cast<QGraphicsItem *>(boss->b2));
    }
    if(boss->scene()!=NULL){
        boss->dead();
        scene->removeItem(static_cast<QGraphicsItem *>(boss));
    }
    if(p->scene()!=NULL){
        p->dead();
        scene->removeItem(static_cast<QGraphicsItem *>(p));
        if(p->life->scene()!=NULL){
            scene->removeItem(static_cast<QGraphicsItem *>(p->life));
        }
    }
    this->hide();
}

void MainWindow::game_start(){
    stage=0;
    boss->stage=0;
    if(graphicsview->scene()!=scene){
        graphicsview->setScene(scene);
    }
    hitcheck->start(100);
    p->start();
    boss->start();
    scene->addItem(static_cast<QGraphicsItem *>(p));
    scene->addItem(static_cast<QGraphicsItem *>(p->life));
    scene->addItem(static_cast<QGraphicsItem *>(boss));
    p->setPos(400,400);
    p->life->setPos(p->x()+27,p->y()+25);
    score->show();
    bosshp->show();
    levelup->start(3000);

    scoreup->start(1000);

}

void MainWindow::playermove(){
    p->setPos(p->life->x()-27,p->life->y()-25);
    if(p->b1->scene()!=NULL&&p->b2->scene()!=NULL)
    {
        p->b1->setPos(p->x()-30,p->life->y());
        p->b2->setPos(p->x()+70,p->life->y());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    p->setPos(e->x()-50,e->y()-110);
    p->life->setPos(p->x()+27,p->y()+25);
    if(p->b1->scene()!=NULL&&p->b2->scene()!=NULL)
    {
        p->b1->setPos(p->x()-30,p->life->y());
        p->b2->setPos(p->x()+70,p->life->y());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    switch (e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        move->start(20);
        p->life->theta=-90*M_PI/180;
        break;
    case Qt::Key_Down:
    case Qt::Key_X:
        move->start(20);
        p->life->theta=90*M_PI/180;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        move->start(20);
        p->life->theta=0;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        move->start(20);
        p->life->theta=180*M_PI/180;
        break;
    case Qt::Key_1:
        if(p->life->scene()!=NULL){
            p->life->scene()->removeItem(p->life);
        }
        else{
            scene->addItem(p->life);
        }
        break;
    case Qt::Key_P:
        if(protect->scene()==NULL&&skill_left!=0){
            scene->addItem(static_cast<QGraphicsItem*>(protect));
            skill_left--;
            banner->removeItem(skill_time[skill_left]);
            playerskill();
        }
        break;
    default:
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
    move->stop();
}

void MainWindow::hit(){
    if(scene->collidingItems(static_cast<QGraphicsItem*>(p->life)).at(0)!=p){
        foreach (QGraphicsItem *b, scene->collidingItems(p->life)) {
            if(b!=p){
            if(static_cast<bullet*>(b)->objectName()=="exp"){
                ep++;
                if(ep==4){
                    emit p->mode_up();
                    ep=0;
                }
                static_cast<bullet*>(b)->clear();
            }
            else{
                if(p->life->scene()!=NULL){
                    if(p->hp!=0){
                         p->hp--;
                         banner->removeItem(lp[p->hp]);
                        static_cast<bullet*>(b)->clear();
                                }
                                else{
                                    scene->removeItem(p);
                                    scene->removeItem(p->life);
                                    p->dead();
                                    scoreup->stop();
                                    final_result();
                                }
                }

            }
        }
        }
 }

    if(!scene->collidingItems(static_cast<QGraphicsItem*>(boss)).empty()){
        if(boss->scene()!=NULL){
            foreach (QGraphicsItem *b, scene->collidingItems(boss)) {
                if(static_cast<bullet *>(b)->code==1){
                    if(boss->hp>=0){
                        boss->hp=boss->hp-30;
                        if(boss->scene()!=NULL){
                        bosshp->setNum(boss->hp);
                        }
                    }
                    static_cast<bullet *>(b)->clear();
                    if(boss->hp<=boss->maxhp/2&&boss->bullet_mode<10){
                        scene->addItem(static_cast<QGraphicsItem *>(boss->b1));
                        scene->addItem(static_cast<QGraphicsItem *>(boss->b2));
                        boss->final_skill();
                    }
                    if(boss->hp<=0){
                        if(stage<5){
                            boss_bonus+=boss->maxhp;
                            boss->dead();
                            stage++;
                            boss->stage=stage;
                            boss->start();
                            scene->addItem(static_cast<QGraphicsItem*>(boss));
                            bosshp->setNum(boss->hp);
                            scene->removeItem(boss->b1);
                            scene->removeItem(boss->b2);

                        }
                        else{
                            boss_bonus+=boss->maxhp;
                            boss->dead();
                            if(boss->b1->scene()!=NULL){
                                scene->removeItem(static_cast<QGraphicsItem *>(boss->b1));
                                scene->removeItem(static_cast<QGraphicsItem *>(boss->b2));
                            }
                            final_result();
                            break;
                        }
                    }
                }
            }
            }
        }

}

void MainWindow::final_result(){
   scoreup->stop();
   QGraphicsScene *for_result=new QGraphicsScene(300,300,400,600);
   if(p->scene()==NULL){
       result->setPixmap(QPixmap(":/background/Lose.png").scaled(500,100));
   }
   else if(boss->scene()==NULL){
       result->setPixmap(QPixmap(":/background/win.png").scaled(500,100));
   }
   result->setPos(250,-500);
   for_result->addItem(result);
   QFont f;
   f.setPointSize(18);
   QGraphicsTextItem *t=for_result->addText("Time Score :");
   t->setDefaultTextColor(Qt::cyan);
   t->setPos(250,-360);
   t->setFont(f);
   t=for_result->addText("quick clear bonus :");
   t->setDefaultTextColor(Qt::cyan);
   t->setPos(250,-300);
   t->setFont(f);
   t=for_result->addText("skill left bonus :");
   t->setDefaultTextColor(Qt::cyan);
   t->setPos(250,-240);
   t->setFont(f);
   t=for_result->addText("boss killed bonus :");
   t->setDefaultTextColor(Qt::cyan);
   t->setPos(250,-180);
   t->setFont(f);

   t=for_result->addText(QString().setNum(grade));
   t->setDefaultTextColor(Qt::cyan);
   t->setPos(600,-360);
   t->setFont(f);
   if(boss->scene()==NULL){
       if(grade/100<=120){
          t=for_result->addText(QString().setNum(50000));
          grade+=50000;
          t->setDefaultTextColor(Qt::cyan);
          t->setPos(600,-300);
          t->setFont(f);
       }
       else if(grade/100>120&&grade/100<=300){
           t=for_result->addText(QString().setNum(20000));
           grade+=20000;
           t->setDefaultTextColor(Qt::cyan);
           t->setPos(600,-300);
           t->setFont(f);
       }
      if(skill_left!=0){
          t=for_result->addText(QString().setNum(5000*skill_left));
          grade+=5000*skill_left;
          t->setDefaultTextColor(Qt::cyan);
          t->setPos(600,-240);
          t->setFont(f);
      }
       t=for_result->addText(QString().setNum(boss_bonus));
       grade+=boss_bonus;
       t->setDefaultTextColor(Qt::cyan);
       t->setPos(600,-180);
       t->setFont(f);
   }
   t=for_result->addText(QString().setNum(grade));
   t->setDefaultTextColor(Qt::cyan);
   t->setPos(600,-120);
   t->setFont(f);
   graphicsview->setScene(for_result);
}

void MainWindow::score_up(){
    grade=grade+100;
    score->setNum(grade);
}

void MainWindow::use_skill(){
    if(protect->scene()!=NULL){
        if(!scene->collidingItems(protect).empty()){
            foreach (QGraphicsItem *b, scene->collidingItems(protect)) {
                if(b!=boss&&b!=p){
                    if(b!=boss->b1&&b!=boss->b2&&static_cast<bullet *>(b)->code==0){
                        static_cast<bullet *>(b)->clear();
                    }
                }
            }
        }
    }
}

void MainWindow::playerskill(){
    protect->setPos(p->x(),p->y()-100);
    protect->t1->start(20);
}

void MainWindow::attack(){
    boss->mode(scene);
}

void MainWindow::shoot(){
     p->mode(scene);
    if(p->bullet_mode==2){
        if(p->b1->scene()==NULL||p->b2->scene()==NULL)
        {
            p->b1->setPos(p->x()-30,p->life->y());
            p->b2->setPos(p->x()+70,p->life->y());
            scene->addItem(static_cast<QGraphicsItem *>(p->b1));
            scene->addItem(static_cast<QGraphicsItem *>(p->b2));
        }
    }

}

void MainWindow::exp(){
    bullet *exp=new bullet;
    QPixmap pix;
    int x=rand()%400+100;
    exp->setPos(x,-100);
    pix.load(":/bullet/exp.png");
    exp->setPixmap(pix.scaled(40,40));
    exp->setObjectName("exp");
    exp->theta=M_PI/2;
    connect(exp->t1,&QTimer::timeout,exp,&bullet::fly2);
    scene->addItem(static_cast<QGraphicsItem*>(exp));
    exp->t1->start(30);
    if(p->bullet_mode==2){
        levelup->stop();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

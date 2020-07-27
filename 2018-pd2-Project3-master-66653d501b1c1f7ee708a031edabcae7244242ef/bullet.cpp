#include "bullet.h"

bullet::bullet()
{
    t1=new QTimer;
    t2=new QTimer;
    ctrl1=new QTimer;
    ctrl2=new QTimer;
    time=100;
    r=5;
    angle=M_PI/360;
    flyangle=0;
}

void bullet::clear(){
    t1->stop();
    t2->stop();
    ctrl1->stop();
    ctrl2->stop();
    this->scene()->removeItem(this);
    delete this;
}

void bullet::fly_ref(){
    this->setPos(x()+r*cos(theta),y()+r*sin(theta));
    if(x()>=700||x()<=100||y()>=600||y()<=-100){
        if(ref<=3){
            theta=theta-M_PI;
            this->pixmap()=this->pixmap().transformed(QMatrix().rotate(theta*180/M_PI));
            ref++;
        }
        else{
            clear();
        }
    }
}

void bullet::fly_down()
{
        this->setPos(this->x(),this->y()+1);
        if(y()>=1500){
            this->scene()->removeItem(this);
            delete this;
            t1->stop();
        }
        t++;
}
void bullet::fly_up(){
    this->setPos(x(),y()-1);
    t++;
}
void bullet::fly_r(){
    this->setPos(x()+1,y());
    t++;
}

void bullet::fly_l(){
    this->setPos(x()-1,y());
    t++;
}
void bullet::fly2(){
    this->setPos(x()+r*cos(theta),y()+r*sin(theta));
    if(this->objectName()=="life"){
        if(x()>=600||x()<=200||y()>=100||y()<=-100){
             this->theta=theta-M_PI;
        }
    }
    else if(this->objectName()=="player"){
        if(x()>=700||x()<=50||y()>=600||y()<=-300){
             this->theta=theta-M_PI;
        }
    }
    else if(this->objectName()=="p"){
        if(this->y()<=-100){
            this->t1->stop();
            this->scene()->removeItem(this);
        }
    }
    else if(x()>=750||x()<=-100||y()>=800||y()<=-200){
        if(this->objectName()!="life"&&this->objectName()!="player"){
            clear();
        }

    }
}

void bullet::fly22(){
    this->setPos(x()+r*cos(theta),y()-r*sin(theta));
}

void bullet::fly23(){
    this->setPos(x()+r*cos(theta),y()+r*sin(theta));
    theta=theta+angle;
    if(x()>=1000||x()<=0||y()>=1600||y()<=-80){
        clear();
    }
}

void bullet::fly24(){
    if(now<90){
        this->setPos(x()+r*cos(theta),y()+r*sin(theta));
        theta=theta+angle;
        if(angle<0){
            this->setPixmap(QPixmap(":/bullet/knife_b.png").transformed(QMatrix().rotate((theta-120)*180/M_PI)));
        }
        else {
         this->setPixmap(QPixmap(":/bullet/knife_r.png").transformed(QMatrix().rotate((theta-90)*180/M_PI)));
        }
        now++;
    }
    else if(now==90){
        angle=theta;
        fly_angle();
        now++;
    }
    else{
        fly_angle();
    }
}
void bullet::fly_angle(){
     this->setPos(x()+r*cos(angle),y()+r*sin(angle));
    if(x()>=700||x()<=100||y()>=600||y()<=-100){
            clear();
        }
}


void bullet::t1_start(){
    t1->start(time);
}

void bullet::t2_start(){
    t2->start(15);
}

void bullet::change_angle(){
        angle=angle+flyangle;
    if(t==152){
        this->scene()->removeItem(this);
        t1->stop();
        t2->stop();
        t=0;
    }
    t++;
}

void bullet::fly_star(){
    if(now<=30){
        theta=72*M_PI/180;

    }
    else if(now>30&&now<=60){
        theta=-144*M_PI/180;
    }
    else if(now>60&&now<=90){
        theta=0;
    }
    else if(now>90&&now<=120){
        theta=-216*M_PI/180;;
    }
    else if(now>120&&now<150){
        theta=-72*M_PI/180;
    }
    else if(now==150){
        theta=0;
        now=0;
        t2->stop();
        t1->stop();
    }
    fly2();
    now++;
}


void bullet::fly_unstar(){
    if(now<=30){
        theta=-108*M_PI/180;

    }
    else if(now>30&&now<=60){

        theta=36*M_PI/180;
    }
    else if(now>60&&now<=90){

        theta=M_PI;
    }
    else if(now>90&&now<=120){

        theta=-36*M_PI/180;
    }
    else if(now>120&&now<=150){
        theta=108*M_PI/180;
    }
    else{
       this->t1->stop();
       this->t2->stop();
        now=0;
    }
    fly2();
    now++;
}

void bullet::specialmove(){
    if(t<=300){
        fly_l();
        fly_down();
    }
    else if(t>=300&&t<=420){
        fly_l();
        fly_up();
    }
    else if(t>=420&&t<=600){
        fly_l();
        fly_down();
    }
    else if(t>=600&&t<=720){
        fly_r();
        fly_down();

    }
    if(t>=720){
        t1->stop();
        t2->stop();
    }

}


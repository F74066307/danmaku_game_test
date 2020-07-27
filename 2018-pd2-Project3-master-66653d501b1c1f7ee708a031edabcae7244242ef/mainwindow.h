#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QKeyEvent>
#include<QMouseEvent>
#include<QLabel>
#include <QTimer>
#include"bullet.h"
#include"chara.h"
#include"player.h"
#include"maria.h"
#include<cmath>
#include<QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
friend class chara;
friend class player;
friend void shoot();
public:
    explicit MainWindow(QWidget *parent = 0);
    void hit();
    void shoot();
    void attack();
    void score_up();
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void playermove();
    void playerskill();
    void use_skill();
    void game_start();
    void closed();
    void final_result();
    void exp();
    ~MainWindow();
    int t=0;
    int times=0;
    int m=0;
    int skill_left=5;
    int grade=0;
    bullet *b1=new bullet;
    bullet *b2=new bullet;
    bullet *b3=new bullet;
    bullet *b4=new bullet;
    bullet *b[5];
    QPixmap bpng[4];
    QTimer *move=new QTimer;
    QTimer *scoreup=new QTimer;
    QTimer *levelup=new QTimer;
    QLabel *score;
    QLabel *bosshp;
    chara *p;
    maria *boss;
    QGraphicsPixmapItem *lp[6],*skill_time[5],*result;
    bullet *protect=new bullet;
    QTimer *hitcheck;
    QPushButton *close;
    int ep=0;
    int stage=0;
    int boss_bonus=0;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene,*banner;
    QGraphicsView *graphicsview,*info;
};

#endif // MAINWINDOW_H

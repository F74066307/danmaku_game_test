#ifndef DANMOKU_H
#define DANMOKU_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QLabel>
#include <QTimer>
#include <cmath>
#include <cstdlib>
#include <QPushButton>
#include "bullet.h"

namespace Ui {
class danmoku;
}

class danmoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit danmoku(QWidget *parent = 0);
    void ring();
    void circle();
    void wave(bullet *bin);
    void flower();
    void flower_wave(bullet *bin);
    void flower_card();
    void flower_cardp2();
    void flower_cardp3();
    void wind();
    void windm();
    void wing();
    void reflect();
    void five_star(bullet *bin);
    void skill_star();
    void skill_flower();
    void clear();
    void use_flower();
    void use_star();
    void use_wind();
    void use_ring();
    void use_laser();
    void use_wing();
    void to_clear();

    ~danmoku();
    bullet *b1=new bullet;
    bullet *b2=new bullet;
    bullet *b3=new bullet;
    bullet *b4=new bullet;
    bullet *b[5];
    QPixmap bpng[4];
    QTimer *end=new QTimer;
    char type;
    int t=0;
    int times=0;
    int mode=0;
signals:
    void clearall();

private:
    Ui::danmoku *ui;
    QGraphicsScene *scene;
    QGraphicsView *graphicsview;

};

#endif // DANMOKU_H

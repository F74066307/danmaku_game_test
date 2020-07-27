#include "top.h"
#include "ui_top.h"

top::top(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::top)
{
    ui->setupUi(this);
    this->setObjectName("top");
    this->setStyleSheet("#top{border-image:url(:/background/image.jpg)}");
    start=new QPushButton(this);
    start->setText("Game Start!");
    start->setGeometry(400,500,100,30);
    danmoku=new QPushButton(this);
    danmoku->setText("Danmoku mode");
    danmoku->setGeometry(600,500,120,30);
}

top::~top()
{
    delete ui;
}

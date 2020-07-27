#include "mainwindow.h"
#include "top.h"
#include "danmoku.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    top t;
    danmoku d;
    t.showMaximized();
    QObject::connect(t.start,&QPushButton::clicked,&w,&MainWindow::showMaximized);
    QObject::connect(t.start,&QPushButton::clicked,&w,&MainWindow::game_start);
    QObject::connect(t.danmoku,&QPushButton::clicked,&d,&MainWindow::showMaximized);
    return a.exec();
}

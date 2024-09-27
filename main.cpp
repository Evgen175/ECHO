#include "mainwindow.h"

#include <QApplication>

double R=0, S=0, a=0, RAD = PI/180;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTextCodec* codec = QTextCodec::codecForName("UTF-8"); //основной пит
    //QTextCodec::setCodecForTr(codec);
    //QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    MainWindow w;
    w.show();
    return a.exec();
}

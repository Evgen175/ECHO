#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PI 3.14159265359

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtDebug>
#include <qtextcodec.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern double R, S, a, RAD, Reflex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DrawShem(const int &R, const int &S, const int &a);

private slots:
    void on_spin_R_valueChanged(int arg1);

    void on_spin_S_valueChanged(int arg1);

    void on_spin_a_valueChanged(double arg1);

    void on_spin_Reflex_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

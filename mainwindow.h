#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PI 3.14159265359


#include <QMainWindow>
#include <QGraphicsScene>
#include <QtDebug>
#include <qtextcodec.h>
//#include <math.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern double R, S, a, RAD;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DrawShem(const int &R, const int &S, const int &a);
    //int *koor (float f, int g);

    //QList <double> PointTangent(double &point_Ax, double &point_Ay, double &point_Cx, double &point_Cy, double &radius_R); // координату точки касательной

    //int Distans_A (double point_Ax, double point_Ay, double point_Cilx, double point_Cily); //Расстояние от центра окружности до точки

  //  QPair <double, double> SearchPoint(double x0, double y0, double x1, double y1, double r);
private slots:
    void on_spin_R_valueChanged(int arg1);

    void on_spin_S_valueChanged(int arg1);

    void on_spin_a_valueChanged(double arg1);

    //void resizeEvent(QResizeEvent *);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

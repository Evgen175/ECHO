#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "searchpoint.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spin_R->setValue(250);
    ui->spin_R->setRange(10,500);
    ui->spin_S->setValue(50);
    ui->spin_S->setRange(1,500*1.2);
    ui->spin_a->setValue(75);
    ui->spin_a->setRange(0,180);
    ui->spin_Reflex->setMinimum(5);
    ui->spin_Reflex->setValue(Reflex);
    R=ui->spin_R->value();
    S=ui->spin_S->value();
    a=ui->spin_a->value();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawShem(const int &R, const int &S, const int &)
{
    static QGraphicsScene *graphicsScene = new QGraphicsScene(this);
    if (!ui->graphicsView->scene()) {
        ui->graphicsView->setScene(graphicsScene);
        ui->graphicsView->scene()->setBackgroundBrush(QBrush(QColor(180, 180, 180)));
    }

    if (R == 0 || S == 0 || R<(S*1.02)) return;
    //ui->graphicsView->scene()-> height() * .25 / 2;

    graphicsScene->clear(); //   graphicsScene->addEllipse(0,0,100,100);
    double  x0 = 0,
            y0 = 0,
            R1 = R - S,
            x0_l = x0,
            y0_l = y0 - R,
            x0_end = x0_l +  cos (a * RAD),
            y0_end = y0_l + sin (a * RAD);

    graphicsScene-> addEllipse(x0 - R, y0 - R, R * 2, R * 2, QPen(Qt::red, 1), QBrush(QColor(0, 200, 200)));
    graphicsScene-> addEllipse(x0 - R + S, y0 - R + S, R1 * 2, R1 * 2 , QPen(Qt::red, 1), QBrush(QColor(180, 180, 180)));

    QPair<double, double> pai = SearchPoint::Point(x0_l, y0_l , x0_end, y0_end, R1);
    double   l_X_E = pai.first/*,
            l_Y_E = pai.second * -1*/;

    float   AB = (l_X_E),
            CA = R1,
            sin_A= (AB/CA);

    if (sin_A<0.0000001 && sin_A > -.0000001) return;
    double xp=x0,yp=-R;
    QPair <double, double> koor;
    qDebug() << "-------------------------------\nТочка вхождения\t\t  X\t  Y\ta";
    ui->textEdit->append("-------------------------------\nТочка вхождения\t\t  X\t  Y\ta");
    for (int var = 1, var1 = 0; var < Reflex; ++var, ++var1) {
        float   x1 = cos(sin_A * var - 90 * RAD) * (var %2 != 0 ? R1 : R),
                y1 = sin(sin_A * var - 90 * RAD) * (var %2 != 0 ? R1 : R);
        koor = SearchPoint::Point(x1 , y1, cos((sin_A * var + 1) - 90 * RAD) * (var1 %2 == 0 ? R1 : R),
                           sin((sin_A * var+1) - 90 * RAD) * (var1 %2 == 0 ? R1 : R), (var1 %2 == 0 ? R1 : R));
        graphicsScene->addLine(xp, yp, x1, y1, QPen(QColor(125, 255 - var * 2, 125), 1));


        qDebug() << "Тчк отраж. от" << QString(var == 1 ? "вхожден" : var1 %2 != 0 ? "внутр" : "внешн") << "D\t" << QString::number(xp) <<"\t" << -yp << "\t" << round((cos(sin_A * var) / RAD * 100)) / 100 <<"\t" << x1 << "\t " << y1 * -1;

        auto yu = "Тчк отраж. от " + QString(var == 1 ? "вхожден" : (var1 %2 != 0) ? "внутр D ":"внешн D ") + "\t" + QString::number(xp) + "\t" + QString::number(-yp) + "\t" + QString::number(round((cos(sin_A * var) / RAD * 100)) / 100) + "\t" + QString::number(x1) + "\t " + QString::number(y1 * -1);


        ui->textEdit->append(yu);
    xp = x1;
    yp = y1;
    }
}

void MainWindow::on_spin_R_valueChanged(int _R)
{
    R=_R;
    DrawShem(R, S, a);
}

void MainWindow::on_spin_S_valueChanged(int _S)
{
    S=_S;
    DrawShem(R, S, a);
}

void MainWindow::on_spin_a_valueChanged(double _a)
{
    a=_a;
    DrawShem(R, S, a);
}

void MainWindow::on_spin_Reflex_valueChanged(int arg1)
{
    if (Reflex < 5)  ui->spin_Reflex->setValue(5);
    Reflex = arg1;
    DrawShem(R, S, a);
}

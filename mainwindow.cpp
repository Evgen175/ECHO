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
    double   l_X_E = pai.first,
            l_Y_E = pai.second * -1;

    float   AB = (l_X_E),
            BC = (l_Y_E),
            CA = R1,
            sin_A= (AB/CA);
/*
//    qDebug() << "СТОРОНА КАТЕТ X  l_X_E  = " << AB << "\t" << sin_A;
//    qDebug() << "СТОРОНА КАТЕТ Y  l_Y_E  = " << BC << "COS a" << "=" <<sin_A/RAD;
//    qDebug() << "СТОРОНА ГИПОТИНУЗА = " << CA;

//    qDebug() << "l_X_E" << l_X_E << "\tl_Y_E" << l_Y_E<< "\n";

//    graphicsScene->addLine(x0_l, y0_l, x0_end, y0_end, QPen(Qt::black, .8));

   // graphicsScene->addLine(x0_l, y0_l, l_X_E, l_Y_E, QPen(Qt::red, 2));
    //graphicsScene->addLine(x0,y0, l_X_E, l_Y_E, QPen(Qt::yellow, 2));
    //graphicsScene->addLine(x0,y0, l_X_E*5, l_Y_E*5, QPen(Qt::yellow, 2));

   // graphicsScene->addEllipse(l_X_E-l_X_E, l_Y_E-l_X_E, l_X_E * 2, l_X_E * 2, QPen(Qt::blue, .2));
    //====================================
    graphicsScene->addLine(-300,0, 300, 0);
    graphicsScene->addLine(0,-300,0, 300);
    //====================================
    //float xp=x0,yp=-R,x1p,y1p;
*/
    if (sin_A<0.0000001 && sin_A > -.0000001) return;
    double xp=x0,yp=-R;
    QPair <double, double> koor;
    qDebug() << "-------------------------------\nТочка вхождения\t\t  X\t  Y\ta";
    for (int var = 1, var1=0; var < 17; ++var,++var1) {
        float   x1 = cos(sin_A * var - 90 *RAD) * (var%2!=0?R1:R),
                y1 = sin(sin_A * var - 90 *RAD) * (var%2!=0?R1:R);
        koor = SearchPoint::Point(x1 , y1, cos((sin_A * var+1) - 90 *RAD) * (var1%2==0?R1:R),
                           sin((sin_A * var+1) - 90 *RAD) * (var1%2==0?R1:R), (var1%2==0?R1:R));
        graphicsScene->addLine(xp, yp, x1, y1, QPen(QColor(125, 255-var*2, 125), 1));
        qDebug() << "Тчк отраж. от" << QString(var==1?"вхожден" : var1%2!=0? "внутр":"внешн")<<"D\t" << xp <<"\t"<<-yp <<"\t" << round((cos(sin_A*var)/RAD*100))/100 <<"\t" << x1<< "\t " << y1*-1;
    xp=x1;
    yp=y1;
 //   qDebug() << var << sin_A*var/RAD;


  //  graphicsScene->addLine(x0, y0, x1, y1, QPen(QColor(0, 255-var*20, 0), 2));
   // qDebug() << var << sin_A*var/RAD;
    }
    //********************************************
//    graphicsScene->addLine(0, l_Y_E, l_X_E, l_Y_E, QPen(QColor(125,0,125),1));
//    graphicsScene->addLine(l_X_E, 0, l_X_E, l_Y_E, QPen(QColor(125,0,125),1));
}

//----------------------------------------------------------------
//QPair<double, double> MainWindow::SearchPoint(double x0, double y0, double x1, double y1, double r){
//    double  A = (x1 - x0) * -1.f,
//            B   = (y1 - y0),
//            C1  = x0 * B * -1.f,
//            C2  = y0 * A * -1.f,
//            C   = C1 + C2,
//            X0  = -A * C / (pow(A,2) + pow(B,2)),
//            Y0  = -B * C / (pow(A,2) + pow(B,2));
//    //************************************************************
//    double  C_P=pow(C, 2),
//            R_P=pow(r, 2)*(pow(A, 2)+pow(B, 2)),
//            AB_P=pow(A, 2)+pow(B, 2);

//    if (C_P > R_P){
//        qDebug() << "Нет точки пересечения";
//        return QPair<double, double> (QPair<double, double> {0,0});
//    }
//    double  d = pow(r,2) - C_P /AB_P,
//                mult = sqrt(d/AB_P),
//                ax = Y0 + A * mult,
//            ay = (X0 - B * mult)*-1/*,
//                by = X0 + B * mult,
//                bx = Y0 - A * mult*/;
//    return QPair<double, double> (QPair<double, double> {ax,ay}) ;
//}

//QList <double> MainWindow::PointTangent(double &point_Ax, double &point_Ay, double &point_Cx, double &point_Cy, double &radius_R){
//    double dx = point_Ax - point_Cx,
//           dy = point_Ay - point_Cy,
//           L = sqrt(dx * dx + dy * dy),
//           jtg = (float)radius_R / L, // SIN Угла между прямой от центра до точки и касательной к радиусуж*/
//           itg = sqrt(1.f - jtg * jtg), // COS Угла ...
//               // L_Kas= itg * L,
//           Xtg = itg * dx * itg + itg * dy * jtg,
//           Ytg = -itg * dx * jtg - itg * dy * itg;
//    return QList <double> {Xtg, Ytg};
//}

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

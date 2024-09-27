#include "searchpoint.h"

QPair<double, double> SearchPoint::Point(double x0, double y0, double x1, double y1, double r){
    double  A = (x1 - x0) * -1.f,
            B   = (y1 - y0),
            C1  = x0 * B * -1.f,
            C2  = y0 * A * -1.f,
            C   = C1 + C2,
            X0  = -A * C / (pow(A,2) + pow(B,2)),
            Y0  = -B * C / (pow(A,2) + pow(B,2));
    //************************************************************
    double  C_P=pow(C, 2),
            R_P=pow(r, 2)*(pow(A, 2)+pow(B, 2)),
            AB_P=pow(A, 2)+pow(B, 2);

    if (C_P > R_P){

        return QPair<double, double> (QPair<double, double> {0,0});
    }
    double  d = pow(r,2) - C_P /AB_P,
            mult = sqrt(d/AB_P),
            ax = Y0 + A * mult,
            ay = (X0 - B * mult)*-1/*,
                by = X0 + B * mult,
                bx = Y0 - A * mult*/;
    return QPair<double, double> (QPair<double, double> {ax,ay}) ;
}

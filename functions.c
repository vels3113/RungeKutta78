#include <math.h>

/*functions from equations with array of variables*/

double funcR(double* v, double t);
double funcR(double* v, double t)
{
    return sqrt(1 + v[2]*v[2] + v[3]*v[3] + t*0);
}

/*double funcx(double* v, double t);
double funcx(double* v, double t)
{
    return v[2]/funcR(v, t);
}

double funcy(double* v, double t);
double funcy(double* v, double t)
{
    return v[3]/funcR(v, t);
}

double funcP(double* v, double t);
double funcP(double* v, double t)
{
    return exp(v[0])*(0.5*sin(v[1]/2)*cos(t)-0.75*v[3]*cos(v[1]/2)*sin(t)/funcR(v, t));
}

double funcQ(double* v, double t);
double funcQ(double* v, double t)
{
    return exp(v[0])*cos(v[1]/2)*(cos(t)+0.75*v[2]*sin(t)/funcR(v, t));
}*/

double funcs(double*, double, int);
double funcs(double* v, double t, int j)
{
    switch (j)
    {
        case 0: return v[2]/funcR(v, t);
        case 1: return v[3]/funcR(v, t);
        case 2: return exp(v[0])*(0.5*sin(v[1]/2)*cos(t)-0.75*v[3]*cos(v[1]/2)*sin(t)/funcR(v, t));
        case 3: return exp(v[0])*cos(v[1]/2)*(cos(t)+0.75*v[2]*sin(t)/funcR(v, t));
    }
    return 0;
}

double maxd(double* v, double);
double maxd(double* v, double t)
{
    double pd[11];
    double m, R3;
    m = 0.;
    int i;
    R3 = pow(funcR(v, t),3);
    pd[0] = (1 + v[3]*v[3])/R3;
    pd[1] = - v[2]*v[3]/R3;
    pd[2] = (1 + v[2]*v[2])/R3;
    pd[3] = funcs(v, t, 2);
    pd[4] = exp(v[0])*(cos(v[1]/2)*cos(t)/4 + 3*v[3]*sin(v[1]/2)*sin(t)/(8*funcR(v,t)));
    pd[5] = 3*exp(v[0])*v[2]*v[3]*cos(v[1]/2)*sin(t)/(4*R3);
    pd[6] = - 3*exp(v[0])*(1 + v[2]*v[2])*cos(v[1]/2)*sin(t)/(4*R3);
    pd[7] = funcs(v, t, 3);
    pd[8] = - exp(v[0])*sin(v[1]/2)*(cos(t) + 3*v[2]*sin(t)/(4*funcR(v,t)))/2;
    pd[9] = 3*exp(v[0])*cos(v[1]/2)*(1 + v[3]*v[3])*sin(t)/(4*R3);
    pd[10] = - 3*exp(v[0])*cos(v[1]/2)*v[2]*v[3]*sin(t)/(4*R3);
    pd[0] = fabs(pd[0]) + fabs(pd[1]);
    pd[1] = fabs(pd[2]) + fabs(pd[1]);
    if(pd[5] > 0)
    {
        pd[2] = pd[5] + fabs(pd[3]) + fabs(pd[4]) + fabs(pd[6]);
    }
    else
    {
        pd[2] = fabs(pd[5] - fabs(pd[3]) - fabs(pd[4]) - fabs(pd[6]));
    }
    if(pd[10] > 0)
    {
        pd[3] = pd[10] + fabs(pd[7]) + fabs(pd[8]) + fabs(pd[9]);
    }
    else
    {
        pd[3] = fabs(pd[10] - fabs(pd[7]) - fabs(pd[8]) - fabs(pd[9]));
    }
    for(i = 0; i < 4; i++)
    {
        if(m < pd[i])
        {
            m = pd[i];
        }
    }
    return m;
}

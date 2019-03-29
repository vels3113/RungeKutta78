#include<math.h>

double resize(double e, double r, double h, double t);
double resize(double e, double r, double h, double t)
{
    const double meps = 2.20e-16;
    double c;
    c = pow(r/e, 1./6);
    if(c > 10)
        c = 10;
    if(c < 0.1)
        c = 0.1;
    if(t > 1)
    {
        if(0.95*h/c < meps*t)
        {
            return h;
        }
        else
        {
            return 0.95*h/c;
        }
    }
    else
    {
        if(0.95*h/c < meps)
        {
            return h;
        }
        else
        {
            return 0.95*h/c;
        }
    }
}

double maxerr(double* err);
double maxerr(double* err)
{
    int j;
    double max = 0.;
    for(j = 0; j <= 3; j++)
    {
        if(max < fabs(err[j]))
        {
            max = fabs(err[j]);
        }
    }
    return max;
}

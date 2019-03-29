#include<math.h>
double maxerr(double* err);
double maxerr(double* err)
{
    int i = 0;
    double d = 0;
    for(i; i <= 3; i++)
    {
        if(d < fabs(err[i]))
        {
            d = fabs(err[i]);
        }
    }
    return d;
}

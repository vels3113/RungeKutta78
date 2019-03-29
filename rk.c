#include<stdlib.h>

void rk(double* v, double* err, double t, double h, double funcs(double*, double, int));
void rk(double* v, double* err, double t, double h, double funcs(double*, double, int))
//perepisat bez zamorazhivaniya peremennyh
{
    double k[24];
    double *vt;
    int j;
    vt = (double*)malloc(4*sizeof(double));//suda zapisyvaem izmenivsheesya znacheniya tochki
    for(j = 0; j <= 3; j++)
        k[j] = h*funcs(v, t, j);
    for(j = 0; j <= 3; j++)
        vt[j] = v[j] + k[j]/2.;
    for(j = 0; j <= 3; j++)
        k[1*4 + j] = h*funcs(vt, t + h/2., j);
    for(j = 0; j <= 3; j++)
        vt[j] = v[j] + k[j]/4. + k[1*4+j]/4.;
    for(j = 0; j <= 3; j++)
        k[2*4 + j] = h*funcs(vt, t + h/2., j);
    for(j = 0; j <= 3; j++)
        vt[j] = v[j] - k[1*4 + j] + 2*k[2*4 + j];
    for(j = 0; j <= 3; j++)
        k[3*4 + j] = h*funcs(vt, t + h, j);
    for(j = 0; j <= 3; j++)
        vt[j] = v[j] + 7*k[j]/27. + 10*k[1*4 + j]/27. + k[3*4 + j]/27.;
    for(j = 0; j <= 3; j++)
        k[4*4 + j] = h*funcs(vt, t + 2*h/3, j);
    for(j = 0; j <= 3; j++)
        vt[j] = v[j] + 28.*k[j]/625. - k[1*4 + j]/5. + 546.*k[2*4 + j]/625. + 54.*k[3*4 + j]/625. - 378.*k[4*4 + j]/625.;
    for(j = 0; j <= 3; j++)
        k[5*4 + j] = h*funcs(vt, t + h/5, j);
    for(j = 0; j <= 3; j++)
        v[j] += k[j]/24. + 5.*k[3*4 + j]/48. + 27.*k[4*4 + j]/56. + 125.*k[5*4 + j]/336.;
    for(j = 0; j <= 3; j++)
        err[j] = (-42.*k[j] - 224.*k[2*4 + j] - 21.*k[3*4 + j] + 162.*k[4*4 + j] + 125.*k[5*4 + j])/336.;
    free(vt);
}

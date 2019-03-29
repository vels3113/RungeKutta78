#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Formula Eulera*/
double mEuler(double s, double* v, double t, double h, double func(double*, double));
/*Runge-Kutta 5 poryadok*/
void rk(double* v, double* err, double t, double h, double func(double*, double, int));
double maxerr(double* err);
double maxd(double* v, double);
/*Proverka priemlimosti oshibki*/
double resize(double e, double r, double h, double t);
/*funcii iz uravneniy*/
double funcs(double* v, double t, int j);
/*double funcR(double* v, double t);
double funcx(double* v, double t);
double funcy(double* v, double t);
double funcP(double* v, double t);
double funcQ(double* v, double t);*/

int main(void)
{
    int i;
    const double meps = 2.20e-16;
    double t2, t, h, e, r, h1;
    double *var, *buf, *err, *gerr;
    FILE *datax, *datay, *dataP, *dataQ, *time, *errors;
    h = 0.001;
    e = 0.00000000001;
    // zadaem nachalnye usloviya
    t = 0.;
    var = (double*)malloc(4*sizeof(double));
    for (i=0; i<=3; i++)
      var[i] = 0.;
    if(var == NULL)
    {
        printf("Memory allocating error.\n");
        return 1;
    }
    buf = (double*)malloc(4*sizeof(double));
    if(buf == NULL)
    {
        printf("Memory allocating error.\n");
        free(var);
        return 1;
    }
    //iniiciruem massiv oshibok
    err = (double*)malloc(4*sizeof(double));
    if(err == NULL)
    {
        printf("Memory allocating error.\n");
        free(var);
        free(buf);
        return 1;
    }
    for (i=0; i<=3; i++)
      err[i] = 0.;
    gerr = (double*)malloc(4*sizeof(double));
    if(gerr == NULL)
    {
        printf("Memory allocating error.\n");
        free(var);
        free(buf);
        free(err);
        return 1;
    }
    for (i=0; i<=3; i++)
      gerr[i] = 0.;
    //schityvaem konechnuyu tochku
    printf("Enter endpoint.\n");
    scanf("%lf", &t2);
    if((t2 < 0) || (t2 > 10*M_PI))
    {
        printf("Value out of range of (0;10*pi)\n");
        free(var);
        free(buf);
        free(err);
        free(gerr);
        return 1;
    }
    //otkryvaem fayly dlya vyvoda dannyh
    datax = fopen("x.txt","w");
    if(datax == NULL)
    {
        printf("Opening output file error.\n");
        free(var);
        free(buf);
        free(err);
        free(gerr);
        return 1;
    }
    datay = fopen("y.txt","w");
    if(datay == NULL)
    {
        printf("Opening output file error.\n");
        fclose(datax);
        free(var);
        free(buf);
        free(err);
        free(gerr);
        return 1;
    }
    dataP = fopen("P.txt","w");
    if(dataP == NULL)
    {
        printf("Opening output file error.\n");
        fclose(datax);
        fclose(datay);
        free(var);
        free(buf);
        free(err);
        free(gerr);
        return 1;
    }
    dataQ = fopen("Q.txt","w");
    if(dataQ == NULL)
    {
        printf("Opening output file error.\n");
        fclose(datax);
        fclose(datay);
        fclose(dataP);
        free(var);
        free(buf);
        free(err);
        free(gerr);
        return 1;
    }
    time = fopen("time.txt","w");
    if(time == NULL)
    {
        printf("Opening output file error.\n");
        fclose(datax);
        fclose(datay);
        fclose(dataP);
        fclose(dataQ);
        free(var);
        free(buf);
        free(err);
        free(gerr);
        return 1;
    }
    errors = fopen("errors.txt","w");
    if(errors == NULL)
    {
        printf("Opening output file error.\n");
        fclose(datax);
        fclose(datay);
        fclose(dataP);
        fclose(dataQ);
        fclose(time);
        free(var);
        free(buf);
        free(err);
        free(gerr);
        return 1;
    }
    //zadaem shag
    fprintf(datax, "%.15e; 0\n", var[0]);
    fprintf(datay, "%.15e; 0\n", var[1]);
    fprintf(dataP, "%.15e; 0\n", var[2]);
    fprintf(dataQ, "%.15e; 0\n", var[3]);
    //integriruem
    while (t<t2)
    {
        if(t + h > t2)
        {
            h = t2 - t;
        }
        for(i = 0; i <= 3; i++)//schitaem v etom do proverki oshibki
            buf[i] = var[i];
        rk(buf, err, t, h, funcs);
        r = maxerr(err);
        if(r > e)
        {
            //h1 = resize(e, r, h, t);
            h1 = h;
            if(fabs(h1 - h) < meps)
            {
                h1 = exp(h*maxd(var,t));
                for(i = 0; i <= 3; i++)
                {
                    gerr[i] = fabs(err[i]) + gerr[i]*h1;
                    var[i] = buf[i];
                }
                t += h;
                fprintf(datax, "%.15e; %.15e\n", var[0], t);
                fprintf(datay, "%.15e; %.15e\n", var[1], t);
                fprintf(dataP, "%.15e; %.15e\n", var[2], t);
                fprintf(dataQ, "%.15e; %.15e\n", var[3], t);
                fprintf(time, "%.15e\n", t);
                fprintf(errors, "%.15e; %.15e; %.15e; %.15e; %.15e\n", err[0], err[1], err[2], err[3], t);
            }
            else
            {
                h = h1;
            }
        }
        else
        {
            h1 = exp(h*maxd(var,t));
            for(i = 0; i <= 3; i++)
            {
                gerr[i] = fabs(err[i]) + gerr[i]*h1;
                var[i] = buf[i];
            }
            t += h;
            fprintf(datax, "%.15e; %.15e\n", var[0], t);
            fprintf(datay, "%.15e; %.15e\n", var[1], t);
            fprintf(dataP, "%.15e; %.15e\n", var[2], t);
            fprintf(dataQ, "%.15e; %.15e\n", var[3], t);
            fprintf(time, "%.15e\n", t);
            fprintf(errors, "%.15e; %.15e; %.15e; %.15e; %.15e\n", err[0], err[1], err[2], err[3], t);
            //h = resize(e, r, h, t);
        }
    }
    /*for (i = 1; i <= 10000; i++)
    {
        for(j = 0; j <= 3; j++)
            buf[j] = var[j];
        t += h;
        //var[0] = mEuler(buf[0], buf, t, h, funcx);
        var[0] = rk(buf, 0, t, h, funcx);
        //var[1] = mEuler(buf[1], buf, t, h, funcy);
        var[1] = rk(buf, 1, t, h, funcx);
        //var[2] = mEuler(buf[2], buf, t, h, funcP);
        var[2] = rk(buf, 2, t, h, funcx);
        //var[3] = mEuler(buf[3], buf, t, h, funcQ);
        var[3] = rk(buf, 3, t, h, funcx);
        fprintf(datax, "%lf\n", var[0]);
        fprintf(datay, "%lf\n", var[1]);
        fprintf(dataP, "%lf\n", var[2]);
        fprintf(dataQ, "%lf\n", var[3]);
        fprintf(time, "%lf\n", t);
    }*/
    fprintf(time, "%.15e\n", t);
    fprintf(errors, "\n%.15e; %.15e; %.15e; %.15e", gerr[0], gerr[1], gerr[2], gerr[3]);
    fclose(time);
    fclose(datax);
    fclose(datay);
    fclose(dataP);
    fclose(dataQ);
    fclose(errors);
    free(buf);
    free(var);
    free(err);
    free(gerr);
    return 0;
}

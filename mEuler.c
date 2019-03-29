double mEuler(double s, double* v, double t, double h, double func(double*, double)) // metod Eulera
{
    return s + h*func(v, t);
}
//dlya odnoy peremennoy
/*{
    double f1, f2, f3, x1, x2, x3;
    double sum = 0.;
    int n = 10000;
    f1= func(a);
    x1 = a;
    x2 = a + (b - a)/n; //bez avtovybora shaga integrirovaniya
    x3 = x2 + (b - a)/n; //berem tri sosednie tochki iz razbieniya i znacheniya v nih
    f2 = func(x2);
    f3 = func(x3);
    while (x2 < b)
    {
        sum = (((x3-x1)/6) *( f1 + 4*f2 + f3)); //formula Simpsonz
        x1 = x3;
        f1 =f3;
        x2 = x1 + (b - a) / n;
        f2 = func(x2);
        x3 = x2 + (b - a) / n;
        f3 = func(x3);
    }
    return sum;
}*/

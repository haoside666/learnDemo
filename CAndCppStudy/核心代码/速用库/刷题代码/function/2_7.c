/*
input:1.0 0.4
output:2.319680
*/
#include <stdio.h>
#include <math.h>
#define TOL 1E-2

double dist(double h,double p);

int main()
{
    double h, p, d;
    scanf("%lf %lf", &h, &p);
    d = dist(h, p);
    printf("%.6f\n", d);
    return 0;
}
double dist(double h,double p)
{
    double sum=h;
    while(1)
    {		
        h*=p;
		if(fabs(h)<TOL) break;
		sum+=2*h;
    }
    return sum;
}



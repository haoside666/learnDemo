/*f(x,n)=x−x^2+x^3−x^4+⋯+(−1)x^n−1+x^n
​​ *input 0.5 12
 *output 0.33
 */
#include <stdio.h>

double fn(double x,int n);

int main()
{
    double x;
    int n;

    scanf("%lf %d", &x, &n);
    printf("%.2f\n", fn(x,n));

    return 0;
}

double fn(double x,int n)
{
	double temp=0,num=1;
	for(int i=1;i<=n;i++)
	{
		num*=x;
		temp+=i%2==1?num:-num;
	}
	return temp;
}


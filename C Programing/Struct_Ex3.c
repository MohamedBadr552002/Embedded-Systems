#include <stdio.h>
#include <stdlib.h>

typedef struct complex{
        float real;
        float imag;

      }complex;

 complex add(complex n1,complex n2);
int main()
{
    complex n1,n2,x;

    printf("enter a real part ");
    scanf("%f",&n1.real);
    printf("enter a imaginary part ");
    scanf("%f",&n1.imag);

    printf("enter a real part ");
    scanf("%f",&n2.real);
    printf("enter a imaginary part ");
    scanf("%f",&n2.imag);

    x=add(n1,n2);
    printf("sum : %0.1f +%0.1f i",x.real,x.imag);

    return 0;
}

complex add(complex n1,complex n2)
{
    complex sum;
    sum.real=n1.real+n2.real;
    sum.imag=n1.imag+n2.imag;

    return sum;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define cir_area(r) 3.14*(float)pow(r,2)
int main()
{
    int x;
    printf("Enter the radius : ");
    scanf("%d",&x);
    printf("area = %f",cir_area(x));

    return 0;
}

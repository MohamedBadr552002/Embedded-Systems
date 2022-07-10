/*
 * main.c
 *
 *  Created on: Jul 7, 2022
 *      Author: Mohamed
 */

#include <stdio.h>

int factorial(int x);
int product=1;
int main()
{
       int num,y;
	   printf("Enter a numbers:");
	   fflush(stdout);
	   scanf("%d" ,&num);
	   y= factorial(num);
	   printf("factorial of %d = %d",num,y);



	return 0;
}

int factorial(int x)
{

	if(x==0)
	{ return product; }

	product=product*x;
	factorial(--x);
}

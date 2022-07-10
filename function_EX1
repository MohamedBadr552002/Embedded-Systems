/*
 * main.c
 *
 *  Created on: Jul 7, 2022
 *      Author: Mohamed
 */

#include <stdio.h>

void print(int lower, int higher);
int is_prime(int x);
int main()
{
   int lower ,higher;
   printf("Enter two numbers:");
   fflush(stdout);fflush(stdin);
   scanf("%d  %d",&lower,&higher);

   print(lower,higher);




	return 0;
}
void print(int lower, int higher)
{
	printf("All prime number between %d to %d are: ", lower, higher);

	while(lower<=higher)
	{
		if(is_prime(lower))
		{
			printf("%d  ",lower);
		}
		lower++;
	}


}

int is_prime(int x)
{
   int i;
   for(i=2;i<=x/2;i++)
   {
	   if(x%i==0)
	   { return 0;}
   }

   return 1;
}

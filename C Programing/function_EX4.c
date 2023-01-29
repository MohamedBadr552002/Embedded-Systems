/*
 * main.c
 *
 *  Created on: Jul 7, 2022
 *      Author: Mohamed
 */

#include <stdio.h>
int product=1;
int power(int num,int pow);

int main()
{
       int x,y;
       printf("enter a num\n");
       fflush(stdout);
       scanf("%d",&x);

       printf("enter a power");
       fflush(stdout);
       scanf("%d",&y);

    printf("%d ^ %d= %d",x,y,power(x,y) );
	return 0;
}

int power(int num,int pow)
{
	product*=num;
   	pow--;
   	if(pow==0)
   	{return product;}
   	power(num,pow);

}

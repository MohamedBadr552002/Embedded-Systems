/*
 * main.c
 *
 *  Created on: Jul 6, 2022
 *      Author: Mohamed
 */

#include <stdio.h>
#include <string.h>

void main()
{   //Ex1
  /*	char s[100];
	printf("Enter a string:");
    fflush(stdout);
	gets(s);
	int i=0;
	char c;
	printf("Enter a character:");
	fflush(stdout);
	scanf("%c",&c);
	int counter=0;

	while(s[i]!=0)
	{
		if(s[i]==c)
		{counter++;}
		i++;
	}

	printf("frequncy of %c = %d",c, counter);*/

	//Ex2(length of string)

	 /*   char s[100];
		printf("Enter a string:");
	    fflush(stdout);
		gets(s);
		int i=0;
		int counter=0;

		while(s[i]!=0)
		{
			counter++;
			i++;
		}

		printf("length  = %d", counter); */

	//Ex3 (reverse )
	        char s[100];
			printf("Enter a string:");
		    fflush(stdout);
			gets(s);
			int l= strlen(s);

			char r[100];
            int j=l-1;
			for(int i=0;i<l;i++)
			{
				r[j]=s[i];
				j--;
			}
       printf("reverse string is :");
		   int i=0;
		   while(r[i]!=0)
		   {
			   printf("%c",r[i]);
			   i++;
		   }



}

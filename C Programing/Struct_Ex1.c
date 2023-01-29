#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student{
     char name[100];
     int n_roll;
     float marks;
}s1;
int main()
{     //enter information
      printf("Enter student name:  ");
      gets(s1.name);
      printf("Enter roll number:");
      scanf("%d",&s1.n_roll);
      printf("Enter Marks:");
      scanf("%f",&s1.marks);

      //print informations
      printf("Name :%s \n",s1.name);
      printf("Roll :%d \n",s1.n_roll);
      printf("Marks :%0.2f \n",s1.marks);




    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct student{
        char name[100];
        int n_roll;
        float marks;
      };
int main()
{
    struct student arr[2];

    for(int i=0;i<2;i++)
    {
       printf("Enter student name:  ");
       scanf("%s",&arr[i].name);
       printf("Enter roll number:");
       scanf("%d",&arr[i].n_roll);
       printf("Enter Marks:");
       scanf("%f",&arr[i].marks);
       printf("\n");

    }

    for(int i=0;i<2;i++)
    {
         printf("Name :%s \n",arr[i].name);
         printf("Roll :%d \n",arr[i].n_roll);
         printf("Marks :%0.2f \n",arr[i].marks);
         printf("\n");
    }


    return 0;
}

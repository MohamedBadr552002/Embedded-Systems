#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define max 50
#define no_Courses 7

typedef struct{
   int is_exist ;
   char F_name[40];
   char L_name[40];
   int ID;
   float GPA;
   int courses[no_Courses];

}Sdata;



Sdata buffer[max];

Sdata* head =buffer;
Sdata* base =buffer;
Sdata* tail =buffer;
Sdata* read =buffer;

//APIs
void add_student_details_manually(Sdata* queue);
void add_student_from_text_file();
void view_detal(Sdata* queue);
void search_about_couses(Sdata* queue);
void find_student();
int count_students(Sdata* queue);
void delet_student();
int update_student(Sdata* queue);
void find_student_by_Fname(Sdata* queue);

int search_for_roll(Sdata* queue,int num);




int main()
{
    char temp_text[40];

     while(1)
    {
        printf("\n \t choose one os these operations \n");
        printf("1 : Add student \n");
        printf("2 : Add from Text file \n");
        printf("3 : Search about Courses \n");
        printf("4 : find student by ID\n");
        printf("5 : Number of Students \n");
        printf("6 : Delet student \n");
        printf("7 : Update student \n");
        printf("8 : Search about students by frist name\n");
        printf("9 : view students \n");

        gets(temp_text);

        switch(atoi(temp_text))
        {
        case 1:
            add_student_details_manually(buffer);
            break;
        case 2:
            add_student_from_text_file();
            break;
        case 3:
            search_about_couses(buffer);
            break;
        case 4:
            find_student();
            break;
       case 5:
           printf("\n==============> Number of students = %d <==============\n",count_students(buffer));
           break;
        case 6:
            delet_student();
            break;
        case 7:
            update_student(buffer);
            break;
        case 8:
            find_student_by_Fname(buffer);
            break;
        case 9:
            view_detal(buffer);
            break;
        default:
            printf("\n======>Wrong option \n");
            break;
        }
    }
    return 0;
}



void add_student_details_manually(Sdata* queue)
{
    char temp_text[40];

    if((head - base)+1 == max)
    {
        printf("FULL \n");
    }
    else
    {
                printf("\nEnter the ID: ");
                gets(temp_text);
                head->ID = atoi(temp_text);

         if(search_for_roll(buffer,head->ID) == 0)
            printf("\n ERROR : this Id is already exist");
         else
         {
               head->is_exist =1;

                printf("\nEnter the first name: ");
                gets(head->F_name);

                printf("\nEnter the last name: ");
                gets(head->L_name);



                printf("\nEnter the GPA: ");
                gets(temp_text);
                head->GPA = atof(temp_text);

                for(int i=0;i<5;i++)
                {
                    printf("\nEnter ID course number %d: ",i);
                    gets(temp_text);
                    head->courses[i]= atoi(temp_text);
                }

         }


            }

    head++;
}

void add_student_from_text_file()
{
    if((head - base)+1 == max)
    {
        printf("FULL \n");
    }

    char file_name[50];

    printf("\n Enter the File name :");
    gets(file_name);

    FILE* pfile =NULL; //pointer to file

    pfile = fopen(file_name, "r");

    if(pfile == NULL)
    {
       printf("\n File does not Exist\n");
       return;
    }

    while(!feof(pfile)) //read untill the end of file
    {
        fscanf(pfile,"%d",&head->ID);
        int num = head->ID;


        // check if Id is exist
        if(search_for_roll(buffer ,num) == 0)
        {
            printf("\n number is repeted \n");
            fscanf(pfile, "%*[^\n]");
			continue ;
        }
        head->is_exist =1;
        fscanf(pfile,"%s",&head->F_name);
        fscanf(pfile,"%s",&head->L_name);
        fscanf(pfile,"%f",&head->GPA);

        for(int i =0 ;i< 5 ;i++)
		{
          fscanf(pfile , "%d" ,&head->courses[i]);
		}

	  head++;

    }

   fclose(pfile);

}

void view_detal(Sdata* queue)
{


    if((queue - base)+1 == max)
        queue = base;
    for(int i=0;i<max;i++)
    {

           if( queue->is_exist == 1)
            {

                printf("the first name : %s \n", queue->F_name);
                printf("the last name : %s \n", queue->L_name);
                printf("the ID : %d \n", queue->ID);
                printf("the GPA : %f \n", queue->GPA);
                printf("the COURSE number 1: %d \n", queue->courses[0]);
                printf("the COURSE number 2: %d \n", queue->courses[1]);
                printf("the COURSE number 3: %d \n", queue->courses[2]);
                printf("the COURSE number 4: %d \n", queue->courses[3]);
                printf("the COURSE number 5: %d \n", queue->courses[4]);
                printf("\n =====================================\n");


            }
           else
           {
               printf("==========>>no student \n");
           }

          queue++;
    }
}

void search_about_couses(Sdata* queue)
{
    char temp_text[40];
    int COURSE_ID;
    int counnt = 0;
    printf("\n enter the Course ID :");
    gets(temp_text);
    COURSE_ID = atoi(temp_text);


    while(counnt != max)
    {
         if(queue->is_exist == 1)
         {
           for(int j=0 ;j<no_Courses ;j++)
           {

                if(queue->courses[j] == COURSE_ID)
                    {printf("%s %s --->ID: %d \n",queue->F_name,queue->L_name,queue->ID);}

           }
         }

        queue++;
        counnt++;
    }


}

void find_student()
{
    char temp_text[40];
    int ST_ID;
    printf("\nEnter student ID :");
    gets(temp_text);
    ST_ID = atoi(temp_text);

    for(int i=0;i<max;i++)
    {
        if(read->is_exist ==1)
        {
            if(read->ID == ST_ID)
          {
            printf("the first name : %s \n", tail->F_name);
            printf("the last name : %s \n", tail->L_name);
            printf("the GPA : %f \n", tail->GPA);
            printf("the COURSE number 1: %d \n", tail->courses[0]);
            printf("the COURSE number 2: %d \n", tail->courses[1]);
            printf("the COURSE number 3: %d \n", tail->courses[2]);
            printf("the COURSE number 4: %d \n", tail->courses[3]);
            printf("the COURSE number 1: %d \n", tail->courses[4]);
            break;
          }
        }
        else
        {
            printf("\nStudent not found\n");
        }
        read++;
    }

    read = base;
}


int count_students(Sdata* queue)
{
    int count=0;

    for(int i=0;i<max;i++)
    {
        if(queue->is_exist == 1)
            count++;
        queue++;
    }

    return count;
}

void delet_student()
{
    char temp_text[40];
    int Id;
     Sdata* copy;
     Sdata* temp;
     Sdata* end;
     temp = base ;
     end = base + 4;
     printf("\n Enter the ID: ");
     gets(temp_text);
     Id =atoi(temp_text);
   for(int i=0;i<max;i++)
   {
       if(temp->is_exist == 1)
       {if(temp->ID == Id)
           {
              copy = temp + 1;
              while(temp != end) //shifting
              {
                  strcpy(temp->F_name,copy->F_name);
                  strcpy(temp->L_name,copy->L_name);
                  temp->ID = copy->ID;
                  temp->GPA = copy->GPA;

                  for(int j =0;j<no_Courses ;j++)
                  {
                      temp->courses[j]=copy->courses[j];
                  }
                  temp++;
                  copy++;
              }
              end->is_exist =0;
           }
       }
       temp++;
   }
}

int update_student(Sdata* queue)
{
    char temp_text[40];
    char choice[40];
    int ST_ID;
    printf("\nEnter student ID :");
    gets(temp_text);
    ST_ID = atoi(temp_text);

    for(int i=0;i<max;i++)
    {
        if(queue->is_exist == 1)
        {
            if(queue->ID == ST_ID)
            {
                printf("\n what do you want to update :\n");
                printf(" 1 : For First Name \n");
                printf(" 2 : For Last Name \n");
                printf(" 3 : For ID \n");
                printf(" 4 : For GPA \n");
                printf(" 5 : For Courses \n");
                gets(choice);

                switch(atoi(choice))
                {
                  case 1:
                           printf("\nEnter the first name: ");
                            gets(queue->F_name);
                            break;
                  case 2:
                    printf("\nEnter the last name: ");
                    gets(queue->L_name);
                    break;


                  case 3:
                    printf("\nEnter the ID: ");
                    gets(temp_text);
                    queue->ID = atoi(temp_text);
                    break;
                  case 4:
                       printf("\nEnter the GPA: ");
                       gets(temp_text);
                       queue->GPA = atof(temp_text);
                       break;
                  case 5:
                           for(int i=0;i<5;i++)
                            {
                               printf("\nEnter ID course number %d: ",i);
                               gets(temp_text);
                               queue->courses[i]= atoi(temp_text);
                            }
                            break;

                }
                            printf("\n Student has been updated \n");
                return 1;

            }
        }
        queue++;
    }
    printf("\n Student not found \n");
    return 0;
}

void find_student_by_Fname(Sdata* queue)
{
    char temp_text[40];
    printf("\nEnter student First name :");
    gets(temp_text);

    for(int i=0;i<max;i++)
    {
        if(queue->is_exist == 1)
        {
            if(strcmp(temp_text,queue->F_name)== 0)
            {
                printf("%s ",queue->F_name);
                printf("%s  ",queue->L_name);
                printf("ID:%d \n",queue->ID);
            }
        }
        queue++;
    }


}

int search_for_roll(Sdata* queue,int num)
{
    for(int i=0;i<max;i++)
    {
        if(queue->is_exist == 1)
        {
            if(queue->ID == num)
            {

                return 0;
            }

        }

        queue++;
    }

    return num;
}

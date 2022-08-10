#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


 typedef struct {
        int ID;
        char name[40];
        float Marks;
    }Sdata;

//node

 struct  Sstudent{
       Sdata student;
       struct Sstudent* p_next_student;
     };


 struct Sstudent* gp_first_student =NULL; //head


 //functions
 void Add_student();
 int Delet_Student();
 void Veiw_students();
 void Delet_All();
 int Get_Nth_node();
 void get_length();
 int detect_loop();


int main()
{
    char temp_text[40];

    while(1)
    {
        printf("\n \t choose one os these operations \n");
        printf("1 : Add student \n");
        printf("2 : delet student \n");
        printf("3 : view students \n");
        printf("4 : delet all \n");
        printf("5 : Get specific node \n");
        printf("6 : Get number of nodes \n");
        printf("7 : detect Loop \n");

        gets(temp_text);

        switch(atoi(temp_text))
        {
        case 1:
            Add_student();
            break;
        case 2:
            Delet_Student();
            break;
        case 3:
            Veiw_students();
            break;
        case 4:
            Delet_All();
            break;
        case 5:
           Get_Nth_node();
           break;
        case 6:
            get_length();
            break;
        case 7:
            detect_loop();
            break;
        default:
            printf("\n======>Wrong option \n");
            break;
        }
    }


    return 0;
}

void Add_student()
{
    struct Sstudent* pNew_student;
    struct Sstudent* pLast_student;
    char temp_text[40];

    //if list is empety
    //if yes
    if(gp_first_student==NULL)
    {
        //create new node
        pNew_student= (struct Sstudent*)malloc(sizeof(struct Sstudent));
        //make list between nodes
        gp_first_student = pNew_student;
    }
    else//no
    {   //loop until reach to last node
        pLast_student = gp_first_student;
        while (pLast_student->p_next_student)
            pLast_student=pLast_student->p_next_student;

        //create new node
        pNew_student= (struct Sstudent*)malloc(sizeof(struct Sstudent));
        //link the new node
        pLast_student->p_next_student=pNew_student;

    }
        //fill the node
        printf("\nEnter the name :");
        gets(pNew_student->student.name);

        printf("\nEnter the ID :");
        gets(temp_text);
        pNew_student->student.ID = atoi(temp_text);

        printf("\nEnter the Marks :");
        gets(temp_text);
        pNew_student->student.Marks = atof(temp_text);

    pNew_student->p_next_student=NULL;



}

int Delet_Student()
{
    int selected_ID;
    printf("\nEnter the ID to be removed : ");
    scanf("%d",&selected_ID);

    //make sure there is list
    if(gp_first_student)
    {
        struct Sstudent* pselected_st=gp_first_student;
        struct Sstudent* pPrevois_selected_st=NULL;
      //loop until find the selected ID
        while(pselected_st)
        {   //check if it the first one
           if(pselected_st->student.ID == selected_ID)
           {
               // compare each node with Id
              if(pPrevois_selected_st) //if it is not the first
              {
                 pPrevois_selected_st->p_next_student= pselected_st->p_next_student;
                 free(pselected_st);
                 return 1;
              }
              else//if it is the first
              {
                gp_first_student=pselected_st->p_next_student;
                free(pselected_st);
                return 1;
              }
           }
            pPrevois_selected_st=pselected_st;
            pselected_st=pselected_st->p_next_student;
        }
    }

    printf("\n=======>ID is not found");
    return 0;
}

void Veiw_students()
{
    struct Sstudent* pcurrent_st=gp_first_student;
    int count=0;
    //check if list is empty
    if(pcurrent_st == NULL)
    {
     printf("\n======>List is Empty\n");
    }
     else
     {
          while(pcurrent_st)
         { // show the data
           printf("\nThe Data of %d student : \n",count+1);
           printf("name : %s\n",pcurrent_st->student.name);
           printf("ID   : %d\n",pcurrent_st->student.ID);
           printf("Marks : %f\n",pcurrent_st->student.Marks);
           //looping
           pcurrent_st=pcurrent_st->p_next_student;
           count++;

         }
     }

}

void Delet_All()
{
    struct Sstudent* pcurrent_st=gp_first_student;

    //check if list is empty
    if(pcurrent_st == NULL)
    {
     printf("\n======>List is Empty\n");
    }
     else
     {
          while(pcurrent_st)
         {
             //looping
           struct Sstudent* ptemp_st=pcurrent_st;
           pcurrent_st=pcurrent_st->p_next_student;
           //delet
           free(ptemp_st);
         }
        gp_first_student=NULL;
     }
}

int Get_Nth_node()
{
    int count=0;
    int n;
    printf("\n Enter the number of node: \n");
    scanf("%d",&n);
    struct Sstudent* pcurrent_st=gp_first_student;

   //check if list is empty
    if(pcurrent_st == NULL)
    {
      printf("\n======>List is Empty\n");
      return 0;
    }
     else
     {
          while(pcurrent_st)
         {
             if(count == n-1)
             {
                 // show the data
                  printf("\nThe Data of %d student : \n",count+1);
                  printf("name : %s\n",pcurrent_st->student.name);
                  printf("ID   : %d\n",pcurrent_st->student.ID);
                  printf("Marks : %f\n",pcurrent_st->student.Marks);
                  return 1;
             }
             else
             {
                 pcurrent_st=pcurrent_st->p_next_student;
                 count++;

             }

         }
        printf("\n======>Node not found\n");
        return 0;

     }

}

void get_length()
 {
     int count =0;
     struct Sstudent* pcurrent_st=gp_first_student;
     //check if list is empty
     if(pcurrent_st == NULL)
     {
      printf("\n======>List is Empty\n");
     }
     else
     {
          while(pcurrent_st)
         {

             pcurrent_st=pcurrent_st->p_next_student;
             count++;

         }
        printf("\n======>Length of List = %d\n",count);
     }
 }

int detect_loop()
 {
     struct Sstudent* slow= gp_first_student;
     struct Sstudent* fast= gp_first_student;

     //check if list is empty
     if(fast == NULL)
     {
      printf("\n======>List is Empty\n");
     }
     else
     {
         while(slow && fast && fast->p_next_student)//detect the NULL
        {
          slow=slow->p_next_student;//make it move by one step
          fast=fast->p_next_student->p_next_student;//make it move by two steps

           if(slow == fast)
           {
             printf("\n=====>loop found\n");
             return 1;
           }
        }
        printf("\n=====>loop not found\n");
        return 0;
     }

 }

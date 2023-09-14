#include "stdint.h"


int VAL1=3;
int VAL2=7;
int VAL3=0;

int main()
{
    //inline asssembly with out put 
    //Frist parameter --> Output
    //Second parameter -> INput

    __asm("add %0,%1,%2",
    : "=r"(VAL3)
    :"r"(VAL1),
     "r"(VAL2) )  
     
    return 0;
}
#include "stdint.h"


int VAL1=3;

int main()
{
    //inline asssembly with out put 
    //Frist parameter --> Output
    //Second parameter -> INput

    __asm("mov r0,%0",
    : //empety output
    :"r"(VAL1) )  
     
    return 0;
}
#include "stdint.h"

int VAL1 =0;

int main()
{
    //inline assembly code
    __asm("mov %0 ,#0xFF"
    :"=r"(VAL1) )   //=r means store in General Purpose register without write on it 

    return 0;
}
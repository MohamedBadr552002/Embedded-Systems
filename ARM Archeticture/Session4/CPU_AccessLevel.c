enum CPU_AccessLevel{
    Privilaged,
    unPrivilaged
};




void Change_CPU_AccessLevel(enum level)
{
    switch(level)
    {
        case Privilaged:
            __asm("mov r3,CONTROL \t\n"
                  "lsr r3,r3,#0x1 \t\n"
                  "lsl r3,r3,#0x1 \t\n"
                  "msr CONTROL,r3");
            break;
        case unPrivilaged:
             __asm("mov r3,CONTROL \t\n"
                  "orr r3,r3,#0x1 \t\n"
                  "msr CONTROL,r3");
            break;    
    }

}
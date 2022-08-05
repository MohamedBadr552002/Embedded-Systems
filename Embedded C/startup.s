/*startup.s cortex m3*/

/* SRAM 0x20000000  */

.section .vector
.word 0x20001000                  /*stack top address*/
.word _reset                      /*reset*/
.word vector_handler            /*NMI*/
.word vector_handler           /*HARD Fault*/
.word vector_handler          /*MM Fault*/
.word vector_handler         /*Bus Fault*/
.word vector_handler        /*Usage Fault*/
.word vector_handler       /*REVERSED*/
.word vector_handler      /*REVERSED*/
.word vector_handler      /*REVERSED*/
.word vector_handler      /*REVERSED*/
.word vector_handler      /*SV call*/
.word vector_handler      /*Debug reversed*/
.word vector_handler      /*REVERSED*/
.word vector_handler      /*PendSV*/
.word vector_handler      /*Systick*/
.word vector_handler      /*IRQ0*/
.word vector_handler      /*IRQ1*/
.word vector_handler      /*IRQ2*/


.section .text
_reset:
    bl main
    b .

.thumb_func
vector_handler:
    b _reset

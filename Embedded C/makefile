
CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
project_name=learn

all: $(project_name).bin
	@echo "=======build is done ======"


%.o: %.c
	$(CC)gCC.exe $(CFLAGS) -c  $(INCS) $< -o $@

startup.o: startup.s
	$(CC)as.exe $(CFLAGS) $< -o $@	

$(project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@
	
$(project_name).bin: $(project_name).elf
	$(CC)objcopy.exe -O binary $< $@	
	
clear:
	rm *.elf *.bin

clear_all:
	rm 	*.o *.elf *.bin
CURDIR=$(shell pwd)
CPPFLAGS += -I$(CURDIR)/include

objs := start.o led.o main.o uart.o lcd.o
objs += lib/libc.a

BL2.bin: $(objs)
	$(LD) -Tlink.lds -o BL2_USB.elf $^
	$(OBJCOPY) -O binary BL2_USB.elf BL2.bin
	$(OBJDUMP) -D BL2_USB.elf > BL2_elf.dis
	
lib/libc.a:
	make -C ./lib

%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

clean:
	make clean -C ./lib
	rm *.o *.elf *.bin *.dis mkx210 -f

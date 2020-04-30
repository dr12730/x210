export TOOLS-PREFIX=/usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-
export CC		= $(TOOLS-PREFIX)gcc
export LD 		= $(TOOLS-PREFIX)ld
export OBJCOPY	= $(TOOLS-PREFIX)objcopy
export OBJDUMP	= $(TOOLS-PREFIX)objdump
export AR		= $(TOOLS-PREFIX)ar


export CURDIR=$(shell pwd)
export CPPFLAGS:=-nostdlib -nostdinc -I$(CURDIR)/include
export CFLAGS:=-Wall -O2 -fno-builtin

objs := start.o led.o sdram_init.o main.o uart.o clock.o key.o intc.o timer.o
objs += lib/libc.a

usb_timer.bin: $(objs)
	$(LD) -Tlink.lds -o timer.elf $^
	$(OBJCOPY) -O binary timer.elf usb_timer.bin
	$(OBJDUMP) -D timer.elf > timer_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 usb_timer.bin sd_timer.bin
	
lib/libc.a:
	cd lib; make; cd ..;

%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

clean:
	cd lib; make clean; cd ..;
	rm *.o *.elf *.bin *.dis mkx210 -f

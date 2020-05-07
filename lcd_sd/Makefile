export TOOLS-PREFIX=/usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-
export CC		= $(TOOLS-PREFIX)gcc
export LD 		= $(TOOLS-PREFIX)ld
export OBJCOPY	= $(TOOLS-PREFIX)objcopy
export OBJDUMP	= $(TOOLS-PREFIX)objdump
export AR		= $(TOOLS-PREFIX)ar
export CPPFLAGS:=-nostdlib -nostdinc
export CFLAGS:=-Wall -O2 -fno-builtin


all:
	make -C ./BL1
	make -C ./BL2

clean:
	make clean -C ./BL1
	make clean -C ./BL2
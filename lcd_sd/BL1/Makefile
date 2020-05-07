objs := start.o sdram_init.o copy_2_ddr.o clock.o
BL1.bin: $(objs)
	$(LD) -Tlink.lds -o BL1_USB.elf $^
	$(OBJCOPY) -O binary BL1_USB.elf BL1_USB.bin
	$(OBJDUMP) -D BL1_USB.elf > BL1_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 BL1_USB.bin BL1.bin

%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

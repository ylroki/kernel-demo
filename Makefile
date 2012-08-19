
ASM = nasm
ASM_BOOT_FLAG = -I boot/include/
ASM_KERNEL_FLAG = -I include/ -f elf

CC = gcc
C_FLAG = -I include/ -c

LD = ld
KERNEL_ENTRY = 0x30400
LD_FLAG = -s -Ttext ${KERNEL_ENTRY}

OBJS = obj/kernel.o

all: build/boot.bin build/loader.bin build/kernel.bin
	dd if=build/boot.bin of=image/my_os.img bs=512 count=1 conv=notrunc
	sudo mount image/my_os.img /mnt/floppy
	sudo cp build/loader.bin build/kernel.bin /mnt/floppy
	sudo umount /mnt/floppy

clean:
	rm obj/*.o
	rm build/*.bin
	sudo mount image/my_os.img /mnt/floppy
	sudo rm /mnt/floppy/*
	sudo umount /mnt/floppy

# build boot
build/boot.bin: boot/boot.asm boot/include/*.inc
	${ASM} ${ASM_BOOT_FLAG} -o $@ $<

build/loader.bin: boot/loader.asm boot/include/*.inc
	${ASM} ${ASM_BOOT_FLAG} -o $@ $<

# build kernel
obj/kernel.o: kernel/kernel.asm
	${ASM} ${ASM_KERNEL_FLAG} -o $@ $<

build/kernel.bin: ${OBJS}
	${LD} ${LD_FLAG} -o $@ ${OBJS}

# document
doc_env:
	xsltproc \
	--output docs/environment.html \
	/usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl \
	docs/environment.xml

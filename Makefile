
ASM = nasm
ASM_BOOT_FLAG = -I boot/include/
ASM_KERNEL_FLAG = -I include/ -f elf

CC = gcc
C_FLAG = -I include/ -c -fno-builtin -fno-stack-protector

LD = ld
KERNEL_ENTRY = 0x30400
LD_FLAG = -s -Ttext ${KERNEL_ENTRY}

OBJS = obj/kernel.o obj/string.o obj/start.o obj/protect.o obj/kliba.o obj/klib.o\
	obj/global.o obj/main.o

DOCBOOK_XSL = /usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl

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

# build lib
obj/string.o: lib/string.asm
	${ASM} ${ASM_KERNEL_FLAG} -o $@ $<

obj/kliba.o: lib/kliba.asm
	${ASM} ${ASM_KERNEL_FLAG} -o $@ $<

obj/klib.o: lib/klib.c
	${CC} ${C_FLAG} -o $@ $<

# build kernel
obj/kernel.o: kernel/kernel.asm
	${ASM} ${ASM_KERNEL_FLAG} -o $@ $<

obj/start.o: kernel/start.c
	${CC} ${C_FLAG} -o $@ $<

obj/protect.o: kernel/protect.c
	${CC} ${C_FLAG} -o $@ $<

obj/global.o: kernel/global.c
	${CC} ${C_FLAG} -o $@ $<

obj/main.o: kernel/main.c
	${CC} ${C_FLAG} -o $@ $<

build/kernel.bin: ${OBJS}
	${LD} ${LD_FLAG} -o $@ ${OBJS}


# picture

pic:
	cd docs/dot; ./configure ; make; rm -f Makefile
	mv docs/dot/*.png docs/res

# document
DOCS = docs/boot.html docs/protect_mode.html

docs: ${DOCS} ${PIC}

docs/boot.html: docs/boot.xml
	xsltproc --output $@ ${DOCBOOK_XSL} $<

docs/protect_mode.html: docs/protect_mode.xml
	xsltproc --output $@ ${DOCBOOK_XSL} $<



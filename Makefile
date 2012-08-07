boot:
	nasm boot.asm -o obj/boot.bin
	dd if=obj/boot.bin of=obj/a.img bs=512 count=1 conv=notrunc
	nasm loader.asm -o obj/loader.bin
	sudo mount -o loop obj/a.img /mnt/floppy
	sudo cp obj/loader.bin /mnt/floppy
	sudo umount /mnt/floppy
kernel:
	nasm -f elf -o obj/kernel.o kernel.asm
	ld -s -Ttext 0x30400 -o obj/kernel.bin obj/kernel.o
	sudo mount -o loop obj/a.img /mnt/floppy
	sudo cp obj/kernel.bin /mnt/floppy -v
	sudo umount /mnt/floppy

test:	
	nasm -f elf test.asm -o test.o
	ld -s test.o -o test

doc_env:
	xsltproc \
	--output docs/environment.html \
	/usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl \
	docs/environment.xml

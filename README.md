# Code file and directroy
	bochsrc		/* configuration of bochs */
	boot		/* booter,loader... */
	docs		/*  documents */
	include		/* struct, macro, declearation... */ 
	kernel		/* kernel */
	lib			/* common function like disp_str()... */
	Makefile	
	README

All operations below are tested in Lubuntu 13.04,
I suppose it also works at Ubuntu.

# Install bochs
bochs is a x86 PC emulator, it can run our kernel demo.
In order to enable debugger, you should download source and compile it.

For example, download file "bochs-2.6.1.tar.gz", and extract it.
```
$ tar -zxvf bochs-2.6.1.tar.gz
```

Before generating Makefile, maybe some librarys are needed.
```
$ sudo apt-get install gcc build-essential xorg-dev libgtk2.0-dev
```

Then, enter the source directory
```
$ cd bochs-2.6.1
```

There is a mistake to generate Makefile, we should fix it.
```
$ vim Makefile.in
```
At line 190 of Makefile.in, add "-lpthread"

Then, generate Makefile, compile, link, and install
```
$ ./configure --enable-debugger --enable-disasm 
$ make
$ sudo make install
```

# Prepare directory
At the root directory of our repository,

```
$ mkdir image
$ mkdir build
$ mkdir obj
$ cd /mnt;sudo mkdir floppy;cd -
```

# Creare image file
Create image file "my_os.img"
```
$ cd image
$ bximage
```
	
Make filesystem
```
$ mkfs.msdos my_os.img
$ cd ..
```

# Build
We need nasm
```
$ sudo apt-get install nasm
$ make all
$ make install
```

# Run bochs
The configure file "bochsrc" is in repository now, 
so just type 'bochs', OS's kernel placed at address 0x30400, 
you can make breakpoint at that address.



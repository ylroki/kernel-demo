SELECTOR_KERNEL_CS equ 8

extern cstart

extern g_gdt_ptr

[SECTION .bss]
StartSpace resb 2048
StackTop:

[section .text]
global _start

_start:
	mov esp, StackTop
	sgdt [g_gdt_ptr]
	call cstart
	lgdt [g_gdt_ptr]
	
	jmp SELECTOR_KERNEL_CS:csinit

csinit:
	push 0
	popfd
	hlt

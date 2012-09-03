SELECTOR_KERNEL_CS equ 8

extern cstart
extern exception_handler
extern mask_interrupt_handler
extern disp_str

extern g_gdt_ptr
extern g_idt_ptr
extern g_exited

[SECTION .bss]
StartSpace resb 2048
StackTop:

[section .text]
global _start

global	divide_error
global	single_step_exception
global	nmi
global	breakpoint_exception
global	overflow
global	bounds_check
global	inval_opcode
global	copr_not_available
global	double_fault
global	copr_seg_overrun
global	inval_tss
global	segment_not_present
global	stack_exception
global	general_protection
global	page_fault
global	copr_error

global  mask_int_func0
global  mask_int_func1
global  mask_int_func2
global  mask_int_func3
global  mask_int_func4
global  mask_int_func5
global  mask_int_func6
global  mask_int_func7
global  mask_int_func8
global  mask_int_func9
global  mask_int_func10
global  mask_int_func11
global  mask_int_func12
global  mask_int_func13
global  mask_int_func14
global  mask_int_func15



_start:
	mov esp, StackTop
	sgdt [g_gdt_ptr]
	call cstart
	lgdt [g_gdt_ptr]
	lidt [g_idt_ptr]
	
	sti
	jmp SELECTOR_KERNEL_CS:csinit

csinit:
	mov al, [g_exited]
	cmp al, 0
	je csinit

	jmp $


%macro  mask_int_func_master    1
        push    %1
        call    mask_interrupt_handler
        add     esp, 4
		iretd
%endmacro
; ---------------------------------



ALIGN 16
mask_int_func0:                ; Interrupt routine for irq 0 (the clock).
        mask_int_func_master    0
		
ALIGN 16
mask_int_func1:                ; Interrupt routine for irq 1 (keyboard)
        mask_int_func_master    1
		
ALIGN 16
mask_int_func2:                ; Interrupt routine for irq 2 (cascade!)
        mask_int_func_master    2
		
ALIGN 16
mask_int_func3:                ; Interrupt routine for irq 3 (second serial)
        mask_int_func_master    3
		
ALIGN 16
mask_int_func4:                ; Interrupt routine for irq 4 (first serial)
        mask_int_func_master    4
		
ALIGN 16
mask_int_func5:                ; Interrupt routine for irq 5 (XT winchester)
        mask_int_func_master    5
		
ALIGN 16
mask_int_func6:                ; Interrupt routine for irq 6 (floppy)
        mask_int_func_master    6
		
ALIGN 16
mask_int_func7:                ; Interrupt routine for irq 7 (printer)
        mask_int_func_master    7
		
; ---------------------------------
%macro  mask_int_func_slave     1
        push    %1
        call    mask_interrupt_handler
        add     esp, 4
		iretd
%endmacro
; ---------------------------------

ALIGN 16
mask_int_func8:                ; Interrupt routine for irq 8 (realtime clock).
        mask_int_func_slave     8
		
ALIGN 16
mask_int_func9:                ; Interrupt routine for irq 9 (irq 2 redirected)
        mask_int_func_slave     9
		
ALIGN 16
mask_int_func10:                ; Interrupt routine for irq 10
        mask_int_func_slave     10

ALIGN 16
mask_int_func11:                ; Interrupt routine for irq 11
        mask_int_func_slave     11
		
ALIGN 16
mask_int_func12:                ; Interrupt routine for irq 12
        mask_int_func_slave     12
		
ALIGN 16
mask_int_func13:                ; Interrupt routine for irq 13 (FPU exception)
        mask_int_func_slave     13
		
ALIGN 16
mask_int_func14:                ; Interrupt routine for irq 14 (AT winchester)
        mask_int_func_slave     14
		
ALIGN 16
mask_int_func15:                ; Interrupt routine for irq 15
        mask_int_func_slave     15
		


; 中断和异常 -- 异常
divide_error:
	push	0xFFFFFFFF	; no err code
	push	0		; vector_no	= 0
	jmp	exception
single_step_exception:
	push	0xFFFFFFFF	; no err code
	push	1		; vector_no	= 1
	jmp	exception
nmi:
	push	0xFFFFFFFF	; no err code
	push	2		; vector_no	= 2
	jmp	exception
breakpoint_exception:
	push	0xFFFFFFFF	; no err code
	push	3		; vector_no	= 3
	jmp	exception
overflow:
	push	0xFFFFFFFF	; no err code
	push	4		; vector_no	= 4
	jmp	exception
bounds_check:
	push	0xFFFFFFFF	; no err code
	push	5		; vector_no	= 5
	jmp	exception
inval_opcode:
	push	0xFFFFFFFF	; no err code
	push	6		; vector_no	= 6
	jmp	exception
copr_not_available:
	push	0xFFFFFFFF	; no err code
	push	7		; vector_no	= 7
	jmp	exception
double_fault:
	push	8		; vector_no	= 8
	jmp	exception
copr_seg_overrun:
	push	0xFFFFFFFF	; no err code
	push	9		; vector_no	= 9
	jmp	exception
inval_tss:
	push	10		; vector_no	= A
	jmp	exception
segment_not_present:
	push	11		; vector_no	= B
	jmp	exception
stack_exception:
	push	12		; vector_no	= C
	jmp	exception
general_protection:
	push	13		; vector_no	= D
	jmp	exception
page_fault:
	push	14		; vector_no	= E
	jmp	exception
copr_error:
	push	0xFFFFFFFF	; no err code
	push	16		; vector_no	= 10h
	jmp	exception

exception:
	call	exception_handler
	add	esp, 4*2	; 让栈顶指向 EIP，堆栈中从顶向下依次是：EIP、CS、EFLAGS
	iretd

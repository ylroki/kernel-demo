%include "const.inc"

extern kernel_init
extern exception_handler
extern mask_interrupt_handler
extern disp_str
extern kernel_main

extern g_gdt_ptr
extern g_idt_ptr
extern g_exited
extern g_proc_ready
extern g_tss
extern g_k_reenter
extern g_irq_table
extern g_syscall_table

[SECTION .data]
clock_int_msg db  "^",0

[SECTION .bss]
StartSpace resb 2048
StackTop:

[section .text]
global _start

global  divide_error
global  single_step_exception
global  nmi
global  breakpoint_exception
global  overflow
global  bounds_check
global  inval_opcode
global  copr_not_available
global  double_fault
global  copr_seg_overrun
global  inval_tss
global  segment_not_present
global  stack_exception
global  general_protection
global  page_fault
global  copr_error

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

global syscall

global restart

; The entry of kernel
_start:
    ; prepare kernel stack
    mov esp, StackTop

    ; store GDT
    sgdt [g_gdt_ptr]

    ; prepare new GDT
    ; prepare protect mod
    call kernel_init

    ; load gdt and idt(interrupt descriptor table)
    lgdt [g_gdt_ptr]
    lidt [g_idt_ptr]

    ; load tss
    xor eax, eax
    mov ax, SELECTOR_TSS
    ltr ax
    
    ; init process table
    jmp kernel_main

; return from irq, 
; if irq is reeneter one, recover the previous irq
; otherwise, recover the process
restart:
    mov esp, [g_proc_ready]
    lldt [esp + P_LDT_SEL]
    lea eax, [esp + P_STACKTOP]
    mov dword [g_tss + TSS3_S_SP0], eax
restart_reenter:
    dec dword [g_k_reenter]
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 4

    iretd

; interrupt occur, save the reg;
; if this irq is the only one, which means
; esp point to process stackframe(not process's stack)
; we need switch to kernel stack
; otherwise, this irq may interrupt other irq,
; stack here is just the kernel stack
save:
	pushad
    push ds
    push es
    push fs
    push gs
    mov dx, ss
    mov ds, dx
    mov es, dx

	mov esi, esp
    
    ;Judge reenter or not
    inc dword [g_k_reenter]
    cmp dword [g_k_reenter], 0
    jne .reenter
    
    ;switch to kernel stack
    mov esp, StackTop
	push restart
	jmp [esi+RETADR-P_STACKBASE]
.reenter:
	push restart_reenter
	jmp [esi+RETADR-P_STACKBASE]


%macro  mask_int_func_master    1
		call save ; save reg 

		in al, INT_M_CTLMASK
		or al, (1<<%1)
		out INT_M_CTLMASK, al; disable this irq
		mov al, EOI
		out INT_M_CTL, al

		sti ; enable other irq

        push    %1
        call    [g_irq_table + 4 * %1]
		pop ecx

		cli ; disable all irq

		in al, INT_M_CTLMASK
		and al, ~(1<<%1)
		out INT_M_CTLMASK, al; enable this irq
		ret ; jmp to restart or restart_reenter
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
        



divide_error:
    push    0xFFFFFFFF  ; no err code
    push    0       ; vector_no = 0
    jmp exception
single_step_exception:
    push    0xFFFFFFFF  ; no err code
    push    1       ; vector_no = 1
    jmp exception
nmi:
    push    0xFFFFFFFF  ; no err code
    push    2       ; vector_no = 2
    jmp exception
breakpoint_exception:
    push    0xFFFFFFFF  ; no err code
    push    3       ; vector_no = 3
    jmp exception
overflow:
    push    0xFFFFFFFF  ; no err code
    push    4       ; vector_no = 4
    jmp exception
bounds_check:
    push    0xFFFFFFFF  ; no err code
    push    5       ; vector_no = 5
    jmp exception
inval_opcode:
    push    0xFFFFFFFF  ; no err code
    push    6       ; vector_no = 6
    jmp exception
copr_not_available:
    push    0xFFFFFFFF  ; no err code
    push    7       ; vector_no = 7
    jmp exception
double_fault:
    push    8       ; vector_no = 8
    jmp exception
copr_seg_overrun:
    push    0xFFFFFFFF  ; no err code
    push    9       ; vector_no = 9
    jmp exception
inval_tss:
    push    10      ; vector_no = A
    jmp exception
segment_not_present:
    push    11      ; vector_no = B
    jmp exception
stack_exception:
    push    12      ; vector_no = C
    jmp exception
general_protection:
    push    13      ; vector_no = D
    jmp exception
page_fault:
    push    14      ; vector_no = E
    jmp exception
copr_error:
    push    0xFFFFFFFF  ; no err code
    push    16      ; vector_no = 10h
    jmp exception

exception:
    call    exception_handler
    add esp, 4*2    
    iretd

;------------------------------------------
syscall:
	call save ; save reg 
	sti ; enable other irq

	call    [g_syscall_table + 4 * eax]
	mov  [esi + EAXREG - P_STACKBASE], eax ; eax store return value of call

	cli ; disable all irq

	ret ; jmp to restart or restart_reenter

global sys_test_inc
sys_test_inc:
	mov eax, 0
	int 0x80
	ret

global sys_test_dec
sys_test_dec:
	mov eax, 1
	int 0x80
	ret

global get_ticks
get_ticks:
	mov eax, 2
	int 0x80
	ret

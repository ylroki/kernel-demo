#include "pub.h"
#include "string.h"
#include "global.h"


typedef void (*int_handler)();

/* exception function */
void	divide_error();
void	single_step_exception();
void	nmi();
void	breakpoint_exception();
void	overflow();
void	bounds_check();
void	inval_opcode();
void	copr_not_available();
void	double_fault();
void	copr_seg_overrun();
void	inval_tss();
void	segment_not_present();
void	stack_exception();
void	general_protection();
void	page_fault();
void	copr_error();

void mask_int_func0();
void mask_int_func1();
void mask_int_func2();
void mask_int_func3();
void mask_int_func4();
void mask_int_func5();
void mask_int_func6();
void mask_int_func7();
void mask_int_func8();
void mask_int_func9();
void mask_int_func10();
void mask_int_func11();
void mask_int_func12();
void mask_int_func13();
void mask_int_func14();
void mask_int_func15();

void clear_some_lines()
{
	disp_pos = 0;
	int i;
	for (i = 0; i < 80 * 5; ++i)
	{
		disp_str(" ");
	}
	disp_pos = 0;
}

void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags)
{
	char* err_msg[] =
	{
		"Divide Error",
		"Single Step Exception",
		"NMI Interrupt",
		"Breakpoint",
		"Overflow",
		"Bound Range Exceeded",
		"Undefined Opcode",
		"Device Not Available",
		"Double Fault",
		"Segment Overrun",
		"Invalid TSS",
		"Segment Not Present",
		"Stack Exception",
		"General Protection",
		"Page Fault",
		"Intel Reserved",
		"Floating Point Error",
		"Alignment Check",
		"Machine Check",
		"Floating Point Exception"
	};

	clear_some_lines();	
	disp_str("Exception: ");
	disp_str(err_msg[vec_no]);
	disp_str("\n");
	disp_str("CS: ");
	disp_int(cs);
	disp_str(" IP: ");
	disp_int(eip);
	disp_str(" Error code: ");
	disp_int(err_code);
	disp_str(" Flags: ");
	disp_int(eflags);
	disp_str("\n");

	return;
}

void mask_interrupt_handler(int irq)
{
	char str[2] = {0};
	char quit_str[] = "OS QUIT";
	str[0] = irq + 'A';

	clear_some_lines();
	disp_str("IRQ: ");
	disp_int(irq);
	disp_str("\n");
	if (1 == irq)
	{
		g_exited = 1;
		disp_str(quit_str);
	}

}

void init_8259A()
{
	out_byte(INT_M_CTL, 0x11);
	out_byte(INT_S_CTL, 0x11);
	out_byte(INT_M_CTLMASK, INT_VECTOR_IRQ0);
	out_byte(INT_S_CTLMASK, INT_VECTOR_IRQ8);
	out_byte(INT_M_CTLMASK, 0x4);
	out_byte(INT_S_CTLMASK, 0x2);
	out_byte(INT_M_CTLMASK, 0x1);
	out_byte(INT_S_CTLMASK, 0x1);
	/* open clock and keyboard interrupt*/
	out_byte(INT_M_CTLMASK, 0xFE);
	out_byte(INT_S_CTLMASK, 0xFF);
}

void init_idt_desc(unsigned char vector, uint8_t desc_type,
		int_handler handler, unsigned char privilege)
{
	gate_t * p_gate = &g_idt[vector];
	uint32_t base = (uint32_t)handler;
	p_gate->offset_low = base & 0xFFFF;
	p_gate->selector = SELECTOR_KERNEL_CS;
	p_gate->dcount = 0;
	p_gate->attr = desc_type | (privilege<<5);
	p_gate->offset_high = (base>>16) & 0xFFFF;
}



void init_exception()
{
	/* 异常中断*/
	init_idt_desc(INT_VECTOR_DIVIDE,	DA_386IGate,
		      divide_error,		PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_DEBUG,		DA_386IGate,
		      single_step_exception,	PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_NMI,		DA_386IGate,
		      nmi,			PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_BREAKPOINT,	DA_386IGate,
		      breakpoint_exception,	PRIVILEGE_USER);

	init_idt_desc(INT_VECTOR_OVERFLOW,	DA_386IGate,
		      overflow,			PRIVILEGE_USER);

	init_idt_desc(INT_VECTOR_BOUNDS,	DA_386IGate,
		      bounds_check,		PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_INVAL_OP,	DA_386IGate,
		      inval_opcode,		PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_COPROC_NOT,	DA_386IGate,
		      copr_not_available,	PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_DOUBLE_FAULT,	DA_386IGate,
		      double_fault,		PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_COPROC_SEG,	DA_386IGate,
		      copr_seg_overrun,		PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_INVAL_TSS,	DA_386IGate,
		      inval_tss,		PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_SEG_NOT,	DA_386IGate,
		      segment_not_present,	PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_STACK_FAULT,	DA_386IGate,
		      stack_exception,		PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_PROTECTION,	DA_386IGate,
		      general_protection,	PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_PAGE_FAULT,	DA_386IGate,
		      page_fault,		PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_COPROC_ERR,	DA_386IGate,
		      copr_error,		PRIVILEGE_KRNL);
}

void init_mask_interrupt()
{
	/* master*/
	init_idt_desc(INT_VECTOR_IRQ0 + 0, DA_386IGate,
			mask_int_func0, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ0 + 1, DA_386IGate,
			mask_int_func1, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ0 + 2, DA_386IGate,
			mask_int_func2, PRIVILEGE_KRNL);
			
	init_idt_desc(INT_VECTOR_IRQ0 + 3, DA_386IGate,
			mask_int_func3, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ0 + 4, DA_386IGate,
			mask_int_func4, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ0 + 5, DA_386IGate,
			mask_int_func5, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ0 + 6, DA_386IGate,
			mask_int_func6, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ0 + 7, DA_386IGate,
			mask_int_func7, PRIVILEGE_KRNL);

	/* slave*/
	init_idt_desc(INT_VECTOR_IRQ8 + 0, DA_386IGate,
			mask_int_func0, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ8 + 1, DA_386IGate,
			mask_int_func1, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ8 + 2, DA_386IGate,
			mask_int_func2, PRIVILEGE_KRNL);
			
	init_idt_desc(INT_VECTOR_IRQ8 + 3, DA_386IGate,
			mask_int_func3, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ8 + 4, DA_386IGate,
			mask_int_func4, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ8 + 5, DA_386IGate,
			mask_int_func5, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ8 + 6, DA_386IGate,
			mask_int_func6, PRIVILEGE_KRNL);

	init_idt_desc(INT_VECTOR_IRQ8 + 7, DA_386IGate,
			mask_int_func7, PRIVILEGE_KRNL);


}

uint32_t seg2phys(uint16_t seg)
{
	descriptor_t* p_dest = &g_gdt[seg >> 3];
	return (p_dest->base_high<<24 | p_dest->base_mid<<16 | p_dest->base_low);
}

void init_descriptor(descriptor_t *p_desc,uint32_t base,uint32_t limit,uint16_t attribute)
{
	p_desc->limit_low	= limit & 0x0FFFF;
	p_desc->base_low	= base & 0x0FFFF;
	p_desc->base_mid	= (base >> 16) & 0x0FF;
	p_desc->attr1		= attribute & 0xFF;
	p_desc->limit_high_attr2= ((limit>>16) & 0x0F) | (attribute>>8) & 0xF0;
	p_desc->base_high	= (base >> 24) & 0x0FF;
}

void init_protect_mode()
{
	init_8259A();

	init_exception();

	init_mask_interrupt();

	memset(&g_tss, 0, sizeof(g_tss));
	g_tss.ss0 = SELECTOR_KERNEL_DS;
	init_descriptor(&g_gdt[INDEX_TSS],
			vir2phys(seg2phys(SELECTOR_KERNEL_DS), &g_tss),
			sizeof(g_tss) - 1,
			DA_386TSS);
	g_tss.iobase = sizeof(g_tss); /* 没有I/O许可位图 */

	/* 填充 GDT 中进程的 LDT 的描述符 */
	int idx = 0;
	for (idx = 0; idx < PROC_MAX; ++idx)
	{
		init_descriptor(&g_gdt[INDEX_LDT_FIRST + idx<<3],
			vir2phys(seg2phys(SELECTOR_KERNEL_DS), g_proc_table[idx].ldts),
			LDT_SIZE * sizeof(descriptor_t) - 1,
			DA_LDT);
	}
}



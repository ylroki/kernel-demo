#include "pub.h"

/*********************************/

/*global var*/
uint8_t g_gdt_ptr[6];
descriptor_t g_gdt[GDT_SIZE];

uint8_t g_idt_ptr[6];
gate_t g_idt[IDT_SIZE];
irq_handler g_irq_table[IRQ_MAX];

void sys_test_inc_handler();
void sys_test_dec_handler();
uint32_t sys_get_ticks_handler();
int g_test_val = 0;
syscall_handler g_syscall_table[SYSCALL_MAX] = 
{
	sys_test_inc_handler,
	sys_test_dec_handler,
	sys_get_ticks_handler
};

tss_t g_tss;

int g_k_reenter;
uint32_t g_ticks;

/*******************************/


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

    clear_some_lines(0, PROTECT_DISPLAY_LINE_END); 
	uint32_t pos = 0;
	
    pos = disp_str("Exception: ", pos);
    pos = disp_str(err_msg[vec_no], pos);
    pos = disp_str("\n", pos);
    pos = disp_str("CS: ", pos);
    pos = disp_hex(cs, pos);
    pos = disp_str(" IP: ", pos);
    pos = disp_hex(eip, pos);
    pos = disp_str(" Error code: ", pos);
    pos = disp_hex(err_code, pos);
    pos = disp_str(" Flags: ", pos);
    pos = disp_hex(eflags, pos);
    pos = disp_str("\n", pos);
	while(1){}

    return;
}

void mask_interrupt_handler(uint32_t irq)
{
    clear_some_lines(0, PROTECT_DISPLAY_LINE_END);

	uint32_t pos = 0;
    pos = disp_str("IRQ: ", pos);
    pos = disp_int(irq, pos);
    pos = disp_str("\n", pos);
}

void clock_init()
{
        disp_str("init clock", 2 * disp_pos_per_line);
	g_ticks = 0;

	/* init 8253 chip*/
	out_byte(0x43, 0x34);/* 8253 mode control 0x34 = 00110100*/
	uint32_t count = 1193182/CLOCK_HZ;/* set clock irq frequence 1000HZ*/
	out_byte(0x40, (uint8_t)(count&0xff));
	out_byte(0x40, (uint8_t)(count>>8));

	/* active clock irq*/
	set_irq_handler(0, clock_handler);
	enable_irq(0);
}

void clock_handler(uint32_t irq)
{
	++g_ticks;
	uint32_t pos = PROTECT_DISPLAY_LINE_END*disp_pos_per_line+120; 
	pos = disp_str("tick: ", pos);
	pos = disp_int(g_ticks, pos);
	if (g_k_reenter != 0)
	{
		return;
	}

	kernel_schedule();
}

void sys_test_inc_handler()
{
	int tmp = g_test_val;
	++tmp;
	g_test_val = tmp;
}

void sys_test_dec_handler()
{
	int tmp = g_test_val;
	--tmp;
	g_test_val = tmp;
}

uint32_t sys_get_ticks_handler()
{
	return g_ticks;	
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
    out_byte(INT_M_CTLMASK, 0xFF);
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
    init_idt_desc(INT_VECTOR_DIVIDE,    DA_386IGate,
              divide_error,     PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_DEBUG,     DA_386IGate,
              single_step_exception,    PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_NMI,       DA_386IGate,
              nmi,          PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_BREAKPOINT,    DA_386IGate,
              breakpoint_exception, PRIVILEGE_USER);

    init_idt_desc(INT_VECTOR_OVERFLOW,  DA_386IGate,
              overflow,         PRIVILEGE_USER);

    init_idt_desc(INT_VECTOR_BOUNDS,    DA_386IGate,
              bounds_check,     PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_INVAL_OP,  DA_386IGate,
              inval_opcode,     PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_COPROC_NOT,    DA_386IGate,
              copr_not_available,   PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_DOUBLE_FAULT,  DA_386IGate,
              double_fault,     PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_COPROC_SEG,    DA_386IGate,
              copr_seg_overrun,     PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_INVAL_TSS, DA_386IGate,
              inval_tss,        PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_SEG_NOT,   DA_386IGate,
              segment_not_present,  PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_STACK_FAULT,   DA_386IGate,
              stack_exception,      PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_PROTECTION,    DA_386IGate,
              general_protection,   PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_PAGE_FAULT,    DA_386IGate,
              page_fault,       PRIVILEGE_KRNL);

    init_idt_desc(INT_VECTOR_COPROC_ERR,    DA_386IGate,
              copr_error,       PRIVILEGE_KRNL);
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

	uint32_t idx = 0;
	for (idx = 0; idx < IRQ_MAX; ++idx)
	{
		g_irq_table[idx] = mask_interrupt_handler;
	}
}

void enable_irq(uint32_t irq)
{
	if (irq < 8)	
	{
		out_byte(INT_M_CTLMASK, in_byte(INT_M_CTLMASK) & ~(1<<irq));
	}
	else
	{
		out_byte(INT_S_CTLMASK, in_byte(INT_S_CTLMASK) & ~(1<<irq));
	}
}

void disable_irq(uint32_t irq)
{
	if (irq < 8)	
	{
		out_byte(INT_M_CTLMASK, in_byte(INT_M_CTLMASK)|(1<<irq));
	}
	else
	{
		out_byte(INT_S_CTLMASK, in_byte(INT_S_CTLMASK)|(1<<irq));
	}
}

void set_irq_handler(uint32_t irq, irq_handler handler)
{
	disable_irq(irq);
	g_irq_table[irq] = handler;
}

uint32_t seg2phys(uint16_t seg)
{
    descriptor_t* p_dest = &g_gdt[seg >> 3];
    return (p_dest->base_high<<24 | p_dest->base_mid<<16 | p_dest->base_low);
}

void init_descriptor(descriptor_t *p_desc,uint32_t base,uint32_t limit,uint16_t attribute)
{
    p_desc->limit_low   = limit & 0x0FFFF;
    p_desc->base_low    = base & 0x0FFFF;
    p_desc->base_mid    = (base >> 16) & 0x0FF;
    p_desc->attr1       = attribute & 0xFF;
    p_desc->limit_high_attr2= ((limit>>16) & 0x0F) | (attribute>>8) & 0xF0;
    p_desc->base_high   = (base >> 24) & 0x0FF;
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
    g_tss.iobase = sizeof(g_tss); 

    /* init ldt  in gdt*/
    int idx = 0;
    for (idx = 0; idx < PROC_MAX; ++idx)
    {
        init_descriptor(&g_gdt[INDEX_LDT_FIRST + idx],
            vir2phys(seg2phys(SELECTOR_KERNEL_DS), g_proc_table[idx].ldts),
            LDT_SIZE * sizeof(descriptor_t) - 1,
            DA_LDT);
    }
}

void kernel_init()
{
    clear_some_lines(0, disp_line_limit);
    disp_str("kernel enter protect mode", 0*disp_pos_per_line);

    uint16_t* p_gdt_limit = (uint16_t*)(&g_gdt_ptr[0]);
    uint32_t* p_gdt_base = (uint32_t*)(&g_gdt_ptr[2]);
    uint16_t* p_idt_limit = (uint16_t*)(&g_idt_ptr[0]);
    uint32_t* p_idt_base = (uint32_t*)(&g_idt_ptr[2]);

    memcpy(g_gdt, (void*)(*p_gdt_base), *p_gdt_limit + 1);

    *p_gdt_base = (uint32_t)g_gdt;
    *p_gdt_limit = GDT_SIZE * sizeof(descriptor_t) - 1;
    *p_idt_base = (uint32_t)g_idt;
    *p_idt_limit = IDT_SIZE * sizeof(gate_t) - 1;

    init_protect_mode();

	/* init syscall*/
    init_idt_desc(INT_VECTOR_SYSCALL, DA_386IGate,
            syscall, PRIVILEGE_USER);

    return ;
}


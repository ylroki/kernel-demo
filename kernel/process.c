#include "pub.h"

/***********************************/
/* global var*/
void process_a();
void process_b();
void process_c();

proc_t* g_proc_ready;
proc_t g_proc_table[PROC_MAX];
proc_func g_func_table[PROC_MAX] = {process_a, process_b, process_c};

char g_task_stack[STACK_SIZE*PROC_MAX];

/************************************/
void init_process_table()
{
	proc_t* p_proc  = g_proc_table;
    
    int idx = 0;
    for (idx = 0; idx < PROC_MAX; ++idx)
    {
        p_proc = g_proc_table + idx;
        p_proc->ldt_sel = SELECTOR_LDT_FIRST + (idx<<3);
        memcpy(&p_proc->ldts[0], &g_gdt[SELECTOR_KERNEL_CS>>3], sizeof(descriptor_t));
        p_proc->ldts[0].attr1 = DA_C | PRIVILEGE_TASK << 5; /* change the DPL*/
        memcpy(&p_proc->ldts[1], &g_gdt[SELECTOR_KERNEL_DS>>3], sizeof(descriptor_t));
        p_proc->ldts[1].attr1 = DA_DRW | PRIVILEGE_TASK << 5;   /* change the DPL*/

        p_proc->regs.cs = (0 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.ds = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.es = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.fs = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.ss = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.gs = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | RPL_TASK;
        p_proc->regs.eip= (uint32_t)g_func_table[idx];
        p_proc->regs.esp= (uint32_t) g_task_stack + STACK_SIZE * idx;
        p_proc->regs.eflags = 0x1202;   /* IF=1, IOPL=1, bit 2 is always 1.*/
    }

    g_proc_ready = g_proc_table;

}

void run_first_process()
{
	g_k_reenter = 0;

	/* actibe clock irq*/
	set_irq_handler(0, clock_handler);
	enable_irq(0);

	init_process_table();

	restart();
}

void kernel_schedule()
{
    ++g_proc_ready;
    if (g_proc_ready >= g_proc_table + PROC_MAX)
        g_proc_ready = g_proc_table;
}


/**************************************/
void process_a()
{
    while (1)
    {
        disp_str("A");
        delay(1);
    }
}

void process_b()
{
    while (1)
    {
        disp_str("B");
        delay(1);
    }
}

void process_c()
{
    while (1)
    {
        disp_str("C");
        delay(1);
    }
}

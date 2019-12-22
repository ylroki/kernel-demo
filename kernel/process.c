#include "pub.h"

/***********************************/
/* global var*/
void process_keyboard();
void process_b();
void process_c();

proc_t* g_proc_ready;
proc_t g_proc_table[PROC_MAX];
proc_func g_func_table[PROC_MAX] = {process_keyboard, process_b, process_c};

char g_task_stack[STACK_SIZE*PROC_MAX];

/************************************/
void init_process_table()
{
    disp_str("run process...", 6 * disp_pos_per_line);
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

        p_proc->regs.cs = (0 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;/* this RPL is
				import when iretd*/
        p_proc->regs.ds = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.es = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.fs = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.ss = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        p_proc->regs.gs = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | RPL_TASK;
        p_proc->regs.eip= (uint32_t)g_func_table[idx];
        p_proc->regs.esp= (uint32_t) g_task_stack + STACK_SIZE * (idx+1);
        p_proc->regs.eflags = 0x1202;   /* IF=1, IOPL=1, bit 2 is always 1.*/
    }

    g_proc_ready = g_proc_table+1;

}

void run_first_process()
{
	g_k_reenter = 0;
	
	clock_init();

	/* actibe keyboard irq*/
	keyboard_irq_init();
	
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
void process_keyboard()
{
    int tick=0;
    while (1)
    {
		keyboard_read();
        disp_str("process a", 7 * disp_pos_per_line);
        //disp_str(g_string_tab[g_ticks%10], 7 * disp_pos_per_line + 20);
        disp_int(g_ticks, 7 * disp_pos_per_line + 20);
		delay_loop(1);
    }
}

void process_b()
{
    while (1)
    {
        disp_str("process b", 8 * disp_pos_per_line);
        //disp_str(g_string_tab[g_ticks%10], 8 * disp_pos_per_line + 20);
        disp_int(g_ticks, 8 * disp_pos_per_line + 20);
        delay_loop(1);
    }
}

void process_c()
{
    while (1)
    {
        disp_str("process c", 9 * disp_pos_per_line);
        //disp_str(g_string_tab[g_ticks%10], 9 * disp_pos_per_line + 20);
        disp_int(g_ticks, 9 * disp_pos_per_line + 20);

        delay_loop(1);
    }
}

#include "pub.h"
#include "proc.h"
#include "global.h"


uint8_t g_gdt_ptr[6];
descriptor_t g_gdt[GDT_SIZE];

uint8_t g_idt_ptr[6];
gate_t g_idt[IDT_SIZE];
irq_handler g_irq_table[IRQ_MAX];

uint8_t g_exited;

proc_t* g_proc_ready;
proc_t g_proc_table[PROC_MAX];

char g_task_stack[STACK_SIZE*PROC_MAX];

tss_t g_tss;

int g_k_reenter;

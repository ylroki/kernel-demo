#ifndef __INCLUDE_GLOBAL_H__
#define __INCLUDE_GLOBAL_H__
#include "pub.h"
#include "proc.h"


#define PROC_MAX 3
#define STACK_SIZE 1024 //stack for process
extern uint8_t g_gdt_ptr[6];
extern descriptor_t g_gdt[GDT_SIZE];

extern uint8_t g_idt_ptr[6];
extern gate_t g_idt[IDT_SIZE];

extern uint8_t g_exited;

extern proc_t* g_proc_ready;
extern proc_t g_proc_table[PROC_MAX];

extern char g_task_stack[STACK_SIZE*PROC_MAX];
extern tss_t g_tss;

extern int g_k_reenter;
#endif

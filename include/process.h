#ifndef __INCLUDE_PROCESS_H__
#define __INCLUDE_PROCESS_H__
#include "type.h"

#define LDT_SIZE 2 /* ldt used by each process*/
#define PROC_NAME_MAX 16

typedef struct stackframe_s
{
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t kernel_esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t retaddr;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
}stackframe_t;

typedef struct proc_s
{
    stackframe_t regs;
    uint16_t ldt_sel;
    descriptor_t ldts[LDT_SIZE];
    uint32_t pid;
    char proc_name[PROC_NAME_MAX];
}proc_t;


typedef void (*proc_func)();

#define PROC_MAX 3
#define STACK_SIZE 1024 
extern uint8_t g_exited;

extern proc_t* g_proc_ready;
extern proc_t g_proc_table[PROC_MAX];

extern char g_task_stack[STACK_SIZE*PROC_MAX];

extern void kernel_schedule();

#endif

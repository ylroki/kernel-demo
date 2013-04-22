#ifndef __INCLUDE_PROC_H__
#define __INCLUDE_PROC_H__
#include "pub.h"


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

#define PROC_NAME_MAX 16
typedef struct proc_s
{
    stackframe_t regs;
    uint16_t ldt_sel;
    descriptor_t ldts[LDT_SIZE];
    uint32_t pid;
    char proc_name[PROC_NAME_MAX];
}proc_t;


typedef void (*proc_func)();

#endif

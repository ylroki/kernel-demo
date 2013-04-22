#include "pub.h"
#include "string.h"
#include "global.h"

extern void init_protect_mode();

void cstart()
{
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

    g_exited = 0;
    
    disp_str("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nhello world\n");
    return ;
}


#include "pub.h"

void* memcpy(void* dst, void* src, int size);

uint8_t g_gdt_ptr[6];
descriptor_t g_gdt[GDT_SIZE];


void cstart()
{
	uint16_t* p_gdt_limit = (uint16_t*)(&g_gdt_ptr[0]);
	uint32_t* p_gdt_base = (uint32_t*)(&g_gdt_ptr[2]);

	memcpy(g_gdt, (void*)(*p_gdt_base), *p_gdt_limit + 1);

	*p_gdt_base = (uint32_t*)g_gdt;
	*p_gdt_limit = GDT_SIZE * sizeof(descriptor_t) - 1;
	return ;
}


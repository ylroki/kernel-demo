#ifndef __INCLUDE_PROTECT_H__
#define __INCLUDE_PROTECT_H__
#include "type.h"

/*
 * protect.h define some macro, struct for protect mode
 */

/* privilege */
#define PRIVILEGE_KRNL  0
#define PRIVILEGE_TASK  1
#define PRIVILEGE_USER  3

/* RPL */
#define RPL_KRNL    SA_RPL0
#define RPL_TASK    SA_RPL1
#define RPL_USER    SA_RPL3

#define INT_M_CTL 0x20
#define INT_M_CTLMASK 0x21
#define INT_S_CTL 0xA0
#define INT_S_CTLMASK 0xA1

#define INT_VECTOR_IRQ0 0x20
#define INT_VECTOR_IRQ8 0x28


/* attribute of selector*/
#define SA_RPL_MASK  0xfffc
#define SA_RPL0 0
#define SA_RPL1 1
#define SA_RPL2 2
#define SA_RPL3 3

#define SA_TI_MASK  0xfffb
#define SA_TIG 0
#define SA_TIL 4

/* attribute of descriptor*/
#define DA_32           0x4000  
#define DA_LIMIT_4K     0x8000  
#define DA_DPL0         0x00    /* DPL = 0              */
#define DA_DPL1         0x20    /* DPL = 1              */
#define DA_DPL2         0x40    /* DPL = 2              */
#define DA_DPL3         0x60    /* DPL = 3              */


/* type of descriptoe */
#define DA_DR           0x90    
#define DA_DRW          0x92    
#define DA_DRWA         0x93    
#define DA_C            0x98    
#define DA_CR           0x9A    
#define DA_CCO          0x9C    
#define DA_CCOR         0x9E    

#define DA_LDT          0x82    
#define DA_TaskGate     0x85    
#define DA_386TSS       0x89    
#define DA_386CGate     0x8C    
#define DA_386IGate     0x8E    
#define DA_386TGate     0x8F    

/* GDT */
/* index of descriptor */
#define INDEX_DUMMY     0   
#define INDEX_FLAT_C        1   
#define INDEX_FLAT_RW       2   
#define INDEX_VIDEO     3   
#define INDEX_TSS       4
#define INDEX_LDT_FIRST 5

/* selector */
#define SELECTOR_DUMMY         0        
#define SELECTOR_FLAT_C     0x08        
#define SELECTOR_FLAT_RW    0x10        
#define SELECTOR_VIDEO      (0x18+3)   /* RPL=3*/
#define SELECTOR_TSS        0x20
#define SELECTOR_LDT_FIRST      0x28


#define SELECTOR_KERNEL_CS  SELECTOR_FLAT_C
#define SELECTOR_KERNEL_DS  SELECTOR_FLAT_RW
#define SELECTOR_KERNEL_GS  SELECTOR_VIDEO



/* interrupt vector */
#define INT_VECTOR_DIVIDE       0x0
#define INT_VECTOR_DEBUG        0x1
#define INT_VECTOR_NMI          0x2
#define INT_VECTOR_BREAKPOINT       0x3
#define INT_VECTOR_OVERFLOW     0x4
#define INT_VECTOR_BOUNDS       0x5
#define INT_VECTOR_INVAL_OP     0x6
#define INT_VECTOR_COPROC_NOT       0x7
#define INT_VECTOR_DOUBLE_FAULT     0x8
#define INT_VECTOR_COPROC_SEG       0x9
#define INT_VECTOR_INVAL_TSS        0xA
#define INT_VECTOR_SEG_NOT      0xB
#define INT_VECTOR_STACK_FAULT      0xC
#define INT_VECTOR_PROTECTION       0xD
#define INT_VECTOR_PAGE_FAULT       0xE
#define INT_VECTOR_COPROC_ERR       0x10



/*linner addr to physical addr*/
#define vir2phys(seg_base, vir) (uint32_t)(((uint32_t)seg_base) + (uint32_t)(vir))

#define GDT_SIZE 128
#define IDT_SIZE 256
#define IRQ_MAX 16




/*************************************************/

/* struct*/

typedef struct descriptor_s
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t attr1;
    uint8_t limit_high_attr2;
    uint8_t base_high;
}descriptor_t;

typedef struct gate_s
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t dcount;
    uint8_t attr;
    uint16_t offset_high;
}gate_t;

typedef struct tss_s{
    uint32_t    backlink;
    uint32_t    esp0;   /* stack pointer to use during interrupt */
    uint32_t    ss0;    /*   "   segment  "  "    "        "     */
    uint32_t    esp1;
    uint32_t    ss1;
    uint32_t    esp2;
    uint32_t    ss2;
    uint32_t    cr3;
    uint32_t    eip;
    uint32_t    flags;
    uint32_t    eax;
    uint32_t    ecx;
    uint32_t    edx;
    uint32_t    ebx;
    uint32_t    esp;
    uint32_t    ebp;
    uint32_t    esi;
    uint32_t    edi;
    uint32_t    es;
    uint32_t    cs;
    uint32_t    ss;
    uint32_t    ds;
    uint32_t    fs;
    uint32_t    gs;
    uint32_t    ldt;
    uint16_t    trap;
    uint16_t    iobase; 
}tss_t;


typedef void (*irq_handler)(uint32_t);
typedef void (*int_handler)();


/*****************************************************/
/* declaration*/


extern uint8_t g_gdt_ptr[6];
extern descriptor_t g_gdt[GDT_SIZE];

extern uint8_t g_idt_ptr[6];
extern gate_t g_idt[IDT_SIZE];

extern irq_handler g_irq_table[IRQ_MAX];
extern tss_t g_tss;

extern int g_k_reenter;/*irq reenter flag*/


extern void clock_handler(uint32_t irq);
extern void enable_irq(uint32_t irq);
extern void set_irq_handler(uint32_t irq, irq_handler hander);


/* exception function */
void    divide_error();
void    single_step_exception();
void    nmi();
void    breakpoint_exception();
void    overflow();
void    bounds_check();
void    inval_opcode();
void    copr_not_available();
void    double_fault();
void    copr_seg_overrun();
void    inval_tss();
void    segment_not_present();
void    stack_exception();
void    general_protection();
void    page_fault();
void    copr_error();

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



#endif

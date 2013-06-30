#include "pub.h"

#define SCAN_CODE_ESC 0x01
#define SCAN_CODE_BS 0x0e
#define SCAN_CODE_TAB 0x0f
#define SCAN_CODE_CRLF 0x1c
#define SCAN_CODE_L_CTRL 0x1d
#define SCAN_CODE_L_SHIFT 0x2a
#define SCAN_CODE_R_SHIFT 0x36
#define SCAN_CODE_L_ALT 0x38
#define SCAN_CODE_CAPS_LOCK 0x3a
#define SCAN_CODE_F1 0x3b
#define SCAN_CODE_F2 0x3c
#define SCAN_CODE_F3 0x3d
#define SCAN_CODE_F4 0x3e
#define SCAN_CODE_F5 0x3f
#define SCAN_CODE_F6 0x40
#define SCAN_CODE_F7 0x41
#define SCAN_CODE_F8 0x42
#define SCAN_CODE_F9 0x43
#define SCAN_CODE_F10 0x44
#define SCAN_CODE_NUM_LOCK 0x45
#define SCAN_CODE_SCROLL_LOCK 0x46
#define SCAN_CODE_HOME 0x47
#define SCAN_CODE_UP 0x48
#define SCAN_CODE_PAGEUP 0x49
#define SCAN_CODE_PAD_MINUS 0x4a
#define SCAN_CODE_LEFT 0x4b
#define SCAN_CODE_MID 0x4c
#define SCAN_CODE_RIGHT 0x4d
#define SCAN_CODE_PAD_PLUS 0x4e
#define SCAN_CODE_END 0x4f
#define SCAN_CODE_DOWN 0x50
#define SCAN_CODE_PAGEDOWN 0x51
#define SCAN_CODE_INSERT 0x52
#define SCAN_CODE_DELETE 0x53
#define SCAN_CODE_ENTER 0x54

char *g_scan_code_map[]= 
{
	"none",
	"ESC",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"0",
	"-",
	"=",
	"bs", /* bs*/
	"tab", /* tab*/
	"q",
	"w",
	"e", 
	"r",
	"t",
	"y",
	"u",
	"i",
	"o",
	"p",
	"[",
	"]",
	"crlf", /**/
	"l ctrl", /*ctrl*/
	"a",
	"s",
	"d",
	"f",
	"g",
	"h",
	"j",
	"k",
	"l",
	";",
	"'",
	"`",
	"l shift", /*L shift*/
	"\\",
	"z",
	"x",
	"c",
	"v",
	"b",
	"n",
	"m",
	",",
	".",
	"/",
	"r shift", /*R shift*/
	"*", /*print screen*/
	"alt", /*alt*/
	" ", /*space*/
	"caps", /*caps*/
	"f1", /*f1*/
	"f2", /*f2*/
	"f3", /*f3*/
	"f4", /*f4*/
	"f5", /*f5*/
	"f6", /*f6*/
	"f7", /*f7*/
	"f8", /*f8*/
	"f9", /*f9*/
	"f10", /*f10*/
	"num", /*num*/
	"scroll", /*scroll*/
	"home", /*home*/
	"up", /*up*/
	"page up", /*page up*/
	"-", /*-*/
	"left", /*left*/
	"center", /*center*/
	"right", /*right*/
	"+", /*+*/
	"end", /*end*/
	"down", /*down*/
	"page down", /*page down*/
	"ins", /*ins*/
	"del", /*del*/
	"enter", /*0x54*/
	"none",
	"none",
	"f11",
	"f12",
	"none", /*0x59*/
	"none", /*0x5a*/
	"none", /*0x5b*/
	"none", /*0x5c*/
	"none", /*0x5d*/
	"none", /*0x5e*/
	"none", /*0x5f*/
	"none", /*0x60*/
	"none", /*0x61*/
	"none", /*0x62*/
	"none", /*0x63*/
	"none", /*0x64*/
	"none", /*0x65*/
	"none", /*0x66*/
	"none", /*0x67*/
	"none", /*0x68*/
	"none", /*0x69*/
	"none", /*0x6a*/
	"none", /*0x6b*/
	"none", /*0x6c*/
	"none", /*0x6d*/
	"none", /*0x6e*/
	"none", /*0x6f*/
	"none", /*0x70*/
	"none", /*0x71*/
	"none", /*0x72*/
	"none", /*0x73*/
	"none", /*0x74*/
	"none", /*0x75*/
	"none", /*0x76*/
	"none", /*0x77*/
	"none", /*0x78*/
	"none", /*0x79*/
	"none", /*0x7a*/
	"none", /*0x7b*/
	"none", /*0x7c*/
	"none", /*0x7d*/
	"none", /*0x7e*/
	"none" /*0x7f*/
};

char *g_scan_code_map_with_shift[]= 
{
	"none",
	"ESC",
	"!",
	"@",
	"#",
	"$",
	"%",
	"^",
	"&",
	"*",
	"(",
	")",
	"_",
	"+",
	"bs", /* bs*/
	"tab", /* tab*/
	"Q",
	"W",
	"E", 
	"R",
	"T",
	"Y",
	"U",
	"I",
	"O",
	"P",
	"{",
	"}",
	"crlf", /**/
	"l ctrl", /*ctrl*/
	"A",
	"S",
	"D",
	"F",
	"G",
	"H",
	"J",
	"K",
	"L",
	":",
	"\"",
	"~",
	"l shift", /*L shift*/
	"|",
	"Z",
	"X",
	"C",
	"V",
	"B",
	"N",
	"M",
	"<",
	">",
	"?",
	"r shift", /*R shift*/
	"*", /* pad **/
	"alt", /*alt*/
	" ", /*space*/
	"caps", /*caps*/
	"f1", /*f1*/
	"f2", /*f2*/
	"f3", /*f3*/
	"f4", /*f4*/
	"f5", /*f5*/
	"f6", /*f6*/
	"f7", /*f7*/
	"f8", /*f8*/
	"f9", /*f9*/
	"f10", /*f10*/
	"num", /*num*/
	"scroll", /*scroll*/
	"home", /*home*/
	"up", /*up*/
	"page up", /*page up*/
	"-", /*-*/
	"left", /*left*/
	"center", /*center*/
	"right", /*right*/
	"+", /*+*/
	"end", /*end*/
	"down", /*down*/
	"page down", /*page down*/
	"ins", /*ins*/
	"del", /*del*/
	"enter", /*0x54*/
	"none",
	"none",
	"f11",
	"f12",
	"none", /*0x59*/
	"none", /*0x5a*/
	"none", /*0x5b*/
	"none", /*0x5c*/
	"none", /*0x5d*/
	"none", /*0x5e*/
	"none", /*0x5f*/
	"none", /*0x60*/
	"none", /*0x61*/
	"none", /*0x62*/
	"none", /*0x63*/
	"none", /*0x64*/
	"none", /*0x65*/
	"none", /*0x66*/
	"none", /*0x67*/
	"none", /*0x68*/
	"none", /*0x69*/
	"none", /*0x6a*/
	"none", /*0x6b*/
	"none", /*0x6c*/
	"none", /*0x6d*/
	"none", /*0x6e*/
	"none", /*0x6f*/
	"none", /*0x70*/
	"none", /*0x71*/
	"none", /*0x72*/
	"none", /*0x73*/
	"none", /*0x74*/
	"none", /*0x75*/
	"none", /*0x76*/
	"none", /*0x77*/
	"none", /*0x78*/
	"none", /*0x79*/
	"none", /*0x7a*/
	"none", /*0x7b*/
	"none", /*0x7c*/
	"none", /*0x7d*/
	"none", /*0x7e*/
	"none" /*0x7f*/
};


char_queue_t g_keyboard_buf;

void keyboard_handler(uint32_t irq)
{
	uint8_t scan_code = in_byte(0x60);
	char_queue_push(&g_keyboard_buf, scan_code);
		
	if (g_k_reenter != 0)
	{
		return;
	}
}

void keyboard_irq_init()
{
	char_queue_init(&g_keyboard_buf);
	set_irq_handler(1, keyboard_handler);
	enable_irq(1);
}

void keyboard_read()
{
	uint8_t scan_code = 0;
	disable_interrupt();
	if (0 != char_queue_count(&g_keyboard_buf))
	{
		scan_code = char_queue_pop(&g_keyboard_buf);
		bool_t make_flag = (scan_code&0x80) == 0 ? 1 : 0;
		//disp_hex(scan_code);
		if (true == make_flag)
		{
			disp_str(g_scan_code_map[scan_code]);
		}
	}
	enable_interrupt();
}

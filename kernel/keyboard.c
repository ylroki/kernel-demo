#include "pub.h"

#define SCAN_CODE_ESC 0x01
#define SCAN_CODE_BS 0x0e
#define SCAN_CODE_TAB 0x0f
#define SCAN_CODE_CRLF 0x1c
#define SCAN_CODE_L_CTRL 0x1d
#define SCAN_CODE_L_SHIFT 0x2a
#define SCAN_CODE_R_SHIFT 0x36
#define SCAN_CODE_KP_MUL 0x37
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
#define SCAN_CODE_KP7 0x47
#define SCAN_CODE_UP 0x48
#define SCAN_CODE_KP8 0x48
#define SCAN_CODE_PAGEUP 0x49
#define SCAN_CODE_KP9 0x49
#define SCAN_CODE_KP_MINUS 0x4a
#define SCAN_CODE_LEFT 0x4b
#define SCAN_CODE_KP4 0x4b
#define SCAN_CODE_MID 0x4c
#define SCAN_CODE_KP5 0x4c
#define SCAN_CODE_RIGHT 0x4d
#define SCAN_CODE_KP6 0x4d
#define SCAN_CODE_KP_PLUS 0x4e
#define SCAN_CODE_END 0x4f
#define SCAN_CODE_KP1 0x4f
#define SCAN_CODE_DOWN 0x50
#define SCAN_CODE_KP2 0x50
#define SCAN_CODE_PAGEDOWN 0x51
#define SCAN_CODE_KP3 0x51
#define SCAN_CODE_INSERT 0x52
#define SCAN_CODE_KP0 0x52
#define SCAN_CODE_DELETE 0x53
#define SCAN_CODE_KP_DOT 0x53
#define SCAN_CODE_F11 0x57
#define SCAN_CODE_F12 0x58

#define KEY_PAD_START 0x47
#define KEY_PAD_END 0x53

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
	"*", /*kp **/
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
	"7", /*kp*/
	"8", /*kp*/
	"9", /*kp*/
	"-", /*-*/
	"4", /*kp*/
	"5", /*p*/
	"6", /*kp*/
	"+", /*+*/
	"1", /*kp*/
	"2", /*kp*/
	"3", /*kp*/
	"0", /*kp*/
	".", /*kp*/
	"none", /*0x54*/
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
	"f10", /*f10*/
	"num", /*num*/
	"scroll", /*scroll*/
	"7",/*kp*/ 
	"8", 
	"9", 
	"-", 
	"4", 
	"5", 
	"6", 
	"+", 
	"1", 
	"2", 
	"3", 
	"0", 
	".", /*kp*/
	"none", /*0x54*/
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
bool_t g_ctrl_pushed = false;
bool_t g_shift_pushed = false;
bool_t g_alt_pushed = false;
bool_t g_caps_enable = false;
bool_t g_num_enable = false;
bool_t g_scroll_enable = false;
uint32_t g_pos = 10*160;

uint8_t keyboard_buf_pop()
{
	while (0 == char_queue_count(&g_keyboard_buf))
	{
		delay_loop(1);
	}
	return char_queue_pop(&g_keyboard_buf);
}

void key_state_display(uint32_t line)
{
	uint32_t pos = line*disp_pos_per_line;

	pos = disp_str("ctr:", pos);
	pos = disp_int(g_ctrl_pushed, pos);
	pos = disp_str(" ", pos);

	pos = disp_str("shift:", pos);
	pos = disp_int(g_shift_pushed, pos);
	pos = disp_str(" ", pos);

	pos = disp_str("alt:", pos);
	pos = disp_int(g_alt_pushed, pos);
	pos = disp_str(" ", pos);

	pos = disp_str("caps:", pos);
	pos = disp_int(g_caps_enable, pos);
	pos = disp_str(" ", pos);

	pos = disp_str("num:", pos);
	pos = disp_int(g_num_enable, pos);
	pos = disp_str(" ", pos);

	pos = disp_str("scroll:", pos);
	pos = disp_int(g_scroll_enable, pos);
	pos = disp_str(" ", pos);
}

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
	disp_str("init keyboard", 3 * disp_pos_per_line);
	g_ctrl_pushed = false;
	g_shift_pushed = false;
	g_alt_pushed = false;
	g_caps_enable = false;
	g_num_enable = false;
	g_scroll_enable = false;
	char_queue_init(&g_keyboard_buf);
	set_irq_handler(1, keyboard_handler);
	enable_irq(1);
	key_state_display(4);
}

void single_scan_code_handle(uint8_t scan_code)
{
	/*
	 * single scan code:
	 * 		printable char: a-z 0-9 - = \ ` space ] ; , ' / [
	 *		special key: tab caps lshift lctrl lalt rshift crlf esc
	 *			f1-f12 scroll num backspace
	 *		key pad:  - . 0-9 * +
	 *
	 */
	bool_t make_flag = (scan_code&0x80) == 0 ? true : false;
	uint8_t key = (scan_code & 0x7f);
	switch (key)
	{
		case SCAN_CODE_BS:
			{
				if (false == make_flag)
					break;
				g_pos -= 2;
				if (g_pos < 0)
					g_pos = 0;
				g_pos = disp_str(" ", g_pos);
				g_pos -= 2;
				if (g_pos < 0)
					g_pos = 0;
				break;
			}
		case SCAN_CODE_ESC:
			{
				if (false == make_flag)
					break;
				g_pos = disp_str("esc", g_pos);
				break;
			}
		case SCAN_CODE_TAB:
			{
				if (false == make_flag)
					break;
				g_pos = disp_str("    ", g_pos);
				break;
			}
		case SCAN_CODE_CRLF:
			{
				if (false == make_flag)
					break;
				g_pos = disp_str("\n", g_pos);
				break;
			}
		case SCAN_CODE_L_CTRL:
			{
				g_ctrl_pushed = make_flag;
				break;
			}
		case SCAN_CODE_L_SHIFT:
		case SCAN_CODE_R_SHIFT:
			{
				g_shift_pushed = make_flag;
				break;
			}
		case SCAN_CODE_L_ALT:
			{
				g_alt_pushed = make_flag;
				break;
			}
		case SCAN_CODE_CAPS_LOCK:
			{
				if (false == make_flag)
					break;
				g_caps_enable = !g_caps_enable;
				break;
			}
		case SCAN_CODE_F1:
		case SCAN_CODE_F2:
		case SCAN_CODE_F3:
		case SCAN_CODE_F4:
		case SCAN_CODE_F5:
		case SCAN_CODE_F6:
		case SCAN_CODE_F7:
		case SCAN_CODE_F8:
		case SCAN_CODE_F9:
		case SCAN_CODE_F10:
		case SCAN_CODE_F11:
		case SCAN_CODE_F12:
			{
				if (false == make_flag)
					break;
				g_pos = disp_str("f?", g_pos);
				break;
			}
		case SCAN_CODE_NUM_LOCK:
			{
				if (false == make_flag)
					break;
				g_num_enable = !g_num_enable;
				break;
			}
		case SCAN_CODE_SCROLL_LOCK:
			{
				if (false == make_flag)
					break;
				g_scroll_enable = !g_scroll_enable;
				break;
			}
		default:
			{
				if (false == make_flag)
					break;
				if (((KEY_PAD_START <= key) && (KEY_PAD_END >= key))
					|| (SCAN_CODE_KP_MUL == key))
				{
					if (true == g_num_enable)
						g_pos = disp_str(g_scan_code_map[key], g_pos);
					else
						g_pos = disp_str("num lock", g_pos);
				}
				else
				{
					char ch = g_scan_code_map[key][0];
					if ('a' <= ch && 'z' >= ch)
					{
						if (g_shift_pushed == g_caps_enable)
							g_pos = disp_str(g_scan_code_map[key], g_pos);
						else
							g_pos = disp_str(g_scan_code_map_with_shift[key], g_pos);
					}
					else
					{
						if (false == g_shift_pushed)	
							g_pos = disp_str(g_scan_code_map[key], g_pos);
						else
							g_pos = disp_str(g_scan_code_map_with_shift[key], g_pos);
					}
				}
				break;
			}
	}
}

void E0_scan_code_handle(uint8_t scan_code)
{
	/* multiple scan code:
	 *		key pad enter {E0,1C} {E0,9C}
	 * 		rctrl {E0,1D} {E0,9D}
	 *		key pad / {E0,35}
	 * 		ralt {E0,38} {E0,B8}
	 *		home {E0,47} {E0,C7}
	 *		up {E0,48} {E0,C8}
	 *		page up {E0,49} {E0,C9}
	 *		left {E0,4B} {E0,CB}
	 *		right {E0,4D} {E0,CD}
	 *		end {E0,4F} {E0,CF}
	 *		down {E0,50} {E0,D0}
	 *		page down {E0,51} {E0,D1}
	 *		insert {E0,52} {E0,D2}
	 *		delete {E0,53} {E0,D3}
	 * 		lgui {E0,5B} {E0,DB}
	 * 		rgui {E0,5C} {E0,DC}
	 * 		apps {E0,5D} {E0,DD}
	 *		power {E0,5E} {E0,DE}
	 *		sleep {E0,5F} {E0,DF}
	 *		wake {E0,63} {E0,E3}
	 *		printscreen {E0,2A,E0,37} {E0,B7,E0,AA}
	 *		pause {E1,1D,45,E1,9D,C5} {}
	 *
	 */
	bool_t make_flag = (scan_code&0x80) == 0 ? true : false;
	uint8_t key = (scan_code & 0x7f);
	switch (scan_code)
	{
		case 0x2A:
		case 0xB7:
			{
				/* print screen*/
				g_pos = disp_hex(scan_code, g_pos);
				g_pos = disp_hex(keyboard_buf_pop(), g_pos);
				g_pos = disp_hex(keyboard_buf_pop(), g_pos);
				break;
			}
		case 0x1C:
		case 0x9C:
			{
				/* key pad enter {E0,1C} {E0,9C}*/
				if (false == make_flag)
					break;
				g_pos = disp_str("\n", g_pos);
				break;
			}
		case 0x1D:
		case 0x9D:
			{
				/* rctrl {E0,1D} {E0,9D}*/
				g_ctrl_pushed = make_flag;
				break;
			}
		case 0x35:
		case 0xB5:
			{
				/* key pad / {E0,35}*/
				if (false == make_flag)
					break;
				g_pos = disp_str("/", g_pos);
				break;
			}
		case 0x38:
		case 0xB8:
			{
				/* ralt {E0,38} {E0,B8}*/
				g_alt_pushed = make_flag;
				break;
			}
		case 0x47:
		case 0xC7:
			{
				/* home {E0,47} {E0,C7}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x48:
		case 0xC8:
			{
				/* up {E0,48} {E0,C8}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x49:
		case 0xC9:
			{
				/* page up {E0,49} {E0,C9}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x4B:
		case 0xCB:
			{
				/* left {E0,4B} {E0,CB}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x4D:
		case 0xCD:
			{
				/* right {E0,4D} {E0,CD}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x4F:
		case 0xCF:
			{
				/* end {E0,4F} {E0,CF}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x50:
		case 0xD0:
			{
				/* down {E0,50} {E0,D0}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x51:
		case 0xD1:
			{
				/* page down {E0,51} {E0,D1}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x52:
		case 0xD2:
			{
				/* insert {E0,52} {E0,D2}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x53:
		case 0xD3:
			{
				/* delete {E0,53} {E0,D3}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x5B:
		case 0xDB:
			{
				/* lgui {E0,5B} {E0,DB}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x5C:
		case 0xDC:
			{
				/* rgui {E0,5C} {E0,DC}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x5D:
		case 0xDD:
			{
				/* apps {E0,5D} {E0,DD}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x5E:
		case 0xDE:
			{
				/* power {E0,5E} {E0,DE}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x5F:
		case 0xDF:
			{
				/* sleep {E0,5F} {E0,DF}*/
				if (false == make_flag)
					break;
				break;
			}
		case 0x63:
		case 0xE3:
			{
				/* wake {E0,63} {E0,E3}*/
				if (false == make_flag)
					break;
				break;
			}
		default:
			{
				g_pos = disp_hex(scan_code, g_pos);
				break;
			}
	}
}


void keyboard_read()
{
	uint8_t scan_code = 0;
	//disable_interrupt();
	if (0 != char_queue_count(&g_keyboard_buf))
	{
		scan_code = char_queue_pop(&g_keyboard_buf);
		
		if (0xE0 == scan_code)
		{
			scan_code = keyboard_buf_pop();
			E0_scan_code_handle(scan_code);
		}
		else if (0xE1 == scan_code)
		{
			/* */
			for (int i=0; i<5; ++i)
			{
				g_pos = disp_hex(keyboard_buf_pop(), g_pos);
			}
		}
		else /* simple one scan code*/
		{
			single_scan_code_handle(scan_code);	
		}
	}
	key_state_display(4);
	//enable_interrupt();
}

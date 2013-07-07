#include "pub.h"


int kernel_main()
{
	clear_some_lines(PROTECT_DISPLAY_LINE_END, 
			disp_line_limit-PROTECT_DISPLAY_LINE_END);
	disp_pos = PROTECT_DISPLAY_LINE_END*disp_pos_per_line;
    disp_str("\n------\"kernel main begin\"------\n");

	g_test_val = 0;

	run_first_process();
	/* I don't know how to powoff...*/
    while(1){}
}


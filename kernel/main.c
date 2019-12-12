#include "pub.h"


int kernel_main()
{
    disp_str("kernel process 0", 1 * disp_pos_per_line);

	g_test_val = 0;

	run_first_process();
	/* I don't know how to powoff...*/
    while(1){}
}


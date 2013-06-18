#include "pub.h"


int kernel_main()
{
    disp_str("------\"kernel main begin\"------\n");

	g_test_val = 0;

	run_first_process();
	/* I don't know how to powoff...*/
    while(1){}
}


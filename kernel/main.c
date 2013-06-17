#include "pub.h"


int kernel_main()
{
    disp_str("------\"kernel main begin\"------\n");

	run_first_process();
	/* I don't know how to powoff...*/
    while(1){}
}


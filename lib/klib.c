#include "pub.h"
#include "string.h"


void reverse_string(char* string, int len)
{
	int i;
	char temp;
	for (i = 0; i < len / 2; ++i)
	{
		temp = string[i];
		string[i] = string[len - i - 1];
		string[len - i - 1] = temp;
	}
}

char* itoa(char* buffer, int number)
{
	bool_t ge_zero = true;
	int len = 0;
	int base = 16;
	if (0 > number)
	{
		ge_zero = false;
		number = -number;
	}
	
	while (0 != number)
	{
		buffer[len] = number % base;
		if (10 > buffer[len])
		{
			buffer[len] += '0';
		}
		else
		{
			buffer[len] += 'A' - 10;
		}
		++len;
		number /= base;
	}

	if (0 == len)
	{
		buffer[len] = '0';
		++len;
	}

	if (false == ge_zero)
	{
		buffer[len] = '-';
		++len;
	}

	reverse_string(buffer, len);
}

void disp_int(int number)
{
	char str[16] = {0};
	(void)itoa(str, number);
	disp_str(str);
}

#define DELAY_LOOP 1000000
void delay(int time)
{
	int i, j;
	for (i = 0; i < time; ++i)
		for (j = 0; j < DELAY_LOOP; ++j)
		{}
}

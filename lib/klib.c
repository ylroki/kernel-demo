#include "pub.h"


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

char* itoa(char* buffer, int number, int base)
{
    bool_t ge_zero = true;
    int len = 0;
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

	if (16 == base)
	{
		buffer[len++] = 'x';
		buffer[len++] = '0';
	}

    if (false == ge_zero)
    {
        buffer[len] = '-';
        ++len;
    }

    reverse_string(buffer, len);
	buffer[len] = 0;
}

uint32_t disp_int(int number, uint32_t pos)
{
    char str[16] = {0};
    (void)itoa(str, number, 10);
    return disp_str(str, pos);
}

uint32_t disp_hex(int number, uint32_t pos)
{
    char str[16] = {0};
    (void)itoa(str, number, 16);
    return disp_str(str, pos);
}

void clear_some_lines(uint32_t start, uint32_t cnt)
{
    int i = 0;

	if (disp_line_limit - start < cnt)
		cnt = disp_line_limit - start;

    uint32_t disp_pos = start*disp_pos_per_line;
    for (i = disp_pos; i < disp_pos_per_line * cnt; i+=2)
    {
        disp_str(" ", i);
    }
}

void delay(int time)
{
	/*
    uint32_t t = get_ticks();
	while (((get_ticks() - t)*1000/CLOCK_HZ) < time)
	{}
	*/
}

#define DELAY_LOOP 1000
void delay_loop(int time)
{
	int i,j;
	for (i = 0; i < time; ++i)
		for (j = 0; j < DELAY_LOOP; ++j)
		{}
}

/******************************/
void char_queue_init(char_queue_t* q)
{
	memset(q->buf, 0, sizeof(q->buf));
	q->head = 0;
	q->tail = 0;
}

uint32_t char_queue_count(char_queue_t* q)
{
	return (q->tail - q->head + CHAR_QUEUE_BUF_MAX)%CHAR_QUEUE_BUF_MAX;
}

void char_queue_push(char_queue_t* q, char c)
{
	q->buf[q->tail] = c;
	++q->tail;
	if (CHAR_QUEUE_BUF_MAX-1 == q->tail)
	{
		q->tail = 0;
	}
}

char char_queue_pop(char_queue_t* q)
{
	if (0 == char_queue_count(q))
	{
		return (char)0;
	}
	char c = q->buf[q->head];
	++q->head;
	if (CHAR_QUEUE_BUF_MAX-1 == q->head)
	{
		q->head = 0;
	}
	return c;
}

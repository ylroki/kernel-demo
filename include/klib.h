#ifndef __INCLUDE_KLIB_H__
#define __INCLUDE_KLIB_H__

#define CHAR_QUEUE_BUF_MAX 10
typedef struct char_queue
{
	char buf[CHAR_QUEUE_BUF_MAX];
	uint32_t head;
	uint32_t tail;
}char_queue_t;


extern void reverse_string(char* string, int len);
extern char* itoa(char* buffer, int number, int base);
extern void disp_int(int number);
extern void disp_hex(int number);
extern void delay(int time);

extern int disp_pos;
extern void* memcpy(void* dst, void* src, int size);
extern void disp_str(char* str);


#endif

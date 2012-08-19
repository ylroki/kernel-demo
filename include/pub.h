#ifndef _INLCUDE_PUB_H
#define _INLCUDE_PUB_H

#define GDT_SIZE 128

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


typedef struct descriptor_s
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t attr1;
	uint8_t limit_high_attr2;
	uint8_t base_high;
}descriptor_t;
#endif


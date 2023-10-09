#pragma once

#ifndef __EMUZ_H__
#define __EMUZ_H__

#define UINT8 unsigned char
#define INT8 signed char
#define UINT16 unsigned short
#define INT16 signed short
#define UINT32 unsigned int
#define INT32 int
//#define PAIR unsigned short
#define INLINE //__inline
#define TRUE 1
#define FALSE 0

extern char SZHVC_add_array [2*256*256];
extern char SZHVC_sub_array [2*256*256];

typedef union PAIR_u {
	struct { UINT8 l,h,h2,h3; } b;
	struct { UINT16 l,h; } w;
	struct { INT8 l,h,h2,h3; } sb;
	struct { INT16 l,h; } sw;
	UINT32 d;
	INT32 sd;
} PAIR;

UINT8 read_byte(UINT32 addr);
io_read_byte(int port);
io_write_byte(int port, int value);
program_write_byte(UINT32 addr, UINT8 value);
direct_read_decrypted_byte(int pc);
direct_read_raw_byte(int pc);
int __cdecl logerror (const char* s, ...);

#endif /* __EMUZ_H__ */

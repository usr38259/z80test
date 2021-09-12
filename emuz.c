
#include "emuz.h"

extern unsigned char mem [65536];

char SZHVC_add_array [2*256*256];
char SZHVC_sub_array [2*256*256];

UINT8 read_byte(UINT32 addr)
{
	return mem [addr & 0xffff];
}

io_read_byte(port)
{
	return 0;
}

io_write_byte(port, value)
{
	return 0;
}

program_write_byte(UINT32 addr, UINT8 value)
{
	mem [addr & 0xffff] = value;
}

direct_read_decrypted_byte(pc)
{
	return read_byte (pc);
}

direct_read_raw_byte(pc)
{
	return read_byte (pc);
}

int __cdecl logerror (const char* s, ...)
{
	return 0;
}

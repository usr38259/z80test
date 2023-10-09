
#include <stdio.h>
#ifdef __linux__
#include <sys/stat.h>
#endif

#include "z80.h"

#define TEXT_BIN "zexall.com"

#ifdef _WIN32
#ifndef _CRTAPI1
#define _CRTAPI1 __cdecl
#endif
#else
#define _CRTAPI1
#endif

z80_state	z80;
unsigned char mem [65536];

#ifdef __linux__
long file_length (FILE *f);
#define PUTCH putchar
#else
#define file_length(f) filelength(fileno(f))
#define PUTCH putch
#endif

int _CRTAPI1 main ()
{
	FILE *f;
	long fl;
	int i;

	z80_cpu_init (&z80);
	z80_cpu_reset (&z80);

	f = fopen (TEXT_BIN, "rb");
	if (f == NULL) {
		puts ("BIN file '" TEXT_BIN "' open error");
		return 1;
	}
	fl = file_length (f);
	if (fl <= 0 || fl > 49152) {
		puts ("File length error");
		fclose (f);
		return 1;
	}
	if (fread (mem + 0x100, fl, 1, f) != 1) {
		puts ("BIN file read error");
		fclose (f);
		return 1;
	}
	fclose (f);

	z80.sp.w.l = 0x7ffe;
	*(unsigned short*)&mem [0x06] = 0x7ffe;
	mem [0x05] = 0xC9;
	z80.pc.w.l = 0x100;

	while (1) {
		if (z80.pc.w.l == 0) break;
		if (z80.pc.w.l == 5) switch (z80.bc.b.l) {
		case 2: PUTCH (z80.de.b.l); break;
		case 9: for (i = z80.de.w.l; mem[i] != '$'; i ++) PUTCH (mem[i]);
			break;
		default: puts ("Unsupported BDOS call"); return 0;
		}
		z80_cpu_execute (&z80);
	}

	return 0;
}

#ifdef __linux__
long file_length (FILE *f)
{
	struct stat st;
	if (fstat (fileno (f), &st) != 0)
		return -1;
	return st.st_size;
}
#endif

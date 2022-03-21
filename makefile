
z80test.exe:
	cl /Ox z80test.c z80.c emuz.c

test: z80test.exe
	z80test.exe

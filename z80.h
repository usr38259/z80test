#pragma once

#ifndef __Z80_H__
#define __Z80_H__

#include "emuz.h"

enum
{
	Z80_PC, Z80_SP,
	Z80_A, Z80_B, Z80_C, Z80_D, Z80_E, Z80_H, Z80_L,
	Z80_AF, Z80_BC, Z80_DE, Z80_HL,
	Z80_IX, Z80_IY, Z80_AF2, Z80_BC2, Z80_DE2, Z80_HL2,
	Z80_R, Z80_I, Z80_IM, Z80_IFF1, Z80_IFF2, Z80_HALT,
	Z80_DC0, Z80_DC1, Z80_DC2, Z80_DC3, Z80_WZ,

//	Z80_GENPC = STATE_GENPC,
//	Z80_GENSP = STATE_GENSP,
//	Z80_GENPCBASE = STATE_GENPCBASE
};

typedef struct z80_state_t
{
	PAIR            prvpc,pc,sp,af,bc,de,hl,ix,iy,wz;
	PAIR            af2,bc2,de2,hl2;
	UINT8           r,r2,iff1,iff2,halt,im,i;
//	UINT8           nmi_state;          /* nmi line state */
//	UINT8           nmi_pending;        /* nmi pending */
//	UINT8           irq_state;          /* irq line state */
//	UINT8           nsc800_irq_state[4];/* state of NSC800 restart interrupts A, B, C */
//	int             wait_state;         // wait line state
//	int             busrq_state;        // bus request line state
	UINT8           after_ei;           /* are we in the EI shadow? */
	UINT8           after_ldair;        /* same, but for LD A,I or LD A,R */
	UINT32          ea;
//	device_irq_acknowledge_callback irq_callback;
//	legacy_cpu_device *device;
//	address_space *program;
//	direct_read_data *direct;
//	address_space *io;
	int             icount;
//	z80_daisy_chain daisy;
	UINT8           rtemp;
	const UINT8 *   cc_op;
	const UINT8 *   cc_cb;
	const UINT8 *   cc_ed;
	const UINT8 *   cc_xy;
	const UINT8 *   cc_xycb;
	const UINT8 *   cc_ex;
} z80_state;

z80_cpu_init(z80_state *z80);
z80_cpu_reset(z80_state *z80);
z80_cpu_execute(z80_state *z80);
z80_cpu_exit(z80_state *z80);
z80_dasm(z80_state *z80, char *buffer, unsigned char *opcode);

#define DASMFLAG_LENGTHMASK	0x0000ffff
#define DASMFLAG_SUPPORTED	0x80000000
#define DASMFLAG_STEP_OUT	0x40000000
#define DASMFLAG_STEP_OVER	0x20000000

#endif /* __Z80_H__ */

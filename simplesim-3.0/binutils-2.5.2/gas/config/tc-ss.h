/* tc-ss.h -- header file for tc-ss.c.
   Copyright (C) 1993 Free Software Foundation, Inc.
   Contributed by the OSF and Ralph Campbell.
   Written by Keith Knowles and Ralph Campbell, working independently.
   Modified for ECOFF support by Ian Lance Taylor of Cygnus Support.
   Hacked extensively by Todd Austin, University of Wisconsim

   This file is part of GAS.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to
   the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#define TC_SS

#define TARGET_ARCH bfd_arch_ss

#define ONLY_STANDARD_ESCAPES
#define BACKSLASH_V
#define WORKING_DOT_WORD	1
#define OLD_FLOAT_READS
#define REPEAT_CONS_EXPRESSIONS
#define RELOC_EXPANSION_POSSIBLE
#define MAX_RELOC_EXPANSION 3
#define LOCAL_LABELS_FB

/* The SS assembler appears to keep all symbols.  */
#define LOCAL_LABEL(name) 0

#define md_relax_frag(fragp, stretch)	(0)
#define md_undefined_symbol(name)	(0)
#define md_operand(x)

/* We permit PC relative difference expressions when generating
   embedded PIC code.  */
#define DIFF_EXPR_OK

#define LITTLE_ENDIAN   1234
#define BIG_ENDIAN      4321

/* If neither TARGET_BYTES_BIG_ENDIAN nor TARGET_BYTES_LITTLE_ENDIAN
   is specified, default to big endian.  */
#ifndef TARGET_BYTES_BIG_ENDIAN
#ifndef TARGET_BYTES_LITTLE_ENDIAN
#define TARGET_BYTES_BIG_ENDIAN
#endif
#endif

#ifdef TARGET_BYTES_BIG_ENDIAN
#define BYTE_ORDER	BIG_ENDIAN
#else
#define BYTE_ORDER      LITTLE_ENDIAN
#endif

/* The endianness of the target format may change based on command
   line arguments.  */
#define TARGET_FORMAT ss_target_format
extern const char *ss_target_format;

struct ss_cl_insn {
  struct _insn_opcode {
    unsigned long a;                  /* opcode */
    unsigned long b;                  /* arguments */
    } insn_opcode;
  const struct ss_opcode	*insn_mo;
};

extern int tc_get_register PARAMS ((int frame));

#define md_parse_long_option(arg) ss_parse_long_option (arg)
extern int ss_parse_long_option PARAMS ((const char *));

#define tc_frob_label(sym) ss_define_label (sym)
extern void ss_define_label PARAMS ((struct symbol *));

#define TC_CONS_FIX_NEW cons_fix_new_ss
extern void cons_fix_new_ss ();

/* When generating embedded PIC code we must keep PC relative
   relocations.  */
#define TC_FORCE_RELOCATION(fixp) ss_force_relocation (fixp)
extern int ss_force_relocation ();

/* md_apply_fix sets fx_done correctly.  */
#define TC_HANDLE_FX_DONE 1

/* Register mask variables.  These are set by the SS assembly code
   and used by ECOFF and possibly other object file formats.  */
extern unsigned long ss_gprmask;
extern unsigned long ss_cprmask[4];

#ifdef OBJ_ELF

#define elf_tc_final_processing ss_elf_final_processing
extern void ss_elf_final_processing PARAMS ((void));

#define ELF_TC_SPECIAL_SECTIONS \
  { ".sdata",	SHT_PROGBITS,	SHF_ALLOC + SHF_WRITE + SHF_MIPS_GPREL	}, \
  { ".sbss",	SHT_NOBITS,	SHF_ALLOC + SHF_WRITE + SHF_MIPS_GPREL	}, \
  { ".lit4",	SHT_PROGBITS,	SHF_ALLOC + SHF_WRITE + SHF_MIPS_GPREL	}, \
  { ".lit8",	SHT_PROGBITS,	SHF_ALLOC + SHF_WRITE + SHF_MIPS_GPREL	}, \
  { ".ucode",	SHT_MIPS_UCODE,	0					}, \
  { ".mdebug",	SHT_MIPS_DEBUG,	0					},
/* Other special sections not generated by the assembler: .reginfo,
   .liblist, .conflict, .gptab, .got, .dynamic, .rel.dyn.  */

#endif

extern void md_ss_end PARAMS ((void));
#define md_end()	md_ss_end()

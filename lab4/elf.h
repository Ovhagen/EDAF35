#ifndef elf_h
#define elf_h

#include <stdint.h>

#define ET_NONE			(0)
#define ET_REL			(1)
#define ET_EXEC			(2)
#define ET_DYN			(3)
#define ET_CORE			(4)
#define ET_TAC			(5)
#define ET_TAC_OPT		(6)
#define ET_CPU_OPT		(7)
#define ET_LOPROC		(0xff00)
#define ET_HIPROC		(0xffff)

#define EM_NONE			(0)
#define EM_SPARC		(2)
#define EM_PPC			(20)
#define EM_SPU			(23)

#define EV_NONE			(0)
#define EV_CURRENT		(1)

#define ELFCLASSNONE		(0)
#define ELFCLASS32		(1)
#define ELFCLASS64		(2)

#define ELFDATANONE		(0)
#define ELFDATA2LSB		(1)
#define ELFDATA2MSB		(2)

#define EI_MAG0			(0)
#define EI_MAG1			(1)
#define EI_MAG2			(2)
#define EI_MAG3			(3)
#define EI_CLASS		(4)
#define EI_DATA			(5)
#define EI_VERSION		(6)
#define EI_PAD			(7)
#define EI_NIDENT		(16)

#define SHN_UNDEF		(0)
#define SHN_LORESERVE		(0xff00)
#define SHN_LOPROC		(0xff00)
#define SHN_HIPROC		(0xff1f)
#define SHN_ABS			(0xfff1)
#define SHN_COMMON		(0xfff2)
#define SHN_GLOBAL_FRAME	(0xfff3)
#define SHN_HIRESERVE		(0xffff)

#define SHT_NULL		(0)
#define SHT_PROGBITS		(1)
#define SHT_SYMTAB		(2)
#define SHT_STRTAB		(3)
#define SHT_RELA		(4) 
#define SHT_HASH		(5)
#define SHT_DYNAMIC		(6)
#define SHT_NOTE		(7)
#define SHT_NOBITS		(8)
#define SHT_REL			(9)
#define SHT_SHLIB		(10)
#define SHT_DYNSYM		(11)
#define SHT_TAC			(12)
#define SHT_INIT_ARRAY		(14)
#define SHT_FINI_ARRAY		(15)
#define SHT_PREINIT_ARRAY	(16)
#define SHT_GROUP		(17)
#define SHT_SYMTAB_SHNDX	(18)

#define SHT_DEBUG_INFO		(13)
#define SHT_DEBUG_ABBREV	(14)
#define SHT_DEBUG_LINE		(15)
#define SHT_DEBUG_FRAME		(16)		/* MFD ??? wrong number?? */
#define SHT_DEBUG_LOC		(16)		/* MFD ??? wrong number?? */
#define SHT_LOPROC		(0x70000000)
#define SHT_HIPROC		(0x7fffffff)
#define SHT_LOUSER		(0x80000000)
#define SHT_HIUSER		(0xffffffff)

#define SHF_WRITE		(1<<0)
#define SHF_ALLOC		(1<<1)
#define SHF_EXECINSTR		(1<<2)
#define SHF_TLS			(1<<10)
#define SHF_MASKPROC		(0xf0000000)

#define STB_LOCAL		(0)
#define STB_GLOBAL		(1)
#define STB_WEAK		(2)

#define STT_NOTYPE		(0)
#define STT_OBJECT		(1)
#define STT_FUNC		(2)
#define STT_SECTION		(3)
#define STT_FILE		(4)
#define STT_TLS			(6)
#define STT_LOPROC		(13)
#define STT_HIPROC		(15)
#define STT_STAB		(13)

#define STN_UNDEF		(0)

#define ELF32_ST_BIND(i)	((i)>>4)
#define ELF32_ST_TYPE(i)	((i)&0xf)
#define ELF32_ST_INFO(b, t)	(((b)<<4)+((t)&0xf))

#define R_MACHINE_NONE		(0)
#define R_MACHINE_8		(1)
#define R_MACHINE_16		(2)
#define R_MACHINE_32		(3)
#define R_MACHINE_DISP8		(4)
#define R_MACHINE_DISP16	(5)
#define R_MACHINE_DISP32	(6)
#define R_MACHINE_WDISP16	(7)
#define R_MACHINE_WDISP26	(8)
#define R_MACHINE_LO16		(9)
#define R_MACHINE_HI16		(10)

#define ELF32_R_SYM(i)		((i)>>8)
#define ELF32_R_TYPE(i)		((unsigned char)(i))
#define ELF32_R_INFO(s, t)	(((s)<<8)+(unsigned char)(t))

#define PT_NULL			(0)
#define PT_LOAD			(1)
#define PT_DYNAMIC		(2)
#define PT_INTERP		(3)
#define PT_NOTE			(4)
#define PT_SHLIB		(5)
#define PT_PHDR			(6)
#define PT_TLS			(7)
#define PT_LOPROC		(0x70000000)
#define PT_HIPROC		(0x7fffffff)

#define PF_X			(0x1)
#define PF_W			(0x2)
#define PF_R			(0x4)
#define PF_MASKPROC		(0xf0000000)

#define DT_NULL			(0)
#define DT_NEEDED		(1)
#define DT_PLTRELSZ		(2)
#define DT_PLTGOT		(3)
#define DT_HASH			(4)
#define DT_STRTAB		(5)
#define DT_SYMTAB		(6)
#define DT_RELA			(7)
#define DT_RELASZ		(8)
#define DT_RELAENT		(9)
#define DT_STRSZ		(10)
#define DT_SYMENT		(11)
#define DT_INIT			(12)
#define DT_FINI			(13)
#define DT_SONAME		(14)
#define DT_RPATH		(15)
#define DT_SYMBOLIC		(16)
#define DT_REL			(17)
#define DT_RELSZ		(18)
#define DT_RELENT		(19)
#define DT_PLTREL		(20)
#define DT_DEBUG		(21)
#define DT_TEXTREL		(22)
#define DT_JMPREL		(23)
#define DT_LOPROC		(0x70000000)
#define DT_HIPROC		(0x7fffffff)

#define EF_MACHINE_FLAGS	(0)

#define ARMAG			"!<arch>\n"
#define SARMAG			(8)
#define ARFMAG			"`\n"

typedef uint32_t		Elf32_Addr;
typedef	uint16_t		Elf32_Half;
typedef uint32_t		Elf32_Off;
typedef int32_t			Elf32_Sword;
typedef uint32_t		Elf32_Word;
typedef uint64_t		Elf32_Xword;
typedef int64_t			Elf32_Sxword;
typedef struct Elf32_Ehdr	Elf32_Ehdr;
typedef struct Elf32_Shdr 	Elf32_Shdr;
typedef struct Elf32_Sym 	Elf32_Sym;
typedef struct Elf32_Rel 	Elf32_Rel;
typedef struct Elf32_Rela 	Elf32_Rela;
typedef struct Elf32_Phdr 	Elf32_Phdr;
typedef struct Elf32_Tac 	Elf32_Tac;
typedef struct Elf32_Tac_Op 	Elf32_Tac_Op;
typedef Elf32_Word		word_t;
typedef Elf32_Ehdr		ehdr_t;
typedef Elf32_Phdr		phdr_t;
typedef Elf32_Shdr 		shdr_t;
typedef Elf32_Rela 		rela_t;
typedef Elf32_Sym 		esym_t;
typedef Elf32_Tac_Op 		tac_op_t;

typedef struct ar_hdr 		ar_hdr;

struct Elf32_Ehdr {
	unsigned char		e_ident[EI_NIDENT];
	Elf32_Half		e_type;
	Elf32_Half		e_machine;
	Elf32_Word		e_version;
	Elf32_Addr		e_entry;
	Elf32_Off		e_phoff;
	Elf32_Off		e_shoff;
	Elf32_Word		e_flags;
	Elf32_Half		e_ehsize;
	Elf32_Half		e_phentsize;
	Elf32_Half		e_phnum;
	Elf32_Half		e_shentsize;
	Elf32_Half		e_shnum;
	Elf32_Half		e_shstrndx;
};

struct Elf32_Shdr {
	Elf32_Word		sh_name;
	Elf32_Word		sh_type;
	Elf32_Word		sh_flags;
	Elf32_Addr		sh_addr;
	Elf32_Off		sh_offset;
	Elf32_Word		sh_size;
	Elf32_Word		sh_link;
	Elf32_Word		sh_info;
	Elf32_Word		sh_addralign;
	Elf32_Word		sh_entsize;
};

struct Elf32_Sym {
	Elf32_Word		st_name;
	Elf32_Addr		st_value;
	Elf32_Word		st_size;
	unsigned char		st_info;
	unsigned char		st_other;
	Elf32_Half		st_shndx;
};

struct Elf32_Rel {
	Elf32_Addr		r_offset;
	Elf32_Word		r_info;
};

struct Elf32_Rela {
	Elf32_Addr		r_offset;
	Elf32_Word		r_info;
	Elf32_Sword		r_addend;
};

struct Elf32_Phdr {
	Elf32_Word		p_type;
	Elf32_Off		p_offset;
	Elf32_Addr		p_vaddr;
	Elf32_Addr		p_paddr;
	Elf32_Word		p_filesz;
	Elf32_Word		p_memsz;
	Elf32_Word		p_flags;
	Elf32_Word		p_align;
};

struct ar_hdr {
        char            	ar_name[16];
        char            	ar_date[12];
        char            	ar_uid[6];
        char            	ar_gid[6];
        char            	ar_mode[8];
        char            	ar_size[10];
        char            	ar_fmag[2];
};

#endif

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "elf.h"
#include "primary.h"
#include "extended.h"
#include "instr_table.h"

#define MAX_DENOMINATOR	100
#define xstr(s)		#s
#define str(s)		xstr(s)

#if 1
#define pr(...) fprintf(stderr, __VA_ARGS__)
#else
#define pr(...)
#endif

char*			progname;
unsigned long long	hist[MAX_DENOMINATOR+1];

static primary_opcode_t instr_primary(uint32_t instr)
{
	/* extract leftmost 6 bits. */
	return (instr >> 26) & 0x3f;
}

static uint32_t instr_field(uint32_t instr, unsigned pos, unsigned num)
{
	/* extract num bits starting with pos counted from the left. */
	return (instr >> (32-pos-num)) & ((1<<num)-1);
}

static size_t rewrite_instr(pid_t child, uint32_t start, size_t size, instr_table_t* table)
{
	uint32_t	end;		/* after last instr addr. */
	uint32_t	addr;		/* an instr addr. */
	uint32_t	instr;		/* a Power instr. */
	size_t		n;		/* number of rewrites. */

	end = start + size;
	n = 0;

	for (addr = start; addr < end; addr += sizeof instr) {

		errno = 0;
		instr = 0;

		/* Here you should read instr at addr in memory of tracee.
		 *
		 * instr = ptrace(....);
		 *
		 * For this call to ptrace, an error can be detected with errno.
		 *
		 */

		instr = ptrace(PTRACE_PEEKTEXT, child, addr, NULL);

		if (errno != 0)
			error("ptrace failed");

		if (instr_primary(instr) == PO_X
			&& instr_field(instr, 21, 10) == EO_DIVW) {
			install_instr(table, addr, instr);
			ptrace(PTRACE_POKETEXT, child, addr, 0);
			n += 1;
		}
	}

	return n;
}

static size_t rewrite_text(pid_t child, char* program, instr_table_t* table)
{
	FILE*		fp;		/* the executable file. */
	Elf32_Ehdr	ehdr;		/* ELF header, first in file. */
	Elf32_Shdr	shdr;		/* A section header. */
	size_t		i;		/* index variable. */
	size_t		n;		/* number of rewrites. */

	fp = fopen(program, "r");

	if (fp == NULL)
		error("cannot open \"%s\" for reading", program);

	if (fread(&ehdr, sizeof ehdr, 1, fp) != 1)
		error("cannot read elf header");

	if (fseek(fp, ehdr.e_shoff, SEEK_SET) < 0)
		error("cannot fseek to shoff");

	for (n = i = 0; i < ehdr.e_shnum; i += 1) {
		if (fread(&shdr, sizeof shdr, 1, fp) != 1)
			error("cannot read section header");

		else if (shdr.sh_type == SHT_PROGBITS && (shdr.sh_flags & SHF_EXECINSTR))
			n += rewrite_instr(child, shdr.sh_addr, shdr.sh_size, table);
	}

	fclose(fp);

	return n;
}

int main(int argc, char** argv)
{
	int			w;		/* column width in output. 		*/
	pid_t			child;		/* child pid. 				*/
	primary_opcode_t	primary;	/* leftmost 6 bits of Power instr. 	*/
	extended_opcode_t	extended;	/* Power opcode for divide word. 	*/
	int			ra;		/* register of numerator. 		*/
	int			rb;		/* register of denominator. 		*/
	int			c;		/* system call status code. 		*/
	int			i;		/* loop index. 				*/
	int			status;		/* waitpid status. 			*/
	struct pt_regs		regs;		/* copy of child registers. 		*/
	instr_table_t*		table;		/* table of divide instr. 		*/
	uint32_t		addr;		/* stop address of child. 		*/
	uint32_t		instr;		/* instr of child. 			*/
	size_t			n;		/* num static divw instr. 		*/
	uint64_t		ndivw;		/* num executed divw instr. 		*/
	uint64_t		sum;		/* denominators > max. 			*/
	FILE*			divfp;		/* trace file for -t. 			*/
	char*			output;		/* output file name. 			*/

	progname = argv[0];

	memset(&regs, 0, sizeof regs);
	ndivw = 0;

	if (argv[1] != NULL && strcmp(argv[1], "-t") == 0) {
		--argc;
		++argv;

		output = "div.output";
		divfp = fopen(output, "w");

		if (divfp == NULL)
			error("cannot open \"%s\" for writing", output);
	} else
		divfp = NULL;

	child = fork();

	if (child == 0) {
		pr("child is %d\n", getpid());

		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) != 0)
			error("ptrace failed in child");

		execve(argv[1], argv+1, NULL);
		error("child execve failed");

	} else if (child < 0)
		error("could not fork");

	table = new_instr_table();

	status = 0;

	c = waitpid(child, &status, 0);

	if (c < 0 || !WIFSTOPPED(status))
		error("parent expected a stopped child");

	pr("parent found stopped child\n");
	n = rewrite_text(child, argv[1], table);
	pr("parent rewrote child text\n");
	fprintf(stderr, "%zu divw instr in child program\n", n);

	for (;;) {
    if (ptrace (PTRACE_CONT, child, NULL, 0) != 0)
      error("ptrace failed in child");

		c = waitpid(child, &status, 0);

		if (c < 0)
			error("waitpid failed");

		if (WIFEXITED(status))
			break;

		if (c < 0 || !WIFSTOPPED(status))
			error("parent expected a stopped child");

		pr("parent found stopped child\n");

		// regs.nip = 0; // MODIFY!
		if(ptrace(PTRACE_GETREGS, child, NULL, &regs) != 0) {
			error("ptrace failed in child when fetching registers");
		}

		addr = regs.nip;

		pr("Addr: %d\n", addr);

		instr = ptrace(PTRACE_PEEKTEXT, child, addr, NULL); // MODIFY!

		if (instr == 0
			&& (instr = lookup_instr(table, addr)) != 0
			&& instr_primary(instr) == PO_X
			&& instr_field(instr, 21, 10) == EO_DIVW) {

			if(ptrace(PTRACE_POKETEXT, child, addr, instr) != 0){
				error("ptrace failed in child when rewriting instruction");
			}

			if(ptrace(PTRACE_SINGLESTEP, child, NULL, NULL) != 0){
				error("ptrace failed in child when singlestepping");
			}

			waitpid(child, &status, 0);

			if(ptrace(PTRACE_POKETEXT, child, addr, 0) != 0){
				error("ptrace failed in child when rewriting instruction");
			}

			ra = instr_field(instr, 11, 5);
			rb = instr_field(instr, 16, 5);

			if (divfp != NULL)
				fprintf(divfp, "%d / %d\n", regs.gpr[ra], regs.gpr[rb]);

			if (labs(regs.gpr[rb]) <= MAX_DENOMINATOR)
				hist[labs(regs.gpr[rb])] += 1;

			ndivw += 1;
		}

	}

	free_instr_table(table);

	if (ndivw > 0) {
		w = 12;		/* column width. */
		sum = 0;
		fprintf(stderr, "%*s %*s %*s\n", w, "denominator", w, "count", w, "fraction");
		for (i = 1; i <= MAX_DENOMINATOR; i += 1) {
			if (hist[i] > 0) {
				sum += hist[i];
				fprintf(stderr, "%*d %*llu %*.1lf %%\n", w, i, w, hist[i], w, 100.0 * hist[i] / ndivw);
			}
		}
		fprintf(stderr, "%*s %*llu %*.1lf %%\n", w, (">" str(MAX_DENOMINATOR)), w, ndivw - sum, w, 100.0 * (ndivw - sum) / ndivw);
	}

	fprintf(stderr, "%llu executed divw instr\n", ndivw);

	if (divfp != NULL)
		fclose(divfp);

	return 0;
}

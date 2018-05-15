#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instr_table.h"
#include "error.h"

typedef struct {
	uint32_t	instr;
	uint32_t	addr;
} instr_t;

struct instr_table_t {
	size_t		n;	/* actually used. */
	size_t		size;	/* allocated storage. */
	instr_t*	a;
};

instr_table_t* new_instr_table(void)
{
	instr_table_t*	table;

	table = calloc(1, sizeof(instr_table_t));

	if (table == NULL)
		error("out of memory");

	table->size		= 8;
	table->a 		= calloc(1, table->size * sizeof(instr_t));

	if (table->a == NULL)
		error("out of memory");

	return table;
}

void free_instr_table(instr_table_t* table)
{
	free(table->a);
	free(table);
}

static void install(instr_t* a, size_t size, uint32_t addr, uint32_t instr)
{
	size_t		i;

	i = (addr / 4) & (size-1);

	while (a[i].addr != 0)
		i = (i + 1) & (size-1);

	a[i].addr = addr;
	a[i].instr = instr;
}

void install_instr(instr_table_t* table, uint32_t addr, uint32_t instr)
{
	size_t		i;
	instr_t*	a;

	install(table->a, table->size, addr, instr);

	table->n += 1;

	if (table->n * 2 > table->size) {
		a = calloc(1, 2 * table->size * sizeof(instr_t));
		if (a == NULL)
			error("out of memory");
		for (i = 0; i < table->size; i += 1)
			if (table->a[i].addr != 0)
				install(a, 2 * table->size, table->a[i].addr, table->a[i].instr);

		table->size *= 2;
		free(table->a);
		table->a = a;
	}
}

uint32_t lookup_instr(instr_table_t* table, uint32_t addr)
{
	size_t		i;

	i = (addr / 4) & (table->size-1);

	while (table->a[i].addr != 0)
		if (table->a[i].addr == addr)
			return table->a[i].instr;
		else
			i = (i + 1) & (table->size-1);

	error("addr %08x not in table", addr);

	return 0;
}

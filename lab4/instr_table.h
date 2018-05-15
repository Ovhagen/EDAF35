#ifndef instr_table_h
#define instr_table_h

#include <stdint.h>

typedef struct instr_table_t instr_table_t;

instr_table_t* new_instr_table(void);
void free_instr_table(instr_table_t* h);
void install_instr(instr_table_t* h, uint32_t instr, uint32_t addr);
uint32_t lookup_instr(instr_table_t* h, uint32_t addr);

#endif

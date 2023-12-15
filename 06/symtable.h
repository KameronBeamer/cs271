#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <ctype.h>

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

typedef struct Symbol {
	char *name;
	hack_addr addr;
} Symbol;



unsigned int hashCode(char *str);
struct Symbol *symtable_find(char *name);
void symtable_insert(char *name, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();

#endif

/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Kameron Beamer
 * [TERM] FALL 2023
 * 
 ****************************************/
#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "symtable.h"
#include "error.h"
#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH  MAX_LINE_LENGTH - 2
#define MAX_HACK_ADDRESS  INT16_MAX
#define MAX_INSTRUCTIONS  MAX_HACK_ADDRESS

#include "symtable.h"

typedef int16_t hack_addr;
typedef int16_t opcode;

/** function prototypes **/
char *strip(char *s);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

char *extract_label(const char *line, char* label);

void add_predefined_symbols();


enum instr_type {
	Invalid = -1,
	A_Type,
	C_Type,
};

typedef struct a_instruction {
	union a_type_choice {
		hack_addr address;
		char *label;
	} operand;
	bool is_addr;
} a_instruction;

typedef struct c_instruction {
	opcode a:1;
	opcode comp:7;
	opcode dest:4;
	opcode jump:4;
} c_instruction;

typedef struct instruction {
	union instruction_type {
		a_instruction a;
		c_instruction c;
	} instr;
	enum instr_type field;
} instruction;


int parse(FILE * file, instruction *instructions);
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);

void assemble(const char * file_name, instruction* instructions, int num_instructions);
	

#endif

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

//#include "symtable.h"
#include "error.h"

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
	
void parse(FILE * file);

#endif

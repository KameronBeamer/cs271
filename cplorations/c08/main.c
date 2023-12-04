/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Kameron Beamer
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"

int main(int argc, const char *argv[])
{		

	// your code here
	if(argc != 2) {
		// incorrect number of arguments
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);  
	}
	
	FILE *fin = fopen(argv[1], "r" );
	
	if(fin == NULL){ 
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}
	
	parse(fin);
	
	//symtable_print_labels();
	
	fclose(fin);

	return 1;
	
}



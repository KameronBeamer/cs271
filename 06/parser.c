/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Kameron Beamer
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	// your code here
	char s_new[strlen(s)+1];
	int i = 0;
	
	for(char *s2 = s; *s2; s2++) {
		
		if(*s2 == '/' && *(s2+1) == '/') {
			break;
		} else if(!isspace(*s2)) {
			s_new[i++] = *s2;
		}
	}
	
	s_new[i] = '\0';
	strcpy(s, s_new);
	
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
int parse(FILE * file, instruction *instructions) {
	
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	instruction instr;
	
	add_predefined_symbols();
	
	while (fgets(line, sizeof(line), file)) {
		
		line_num ++;
		
		// skip if a comment or starts blank, temporary fix
		if((line[0] == '/' && line[1] == '/') || line[0] == '\n') {
			continue;
		}
		
		
		if(instr_num > MAX_INSTRUCTIONS) {
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		
		strip(line);
		
		if(*line) {
			
			char inst_type = ' ';
			// Determines line type
			if(is_Atype(line)) {
				inst_type = 'A';
				if (!parse_A_instruction(line, &instr.instr.a)){
					exit_program(EXIT_INVALID_A_INSTR, line_num, line);
				}
				instr.field = A_Type;
				
				if(instr.instr.a.is_addr) {
					printf("A: %d\n", instr.instr.a.operand.address);
				} else {
					printf("A: %s\n", instr.instr.a.operand.label);
				}
 
			} else if((is_label(line))) {
				inst_type = 'L';
				char label[MAX_LABEL_LENGTH] = {0};
				strcpy(line, extract_label(line, label));
				
				if(!isalpha(label[0])) {
					exit_program(EXIT_INVALID_LABEL, line_num, line);
				} else if((symtable_find(label)) != NULL) {
					exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
				} else {
					symtable_insert(label, instr_num);
					continue;
				}
				
			} else if(is_Ctype(line)) {
				inst_type = 'C';
				char tmp_line [MAX_LINE_LENGTH] = {0};
				strcpy(tmp_line, line);
				parse_C_instruction(tmp_line, &instr.instr.c);
				
				if(instr.instr.c.dest == -1) {
					exit_program(EXIT_INVALID_C_DEST, line_num, line);
				} else if (instr.instr.c.comp == -1) {
					exit_program(EXIT_INVALID_C_COMP, line_num, line);
				} else if (instr.instr.c.jump == -1) {
					exit_program(EXIT_INVALID_C_JUMP, line_num, line);
				}
				
				instr.field = C_Type;
				printf("C: d=%d, c=%d, j=%d\n", instr.instr.c.dest, instr.instr.c.comp, instr.instr.c.jump);

			}
			
			//printf("%c  %s\n", inst_type, line);
			//printf("%u: %c  %s\n", instr_num, inst_type, line);
		}
		
		instructions[instr_num++] = instr;
	}
	
	return instr_num;
}

/* Function: is_Atype
 * -------------
 * returns if line is an address instruction
 */
bool is_Atype(const char *line) {
	return (line[0] == '@');
}

/* Function: is_label
 * -------------
 * returns if line is a label
 */
bool is_label(const char *line) {
	if(line[0] != '(') {
		return false;
	} else if(line[strlen(line)-1] != ')') {
		return false;
	} else {
		return true;
	}
}

/* Function: is_label
 * -------------
 * returns if line is not a comment, address, or label
 */
bool is_Ctype(const char *line) {
	return (isalnum(line[0]));
}

/* Function: extract_label
 * -------------
 */
char *extract_label(const char *line, char* label) {
	char temp[MAX_LABEL_LENGTH] = {0};
	
	for( int i=1; i < strlen(line)-1; i++){
		temp[i-1] = line[i];
	}
	
	strcpy(label, temp);
	
	return label;
}

/*
 *
 */
void add_predefined_symbols() {
	for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
		predefined_symbol item = predefined_symbols[i];		
		symtable_insert(item.name, item.address);
	}
}	
 
/*
 *
 */ 
bool parse_A_instruction(const char *line, a_instruction *instr) {
	char* s = (char*)malloc(strlen(line));
	strcpy(s, line+1);
	char* s_end = NULL;
	long result = strtol(s, &s_end, 10);
	
	if((s == s_end)) {
		instr->operand.label = (char*)malloc(strlen(line));
		strcpy(instr->operand.label, s);
		instr->is_addr = false;
	} else if(*s_end != 0) {
		return false;
	} else {
		instr->operand.address = result;
		instr->is_addr = true;
	}
	return true;
}


/*
 * step 7, if confused start here
 */
void parse_C_instruction(char *line, c_instruction *instr) {
	char* temp = strtok(line, ";");
	char* jump = strtok(0, ";");
	char* tok = strtok(line, "=");
	char* dest = temp;
	char* comp = strtok(0, "=");
	int a = 0;
	
	if(comp == NULL) {
		char* swap = comp;
		comp = dest;
		dest = swap;
	}
	
	
	instr->jump = str_to_jumpid(jump);
	instr->dest = str_to_destid(dest);
	instr->comp = str_to_compid(comp, &a);
	instr->a = (instr->comp >= 0) ? 0 : 1;
	
}

/*
 * Function: Assemble
 * ------------------
 * Convenverts ___ from one file to machine code to a respective hack file
 */
void assemble(const char * file_name, instruction* instructions, int num_instructions) {
	// open or create new file to write to
	char *hack_name = file_name;
	strcat(hack_name, ".hack");
	FILE *hack_file = fopen(hack_name, "w" );
	
	int instr_num = 0;
	instruction instr;
	opcode op = 0;
	int variable_num = 16;
	
	while(instr_num <= num_instructions) {
		instr = instructions[instr_num];
		
		if(!instr.instr.a.is_addr){
			hack_addr symbol = symtable_find(instr.instr.a.operand);
			
			if(symbol == NULL) {
				symtable_insert(instr.instr.a.operand, variable_num);
				symbol = symtable_find(instr.instr.a.operand);
			}
			
			op = symbol;
			
			// currently unsure what to be freeing
			//free(instr);
		} else if(instr.instr.a.is_addr) {
			op = instr.instr.a.operand.address;
			
		} else /* if(instr.instr.c) */ {
			//instruction_to_opcode
			//OPCODE_TO_BINARY
			
		}
		
		instr_num++;
	}
	
	fclose(hack_file);
}

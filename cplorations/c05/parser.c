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
void parse(FILE * file){
	
	// your code here
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;
	
	while (fgets(line, sizeof(line), file)) {
		strip(line);
		if(*line) {
			
			char inst_type = ' ';
			if(is_Atype(line)) {
				inst_type = 'A';
			} else if(is_label(line)) {
				inst_type = 'L';
			} else if(is_Ctype(line)) {
				inst_type = 'C';
			}
			
			printf("%c  %s\n", inst_type, line);
		}
		line_num ++;
	}
	
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
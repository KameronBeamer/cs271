#include "symtable.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];
struct Symbol* item;

unsigned int hashCode(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	//printf("%ld", hash);
    return hash % SYMBOL_TABLE_SIZE;
}

struct Symbol *symtable_find(char *name) {
   //get the hash 
   int hashIndex = hashCode(name);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->name == name)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SYMBOL_TABLE_SIZE;
   }        
	
   return NULL;        
}

void symtable_insert(char *name, hack_addr addr) {

	struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
	item->addr = addr;
	item->name = (char*)malloc(strlen(name) + 1);
	strcpy(item->name, name);
   
   //get the hash 
   int hashIndex = hashCode(name);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SYMBOL_TABLE_SIZE;
   }
	
   hashArray[hashIndex] = item;
}

void symtable_display_table() {
   int i = 0;
	
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(" (%s,%d)",hashArray[i]->name,hashArray[i]->addr);
      else
         printf(" ~~ ");
   }
	
   printf("\n");
}

void symtable_print_labels() {
   int i = 0;    
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
   }
} 

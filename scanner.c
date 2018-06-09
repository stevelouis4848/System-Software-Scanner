// Name: Steve Louis
// Class: COP 3402 summer 2018
// Assignment: Homework #2 (Scanner)
// 06/15/2018

/*
README

	# How to run

*/

#include <stdlib.h>
#include <stdio.h>

int IDENTIFIER_MAX_LENGTH = 11;
int NUMBER_MAX_LENGTH = 5;
int TABLE_SIZE = 33;

char table[] = {"NULL",'','','','','*','/','','+','-','*','/','','=','-',
					'<','<=','>','>=','(',')',',',';','.','','begin','end',
					'if','then','while','do','call','const','var','','write',
					'read','else'}
					
voidvoid wordVarSymEncoder(char *buffer, FILE *ofp){(char *buffer, FILE *ofp);

int main(int argc, char **argv){
	
	int i;
	
	for(i = 1;i < argc; i++){
		
		scanner(argv[i]);				
	}
	return 0;
}

void scanner(char *fileName){
	
	FILE *ifp, *ofp, *ofp2;
	char buffer[11];
	
	
	ifp = (filename,"r");
	ofp = (,"w");
	ofp2 = ("r");
	
	while(fscanf(ifp, %s, &buffer) != EOF){
		
		
	}
	
}

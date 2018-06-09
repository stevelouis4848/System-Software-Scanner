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

typedef struct listyString{
							int position;
							char c;
							struct listyString *head;
							struct listyString *tail;
							
}listyString;



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
	char buffer;
	listyString *input, *newNode;
	int i = 0;;
		
	input = malloc(sizeof(listyString));
		
	ifp = (filename,"r");
	ofp = (,"w");
	ofp2 = ("r");
	
	input->head = input;
	input->position = 0;
	lastPosition 
	
	while(fscanf(ifp, %c, &buffer) != EOF){
		
		i++;
		
		newNode = malloc(sizeof(listyString));
		
		newNode->head = input;
		newNode->c = *buffer;
		newNode->position = i;
		
		newNode = NULL;
	}
	
}

void Encoder(){listyString *input
	
	
}

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
							int size;
							char c;
							struct listyString *head;
							struct listyString *next;						
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
	listyString *inputHead, *newNode, *prevNode;
	int i = 0;;
		
	inputHead = malloc(sizeof(listyString));
		
	ifp = (filename,"r");
	ofp = (,"w");
	ofp2 = ("r");
	
	inputHead->head = inputHead;
	inputHead->size = i;
	
	prevNode = inputHead;
	
	for (i = 1: fscanf(ifp, %c, &buffer) != EOF; i++){		
		
		newNode = malloc(sizeof(listyString));
		
		newNode->head = inputHead;
		newNode->c = *buffer;
		newNode->size = i;
		
		prevNode->next = newNode;
		prevNode = newNode;
		newNode = NULL;
	}
	
	encoder(inputHead,ofp);	
}

void encoder(listyString* inputHead, FILE *ofp){
	
	int i, j;
	char *bufferChar;
	int *bufferInt;
	listyString *temporaryHead;
	
	
	if(inputHead = NULL){
		
		printf("listyString is NULL");
		return;
	}
		
	if(isalpha(inputHead-->c ) != 0){
			
		temporaryHead = inputhead;
		for( i = 0;isdigit(temporaryHead->c ) != 0 || isalpha(temporaryHead->c ) != 0; i++){
			
			bufferChar = malloc(i + 1 * sizeof(char));
			bufferChar[i] = temporaryHead->c;
			temporaryHead = temporaryHead->next;

			for(j = 0; j < TABLE_SIZE; j++){
				
				if(strcmp(*bufferChar, *table[i]) != 0){
					
					printf("%d ",i)
					
					encoder(temporaryHead,ofp);				
				}				
			}
		}
		
		printf("2%s", *buffer);
		encoder(remporaryHead, ofp);		
	}
	
	if else(isdigit(inputHead->c ) != 0){
		
		temporaryHead = inputhead;
		for(i = 0; isdigit(temporaryHead->c != 0); i++){
			
			bufferInt = malloc(i + 1 * sizeof(int));
			bufferInt[i] = temporaryHead->c;
			temporaryHead = temporaryHead->next;			
		}
		
		printf("3%d ", *bufferInt);
		encoder(temporaryHead,ofp);
	}
	
	else{
		
		i = 0;
		
		bufferChar = malloc(sizeof(int))
		temporaryHead = inputHead;
		
			bufferChar[i] = temporaryHead->c;
			
			
		if(temporary->c == '<' || temporary->c == '>' && temporary->next->c == '=' ){
		
			
		
		}
		
		
	}
}


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
#include <string.h>
#include <ctype.h>


int IDENTIFIER_MAX_LENGTH = 11;
int NUMBER_MAX_LENGTH = 5;
int TABLE_SIZE = 33;

typedef struct listyString{
							int c;
							struct listyString *next;						
}listyString;

char *table[] = {"NULL","NULL","NULL","NULL","NULL","*","/","","+","-","*","/","NULL","=","-",
					"<","<=",">",">=","(",")","NULL",";",".","NULL","begin","end",
					"if","then","while","do","call","const","var","NULL","write",
					"read","else"};
					
void scanner(char *fileName);
void encoder(listyString* inputHead, FILE *ofp);
void stringCopy(char *str1, char *str2, int length);
void intCopy(int *str1, int *str2, int length);
void intEncoder(listyString *inputHead,FILE *ofp);
void wordVarEncoder(listyString *inputHead, FILE *ofp);
void symEncoder(listyString *inputHead, FILE *ofp);

int main(int argc, char **argv){
	
	int i;
	
	printf("main\n");
	for(i = 1;i < argc; i++){
		
		scanner(argv[i]);				
	}
	return 0;
}

void scanner(char *fileName){
	
	printf("scanner\n");
	FILE *ifp, *ofp, *ofp2;
	int buffer;
	
	listyString *inputHead, *newNode, *prevNode;
	
	inputHead = malloc(sizeof(listyString));
		
	ifp = fopen(fileName,"r");
	ofp = fopen("outputFile.txt","w");
	//ofp2 = ("r");

	if ((buffer = fgetc(ifp)) != EOF){
		
		inputHead->c = buffer;
		prevNode = inputHead;
		printf("inside while Input: %c\n",prevNode->c);
	}
	while((buffer = fgetc(ifp)) != EOF){		
		
		
		
		newNode = malloc(sizeof(listyString));
		
		newNode->c = buffer;
		
		prevNode->next = newNode;
		prevNode = newNode;
		newNode = NULL;
		printf("inside while Input: %c\n",prevNode->c);
	}
	encoder(inputHead, ofp);	
}

void encoder(listyString* inputHead, FILE *ofp){
	printf("encoder\n");
	int i, j;
	char *bufferChar, *prevBufferChar;
	int *bufferInt, *prevBufferInt;
	
	if(inputHead == NULL){
		
		printf("listyString is NULL\n");
		fflush( stdout );
		return;
	}
	if(isalpha(inputHead->c ) != 0){
			
		printf("wordVarEncoder\n");
		fflush( stdout );
		//wordVarEncoder(inputHead, ofp);
	}
	else if(isdigit(inputHead->c ) != 0){
		
		printf("intEncoder\n");
		fflush( stdout );
		//intEncoder(inputHead, ofp);
	}
	
	else{
		
		printf("SymEncoder\n");
		fflush( stdout );
		//symEncoder(inputHead, ofp);	
		
	}	 
}

/*
void intEncoder(listyString *inputHead, FILE *ofp){
	
	printf("intDecoder");
	int i = 0, j = 0;;
	
	int *bufferInt, *prevBufferInt;
	listyString *temporaryHead;
	
	temporaryHead = inputHead;
		
	prevBufferInt = malloc(i + 1 * sizeof(char));
	prevBufferInt[i] = temporaryHead->c;
	temporaryHead = temporaryHead->next;
	
	for(i = 1; isdigit(temporaryHead->c != 0); i++){
		
		bufferInt = malloc(i + 2 * sizeof(int));
		
		intCopy(prevBufferInt, bufferInt, i);
					
		bufferInt[i] = temporaryHead->c;
		temporaryHead = temporaryHead->next;			
	}
	
	if(i > NUMBER_MAX_LENGTH){
		
		printf("ERROR:number too long ");
		encoder(temporaryHead,ofp);
	}
	
	else{
		
		for(j = 0;j < i; j++){
			
			printf("3%d ", bufferInt[j]);
		}
		
		encoder(temporaryHead,ofp);
	}
}

void wordVarEncoder(listyString *inputHead, FILE *ofp){
	
	printf("wordVarDecoder");
	int i = 0, j = 0;
	
	char *bufferChar, *prevBufferChar;
	listyString *temporaryHead;
	
	temporaryHead = inputHead;
	
	prevBufferChar = malloc(i + 1 * sizeof(char));
	prevBufferChar[i] = temporaryHead->c;
	temporaryHead = temporaryHead->next;
	
	for( i = 1;isdigit(temporaryHead->c ) != 0 || isalpha(temporaryHead->c ) != 0; i++){
		
		bufferChar = malloc(i + 2 * sizeof(char));
		
		stringCopy(prevBufferChar, bufferChar, i);
		
		bufferChar[i] = temporaryHead->c;
		temporaryHead = temporaryHead->next;

		for(j = 0; j < TABLE_SIZE; j++){
			
			if(strcmp(bufferChar, table[j]) == 0){
				
				printf("%d ",j);
				
				encoder(temporaryHead, ofp);				
			}				
		}	

		free(prevBufferChar);
		prevBufferChar = NULL;
		
		prevBufferChar = malloc(i + 1 * sizeof(char));
		
		stringCopy(bufferChar, prevBufferChar, i);
		
		free(bufferChar);
		bufferChar = NULL;
	}
	
	if(i > NUMBER_MAX_LENGTH){
		
		printf("ERROR:variable too long ");
		encoder(temporaryHead,ofp);
	}
	
	else{
		
		printf("2%s", bufferChar);
		encoder(temporaryHead, ofp);
	}
}

void symEncoder(listyString *inputHead, FILE *ofp){
	printf("symDecoder");
	listyString *temporaryHead;
	char *bufferChar;
	
	int i = 0;
		
	bufferChar = malloc(sizeof(int));
	temporaryHead = inputHead;
	
	bufferChar[i] = temporaryHead->c;
		
	i++;
	
	if(temporaryHead->c == '<' || temporaryHead->c == '>' && temporaryHead->next->c == '=' ){
		
	}	
}

void stringCopy(char *str1, char *str2, int length){
	printf("stringCopy");
	int i;
	
	for(i = 0; i < length; i++){
				
				str2[i] = str1[i];
			}
}

void intCopy(int *str1, int *str2, int length){
	printf("intCopy");
	int i;
	
	for(i = 0; i < length; i++){
				
				str2[i] = str1[i];
	}
}
*/

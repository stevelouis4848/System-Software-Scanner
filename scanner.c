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

char *table[] = {"0", "\0", "2", "3", "+", "-", "*", "/", "%", "=", "!=", "<", "<=", ">", ">=",
					"(", ")", ",", ";", ".", ":=", "begin", "end", "if", "then", "while", "do",
					"call", "const", "var", "procedure", "write", "read", "else"
				};
					
void scanner(char *fileName);
void encoder(listyString* inputHead, FILE *ofp);
//void intEncoder(listyString *inputHead,FILE *ofp);
void wordVarEncoder(listyString *inputHead, FILE *ofp);
void symEncoder(listyString *inputHead, FILE *ofp);
void wordVarTable(listyString *temporaryHead, char *bufferChar,FILE *ofp, int length);

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
		exit(0);
	}
	if(isalpha(inputHead->c ) != 0){
			
		printf("wordVarEncoder\n");
		fflush( stdout );
		wordVarEncoder(inputHead, ofp);
	}
	else if(isdigit(inputHead->c ) != 0){
		
		printf("intEncoder\n");
		fflush( stdout );
		//intEncoder(inputHead, ofp);
	}
	
	else{
		
		printf("SymEncoder\n");
		fflush( stdout );
		symEncoder(inputHead, ofp);	
		
	}	 
}

void wordVarEncoder(listyString *inputHead, FILE *ofp){
	
	printf("wordVarDecoder1\n");
	int i = 0, j = 0, strLength = 0;
	
	char *bufferChar;
	listyString *temporaryHead;
	
	if(inputHead == NULL){
	
		printf("inputhead NULL\n");
		return;	
	}
	
	temporaryHead = inputHead;

	for( i = 0; (temporaryHead != NULL) && (isdigit(temporaryHead->c) != 0) || (isalpha(temporaryHead->c ) != 0); i++){
	
		temporaryHead = temporaryHead->next;
		strLength++;		
	}
	
	bufferChar = malloc(strLength * sizeof(char));
	temporaryHead = inputHead;
	
	
	for( i = 0; i < strLength; i++){
		
		bufferChar[i] = temporaryHead->c;
		temporaryHead = temporaryHead->next;
	}	
	
	if(strLength <= IDENTIFIER_MAX_LENGTH){
		
		for(i = 0;i < TABLE_SIZE; i++){
		
			if(strcmp(bufferChar,table[i]) == 0){
				printf("%d %s\n",i,bufferChar);	
				encoder(temporaryHead, ofp);
			}			
		}		
		
		printf("2 %s\n",bufferChar);
		encoder(temporaryHead, ofp);
	}
	else{
			printf("error:Identifier too long %s",bufferChar);	
			encoder(temporaryHead, ofp);
	}	
}
/*
void intEncoder(listyString *inputHead, FILE *ofp){
	
	printf("intDecoder\n");
	int i, j,strLength = 0;
	
	char *bufferInt, *prevBufferInt;
	listyString *temporaryHead;
	
	if( (temporaryHead->next == NULL) || (isdigit(temporaryHead->next->c == 0))){
		
		printf("3");
		for(j = 0;j <= i; j++){
			
			printf("%c", bufferInt[j]);
		}
		printf("\n");
		encoder(temporaryHead->next,ofp);	
	}
	
	temporaryHead = temporaryHead->next;

	for(i = 1; (temporaryHead != NULL) && (isdigit(temporaryHead->c) != 0) || (isalpha(temporaryHead->c) != 0); i++){
		
		
		if(( (temporaryHead->next != NULL) || isdigit(temporaryHead->next->c == 0))){
			printf("intDecoder3\n");
			
			strLength = strlen(bufferInt);
			for(j = 0; j < strLength; j++ ){
				
				if(isdigit(bufferInt) == 0){
					printf("%s",bufferInt);
					printf("error invalid entry number contains letter");				
				}				
			}
			if(i > NUMBER_MAX_LENGTH){			
				printf("ERROR:number too long ");
				encoder(temporaryHead->next,ofp);
			}
		
			else{
				
				printf("3");
				for(j = 0;j < i; j++){
					
					printf("%c", bufferInt[j]);
					
				}
				printf("\n");
				encoder(temporaryHead->next,ofp);
			}
		}
		
		temporaryHead = temporaryHead->next;
	}		
}
*/
void symEncoder(listyString *inputHead, FILE *ofp){
	printf("symDecoder");
	int i = 0;
	char *bufferSym, *nextBufferSym;;
	listyString *temporaryHead;
				
	temporaryHead = inputHead;
		
	bufferSym = malloc(2 * sizeof(char));
	nextBufferSym = malloc(2 * sizeof(char));
		
	bufferSym[0] = temporaryHead->c;
	//bufferSym[1] = "\0";
	
	
	if(temporaryHead->next != NULL && strcmp(bufferSym,"<") == 0 || strcmp(bufferSym,"<") == 0 || strcmp(bufferSym,"!") == 0){
		
		nextBufferSym[0] = temporaryHead->next->c;
		//nextBufferSym[1] = "\0";
		
		
		if(strcmp(nextBufferSym,"=") == 0){
			
			bufferSym[1] = nextBufferSym[0];
			temporaryHead = temporaryHead->next;
		}				
	}
		
	else if((temporaryHead->next != NULL) && strcmp(bufferSym,"/") == 0){
		
		nextBufferSym[0] = temporaryHead->next->c; 
		
		if(strcmp(nextBufferSym,"/") == 0){
			
			while((temporaryHead->next != NULL) && (temporaryHead->next->next != NULL)){
				
				//while ((temporaryHead->c != "*") && (temporaryHead->c != "/") ){
			
					temporaryHead = temporaryHead->next;			
				//}	
				encoder(temporaryHead->next, ofp);
			}
		}
	}
	
	for(i = 0; i < TABLE_SIZE; i++){
		
		if(strcmp(bufferSym,table[i]) == 0){
				printf("%d %s\n",i,bufferSym);	
				encoder(temporaryHead->next, ofp);
			}				
	}
}
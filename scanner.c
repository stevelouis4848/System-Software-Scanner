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
		intEncoder(inputHead, ofp);
	}
	
	else{
		
		printf("SymEncoder\n");
		fflush( stdout );
		//symEncoder(inputHead, ofp);	
		
	}	 
}

void wordVarEncoder(listyString *inputHead, FILE *ofp){
	
	printf("wordVarDecoder1\n");
	int i = 0, j = 0;
	
	char *bufferChar, *prevBufferChar;
	listyString *temporaryHead;
	
	if(inputHead == NULL){
	
		printf("inputhead NULL\n");
		return;	
	}
	
	temporaryHead = inputHead;
	
	prevBufferChar = malloc(i + 1 * sizeof(char));
	prevBufferChar[i] = temporaryHead->c;
	prevBufferChar[i + 1] = '\0';
	
	printf("\nwordVarDecoder2\n");
	printf("temporaryHead->c: %c\n",temporaryHead->c);
	printf("bufferChar:%s\n",prevBufferChar);
	fflush( stdout );
	
	wordVarTable(temporaryHead, prevBufferChar, ofp, i);
	
	temporaryHead = temporaryHead->next;
	
	for( i = 1; (temporaryHead != NULL) && (isdigit(temporaryHead->c ) != 0) || (isalpha(temporaryHead->c ) != 0); i++){
		
		printf("\nwordVarDecoder3\n");
		printf("temporaryHead->c: %c\n",temporaryHead->c);
		fflush( stdout );
		
		bufferChar = malloc(i + 1 * sizeof(char));
		bufferChar[i + 1] = '\0';
		
		stringCopy(prevBufferChar, bufferChar, i-1);
		
		bufferChar[i] = temporaryHead->c;
		
		wordVarTable(temporaryHead, bufferChar, ofp, i);
			
		free(prevBufferChar);
		prevBufferChar = NULL;
		
		prevBufferChar = malloc(i + 1 * sizeof(char));
		
		stringCopy(bufferChar, prevBufferChar, i + 1);
		
		free(bufferChar);
		bufferChar = NULL;
		
		temporaryHead = temporaryHead->next;
	}	
}

void wordVarTable(listyString *temporaryHead, char *bufferChar,FILE *ofp, int length){
	
		
		if(strcmp(bufferChar, "become") == 0){
			printf("%s\n",bufferChar);
			printf("20\n");	
			encoder(temporaryHead->next, ofp);					
		}			
		else if(strcmp(bufferChar, "begin") == 0){
			printf("%s\n",bufferChar);
			printf("21\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "end") == 0){
			printf("%s\n",bufferChar);
			printf("22\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "if") == 0){
			printf("%s\n",bufferChar);
			printf("23\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "then") == 0){
			printf("%s\n",bufferChar);
			printf("24\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "while") == 0){
			printf("%s\n",bufferChar);
			printf("25\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "do") == 0){
			printf("%s\n",bufferChar);
			printf("26\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "call") == 0){
			printf("%s\n",bufferChar);
			printf("27\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "const") == 0){
			printf("%s\n",bufferChar);
			printf("28\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "var") == 0){
			printf("%s\n",bufferChar);
			printf("29\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "proc") == 0){
			printf("%s\n",bufferChar);
			printf("30\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "write") == 0){
			printf("%s\n",bufferChar);
			printf("31\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "read") == 0){
			printf("%s\n",bufferChar);
			printf("32\n");
			encoder(temporaryHead->next, ofp);	
		}
		else if(strcmp(bufferChar, "else") == 0){
			printf("%s\n",bufferChar);
			printf("33\n");
			encoder(temporaryHead->next, ofp);	
		}			
		else if((temporaryHead->next == NULL) || (isdigit(temporaryHead->next->c ) == 0) && (isalpha(temporaryHead->next->c ) == 0)){
			
			if(length > NUMBER_MAX_LENGTH){
				printf("wordVarDecoder7\n");
				printf("error too long\n");
				fflush( stdout );
				encoder(temporaryHead->next,ofp);
			}	
			else{
				printf("wordVarDecoder8\n");
				printf("2 %s\n",bufferChar);
				fflush( stdout );
				encoder(temporaryHead->next, ofp);
			}			
		}
}



void intEncoder(listyString *inputHead, FILE *ofp){
	
	printf("intDecoder\n");
	int i, j;
	
	char *bufferInt, *prevBufferInt;
	listyString *temporaryHead;
	
	i = 0;
	temporaryHead = inputHead;
		
	prevBufferInt = malloc(i + 1 * sizeof(char));
	prevBufferInt[i + 1] = '\0';
		
	prevBufferInt[i] = temporaryHead->c;

	if( (temporaryHead->next == NULL) || (isdigit(temporaryHead->next->c == 0))){
		
		printf("3");
		for(j = 0;j <= i; j++){
			
			printf("%c", bufferInt[j]);
		}
		printf("\n");
		encoder(temporaryHead->next,ofp);	
	}
	
	temporaryHead = temporaryHead->next;

	for(i = 1; (temporaryHead != NULL) && (isdigit(temporaryHead->c != 0))  ; i++){
		printf("intDecoder2\n");
		bufferInt = malloc(i + 1 * sizeof(int));
		bufferInt[i + 1] = '\0';
		
		printf("intDecoder2\n");
		stringCopy(prevBufferInt, bufferInt, i-1);
					
		bufferInt[i] = temporaryHead->c;
		
		if(( (temporaryHead->next != NULL) || isdigit(temporaryHead->next->c == 0))){
			printf("intDecoder3\n");
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

/*
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
*/
void stringCopy(char *str1, char *str2, int length){
	printf("stringCopy\n");
	int i;
	
	printf("str1: %s\n",str1);
	
	for(i = 0; i <= length; i++){
				
				str2[i] = str1[i];	
			}
			printf("str2: %s\n",str2);
}

void intCopy(int *str1, int *str2, int length){
	printf("intCopy\n");
	int i;
	
	for(i = 0; i <= length; i++){
				
				str2[i] = str1[i];
	}
}

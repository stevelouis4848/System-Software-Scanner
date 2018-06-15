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
listyString *intEncoder(listyString *inputHead,FILE *ofp);
listyString *wordVarEncoder(listyString *inputHead, FILE *ofp);
listyString *symEncoder(listyString *inputHead, FILE *ofp);

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
	
	listyString *inputHead, *newNode, *prevNode, *temporaryHead;
	
	if(fileName == NULL){
			printf("Invalid file name");		
	}
	
	inputHead = malloc(sizeof(listyString));
		
	ifp = fopen(fileName,"r");
	ofp = fopen("outputFile.txt","w");
	//ofp2 = ("r");
	
	if (ifp == NULL || ofp == NULL){
		
		printf("Invalid file pointers");
	}

	fprintf(ofp, "//%s\n",fileName);
	
	if ((buffer = fgetc(ifp)) != EOF){
		
		inputHead->c = buffer;
		prevNode = inputHead;
		fprintf(ofp, "%c", buffer);
	}
	while((buffer = fgetc(ifp)) != EOF){		
				
		newNode = malloc(sizeof(listyString));
		
		newNode->c = buffer;
		
		prevNode->next = newNode;
		prevNode = newNode;
		newNode = NULL;
		//printf("inside while Input: %c\n",prevNode->c);
		fprintf(ofp, "%c", buffer);
	}
	
	
	prevNode->next = NULL;
	temporaryHead = inputHead;
	
	while(temporaryHead != NULL){
		
		printf("inside while Input: %c\n",temporaryHead->c);
		temporaryHead = temporaryHead->next;		
	}
	
	fprintf(ofp,"\n\n");
	
	encoder(inputHead, ofp);
	
	fclose(ifp);
	fclose(ofp);
}

void encoder(listyString* inputHead, FILE *ofp){
	printf("encoder\n");
	int i, j;
	char *bufferChar, *prevBufferChar;
	int *bufferInt, *prevbufferInt;
	
	if(inputHead == NULL){
			
			printf("listyString is NULL\n");
			fflush( stdout );
			exit(0);
		}
	
	while(inputHead != NULL){
		
		if(isalpha(inputHead->c ) != 0){
				
			printf("wordVarEncoder\n");
			fflush( stdout );
			inputHead = wordVarEncoder(inputHead, ofp);
		}
		else if(isdigit(inputHead->c ) != 0){
			
			printf("intEncoder\n");
			fflush( stdout );
			inputHead = intEncoder(inputHead, ofp);
		}
		
		else{
			
			printf("SymEncoder\n");
			fflush( stdout );
			inputHead = symEncoder(inputHead, ofp);	
			
		}	
	}	
}

listyString *wordVarEncoder(listyString *inputHead, FILE *ofp){
	
	printf("wordVarDecoder1\n");
	fflush(stdout);
	int i = 0, j = 0, strLength;
	
	char *bufferChar;
	listyString *temporaryHead;
	
	if(inputHead == NULL){
	
		//printf("inputHead NULL\n");
		return NULL;
	}
		
	printf("wordVarDecoder2\n");
	fflush(stdout);
		
	temporaryHead = inputHead;
	
	//printf("wordVarDecoder3\n");
	fflush(stdout);
	
	strLength = 0;
		
	while((isdigit(temporaryHead->c) != 0) || (isalpha(temporaryHead->c ) != 0)){
		
			//printf("wordVarDecoder4\n");
			fflush(stdout);
			temporaryHead = temporaryHead->next;	
			strLength++;
			
			if(temporaryHead == NULL){	
				break;		
			}			
	}
	
	if(strLength == 0){
		
		return NULL;
	}
	else{
		
		//printf("strLength = %d\n",strLength);
		
	}
	
	//printf("wordVarDecoder5\n");
	fflush(stdout);
	
	bufferChar = malloc(strLength * sizeof(char));
	temporaryHead = inputHead;
	

	for( i = 0; i < strLength; i++){
		
		//printf("wordVarDecoder6\n");
		fflush(stdout);
		bufferChar[i] = temporaryHead->c;
		temporaryHead = temporaryHead->next;
		//printf("bufferChar: %c\n",bufferChar[i]);
		fflush(stdout);
	}	
	
	if(strLength <= IDENTIFIER_MAX_LENGTH){
		//printf("wordVarDecoder7\n");
		fflush(stdout);
		for(i = 0;i < TABLE_SIZE; i++){
		
			if(strcmp(bufferChar,table[i]) == 0){
				printf("%d %s\n",i,bufferChar);
				fprintf(ofp, "%d %s\n", i, bufferChar);
				return temporaryHead;
			}			
		}		
		
		if(i = TABLE_SIZE){
			printf("2 %s\n",bufferChar);
			fprintf(ofp, "2 %s\n", bufferChar);
		}
	}
	else{
			//printf("wordVarDecoder8\n");
			fflush(stdout);
			printf("error:Identifier too long %s",bufferChar);
			fprintf(ofp, "error:Identifier too long %s", bufferChar);
			//return temporaryHead;
	}	
	
	return temporaryHead;
}

listyString *intEncoder(listyString *inputHead, FILE *ofp){
	
	printf("intDecoder\n");
	fflush(stdout);
	int i, j,strLength;
	
	char *bufferInt;
	listyString *temporaryHead;
	
	if(inputHead == NULL){
		
		return NULL;
	}
	
	temporaryHead = inputHead;
	
	strLength = 0;
	
	while((isdigit(temporaryHead->c) != 0) || (isalpha(temporaryHead->c ) != 0)){
		
			//printf("intDecoder2\n");
			fflush(stdout);
			temporaryHead = temporaryHead->next;	
			
			strLength++;
			
			if(temporaryHead == NULL){	
				break;		
			}			
	}
	
	if(strLength == 0){
		
		return NULL;
	}
	else{
		
		//printf("strLength = %d\n",strLength);
		
	}
	
	temporaryHead = inputHead;

	bufferInt = malloc(strLength * sizeof(char));
	
	for( i = 0; i < strLength; i++){

		//printf("intDecoder3\n");
		fflush(stdout);
		bufferInt[i] = temporaryHead->c;
		temporaryHead = temporaryHead->next;
		fflush(stdout);
	}	
	
	for(i = 0; i < strLength; i++){
		
		if (isdigit(bufferInt[i]) ==  0){
		
			printf("error invalid character: %s\n", bufferInt);
			fprintf(ofp, "error invalid character: %s\n", bufferInt);
			//return temporaryHead;		
		}
	}
	
	if(strLength <= NUMBER_MAX_LENGTH){	
	
		//printf("intDecoder4\n");
		fflush(stdout);
		printf("3");
		fprintf(ofp, "3");
		
		for(i = 0;i < strLength; i++){
			
			printf("%c", bufferInt[i]);
			fprintf(ofp, "%c", bufferInt[i]);
		}		
		
		printf("\n");
		fprintf(ofp,"\n");
		return temporaryHead;
	}
		
	else{
		
		printf("ERROR:number too long ");
		fprintf(ofp, "ERROR:number too long ");
	}
	
	return temporaryHead;
}

listyString *symEncoder(listyString *inputHead, FILE *ofp){
	printf("symDecoder\n");
	fflush(stdout);
	
	int i = 0;
	char *bufferSym, *nextBufferSym;;
	listyString *temporaryHead;
				
	temporaryHead = inputHead;
		
	printf("symDecoder2\n");
	fflush(stdout);
	bufferSym = malloc(2 * sizeof(char));
	nextBufferSym = malloc(2 * sizeof(char));
	
	printf("symDecoder3\n");
	fflush(stdout);
	
	bufferSym[0] = temporaryHead->c;
	bufferSym[1] = '\0';
	
	printf("symDecoder4\n");
	fflush(stdout);
	
	if(isspace(*bufferSym) != 0){
		printf("temporaryHead is space\n");
		fflush(stdout);
		
		return temporaryHead->next;
	}

	else if(temporaryHead->next != NULL && strcmp(bufferSym,"<") == 0 || strcmp(bufferSym,">") == 0 || strcmp(bufferSym,"!") == 0){
		printf("symDecoder5\n");
		fflush(stdout);
		nextBufferSym[0] = temporaryHead->next->c;
		nextBufferSym[1] = '\0';
		
		
		if(strcmp(nextBufferSym,"=") == 0){
			
			bufferSym[1] = nextBufferSym[0];
			temporaryHead = temporaryHead->next;
		}				
	}
		
	else if((temporaryHead->next != NULL) && strcmp(bufferSym,"/") == 0){
		
		printf("symDecoder6\n");
		fflush(stdout);
		nextBufferSym[0] = temporaryHead->next->c; 
		
		if(strcmp(nextBufferSym,"*") == 0){
			
			printf("found begining of comment\n");
			temporaryHead = temporaryHead->next;
					
			while(temporaryHead->next != NULL){
				
				bufferSym[0] = temporaryHead->next->c;
				bufferSym[1] = '\0';
				
				printf("In comment: %s\n",bufferSym);
				
				if((strcmp(bufferSym, "*") == 0) && (temporaryHead->next != NULL)){
					
					temporaryHead = temporaryHead->next;
					
					bufferSym[1] = temporaryHead->next->c;
					
					if(strcmp(bufferSym, "*/") == 0){
						
						temporaryHead = temporaryHead->next;
						
						printf("found end of comment\n");
						return temporaryHead->next;	
						
					}		
				}									
				temporaryHead = temporaryHead->next;
			}
			printf("Invalid comment\n");
			return NULL;
		}
	}
	
	for(i = 0; i < TABLE_SIZE; i++){
		
		//printf("symDecoder7\n");
		fflush(stdout);
		if(strcmp(bufferSym,table[i]) == 0){
			
			printf("%d %s\n", i, bufferSym);
			fprintf(ofp, "%d %s\n", i, bufferSym);
			return temporaryHead->next;
		}						
	}
	if(i == TABLE_SIZE){
		
		printf("error Invalid symbol: %s\n", bufferSym);
		fprintf(ofp, "error Invalid symbol: %s\n", bufferSym);
	}
	return temporaryHead->next;
}
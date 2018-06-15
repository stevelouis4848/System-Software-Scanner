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

typedef struct lexToken{
							char *lexme
							int token;
							int error;
							struct lexToken*next;						
}lexToken;

char *table[] = {"0", "\0", "2", "3", "+", "-", "*", "/", "%", "=", "!=", "<", "<=", ">", ">=",
					"(", ")", ",", ";", ".", ":=", "begin", "end", "if", "then", "while", "do",
					"call", "const", "var", "procedure", "write", "read", "else"
				};
					
void scanner(char *fileName);
void encoder(listyString* inputHead, lexToken *lexTokenHead, FILE *ofp);
listyString *intEncoder(listyString *inputHead, FILE *ofp);
listyString *wordVarEncoder(listyString *inputHead, lexToken *lexTokenHead, FILE *ofp);
listyString *symEncoder(listyString *inputHead, lexToken *lexTokenHead, FILE *ofp);
void *strorelexValue(lexToken *lexTokenHead ,char* lexme, int token, int error);
void printFunction(lexToken *lexTokenHead, FILE ofp, int type);

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
	
	listyString *inputHead, *newNode, *prevNode, *temporaryListyHead;

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
	temporaryListyHead = inputHead;
	
	while(temporaryListyHead != NULL){
		
		printf("inside while Input: %c\n",temporaryListyHead->c);
		temporaryListyHead = temporaryListyHead->next;		
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
	lexToken *lexTokenHead;
	lextokenHead = malloc(sizeof(lexToken));
	
	if(inputHead == NULL){
			
			printf("listyString is NULL\n");
			fflush( stdout );
			exit(0);
	}
	
	while(inputHead != NULL){
		
		if(isalpha(inputHead->c ) != 0){
				
			printf("wordVarEncoder\n");
			fflush( stdout );
			inputHead = wordVarEncoder(inputHead, lexTokenHead, ofp);
		}
		else if(isdigit(inputHead->c ) != 0){
			
			printf("intEncoder\n");
			fflush( stdout );
			inputHead = intEncoder(inputHead, lexTokenHead, ofp);
		}
		
		else{
			
			printf("SymEncoder\n");
			fflush( stdout );
			inputHead = symEncoder(inputHead, lexTokenHead, ofp);	
			
		}	
	}	
	
	printFunction(lexTokenHead, ofp, 1);
	printFunction(lexTokenHead, ofp, 2);
}

listyString *wordVarEncoder(listyString *inputHead, lexToken *lexTokenHead, FILE *ofp){
	
	printf("wordVarDecoder1\n");
	fflush(stdout);
	int i = 0, j = 0, strLength;
	
	char *bufferChar;
	listyString *temporaryListyHead;
	
	if(inputHead == NULL){
	
		//printf("inputHead NULL\n");
		return NULL;
	}
		
	printf("wordVarDecoder2\n");
	fflush(stdout);
		
	temporaryListyHead = inputHead;
	
	//printf("wordVarDecoder3\n");
	fflush(stdout);
	
	strLength = 0;
		
	while((isdigit(temporaryListyHead->c) != 0) || (isalpha(temporaryListyHead->c ) != 0)){
		
			//printf("wordVarDecoder4\n");
			fflush(stdout);
			temporaryListyHead = temporaryListyHead->next;	
			strLength++;
			
			if(temporaryListyHead == NULL){	
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
	temporaryListyHead = inputHead;
	

	for( i = 0; i < strLength; i++){
		
		//printf("wordVarDecoder6\n");
		fflush(stdout);
		bufferChar[i] = temporaryListyHead->c;
		temporaryListyHead = temporaryListyHead->next;
		//printf("bufferChar: %c\n",bufferChar[i]);
		fflush(stdout);
	}	
	
	if(strLength <= IDENTIFIER_MAX_LENGTH){
		//printf("wordVarDecoder7\n");
		fflush(stdout);
		for(i = 0;i < TABLE_SIZE; i++){
		
			if(strcmp(bufferChar,table[i]) == 0){
				
				storeLexTokenValue(lexTokenHead, bufferChar, i,0);
				printf("%d %s\n",i,bufferChar);
				//fprintf(ofp, "%d %s\n", i, bufferChar);
				return temporaryListyHead;
			}			
		}		
		
		if(i = TABLE_SIZE){
			storeLexTokenValue(lexTokenHead, bufferChar, 2,0);
			printf("2 %s\n",bufferChar);
			//fprintf(ofp, "2 %s\n", bufferChar);
		}
	}
	else{
			//printf("wordVarDecoder8\n");
			fflush(stdout);
			
			storeLexTokenValue(lexTokenHead, bufferChar, 2,1);
			printf("error:Identifier too long %s",bufferChar);
			//fprintf(ofp, "error:Identifier too long %s", bufferChar);
			//return temporaryListyHead;
	}	
	
	return temporaryListyHead;
}

listyString *intEncoder(listyString *inputHead, lexToken *lexTokenHead, FILE *ofp){
	
	printf("intDecoder\n");
	fflush(stdout);
	int i, j,strLength;
	
	char *bufferInt;
	listyString *temporaryListyHead;
	
	if(inputHead == NULL){
		
		return NULL;
	}
	
	temporaryListyHead = inputHead;
	
	strLength = 0;
	
	while((isdigit(temporaryListyHead->c) != 0) || (isalpha(temporaryListyHead->c ) != 0)){
		
			//printf("intDecoder2\n");
			fflush(stdout);
			temporaryListyHead = temporaryListyHead->next;	
			
			strLength++;
			
			if(temporaryListyHead == NULL){	
				break;		
			}			
	}
	
	if(strLength == 0){
		
		return NULL;
	}
	else{
		
		//printf("strLength = %d\n",strLength);
		
	}
	
	temporaryListyHead = inputHead;

	bufferInt = malloc(strLength * sizeof(char));
	
	for( i = 0; i < strLength; i++){

		//printf("intDecoder3\n");
		fflush(stdout);
		bufferInt[i] = temporaryListyHead->c;
		temporaryListyHead = temporaryListyHead->next;
		fflush(stdout);
	}	
	
	for(i = 0; i < strLength; i++){
		
		if (isdigit(bufferInt[i]) ==  0){
		
			storeLexTokenValue(lexTokenHead, bufferChar, 3,3);
			printf("error invalid character: %s\n", bufferInt);
			//fprintf(ofp, "error invalid character: %s\n", bufferInt);
			//return temporaryListyHead;		
		}
	}
	
	if(strLength <= NUMBER_MAX_LENGTH){	
	
		//printf("intDecoder4\n");
		fflush(stdout);
		printf("3");
		//fprintf(ofp, "3");
		
		for(i = 0;i < strLength; i++){
			
			printf("%c", bufferInt[i]);
			//fprintf(ofp, "%c", bufferInt[i]);
		}		
		
		storeLexTokenValue(lexTokenHead, bufferInt, 3,0);
		
		printf("\n");
		//fprintf(ofp,"\n");
		return temporaryListyHead;
	}
		
	else{
		storeLexTokenValue(lexTokenHead, bufferInt, 3,4);
		printf("ERROR:number too long ");
		//fprintf(ofp, "ERROR:number too long ");
	}
	
	return temporaryListyHead;
}

listyString *symEncoder(listyString *inputHead, FILE *ofp){
	printf("symDecoder\n");
	fflush(stdout);
	
	int i = 0;
	char *bufferSym, *nextBufferSym;;
	listyString *temporaryListyHead;
				
	temporaryListyHead = inputHead;
		
	printf("symDecoder2\n");
	fflush(stdout);
	bufferSym = malloc(2 * sizeof(char));
	nextBufferSym = malloc(2 * sizeof(char));
	
	printf("symDecoder3\n");
	fflush(stdout);
	
	bufferSym[0] = temporaryListyHead->c;
	bufferSym[1] = '\0';
	
	printf("symDecoder4\n");
	fflush(stdout);
	
	if(isspace(*bufferSym) != 0){
		printf("temporaryListyHead is space\n");
		fflush(stdout);
		
		return temporaryListyHead->next;
	}

	else if(temporaryListyHead->next != NULL && strcmp(bufferSym,"<") == 0 || strcmp(bufferSym,">") == 0 || strcmp(bufferSym,"!") == 0){
		printf("symDecoder5\n");
		fflush(stdout);
		nextBufferSym[0] = temporaryListyHead->next->c;
		nextBufferSym[1] = '\0';
		
		
		if(strcmp(nextBufferSym,"=") == 0){
			
			bufferSym[1] = nextBufferSym[0];
			temporaryListyHead = temporaryListyHead->next;
		}				
	}
		
	else if((temporaryListyHead->next != NULL) && strcmp(bufferSym,"/") == 0){
		
		printf("symDecoder6\n");
		fflush(stdout);
		nextBufferSym[0] = temporaryListyHead->next->c; 
		
		if(strcmp(nextBufferSym,"*") == 0){
			
			printf("found begining of comment\n");
			temporaryListyHead = temporaryListyHead->next;
					
			while(temporaryListyHead->next != NULL){
				
				bufferSym[0] = temporaryListyHead->next->c;
				bufferSym[1] = '\0';
				
				printf("In comment: %s\n",bufferSym);
				
				if((strcmp(bufferSym, "*") == 0) && (temporaryListyHead->next != NULL)){
					
					temporaryListyHead = temporaryListyHead->next;
					
					bufferSym[1] = temporaryListyHead->next->c;
					
					if(strcmp(bufferSym, "*/") == 0){
						
						temporaryListyHead = temporaryListyHead->next;
						
						printf("found end of comment\n");
						return temporaryListyHead->next;	
						
					}		
				}									
				temporaryListyHead = temporaryListyHead->next;
			}
			printf("Invalid comment\n");
			return NULL;
		}
	}
	
	for(i = 0; i < TABLE_SIZE; i++){
		
		//printf("symDecoder7\n");
		fflush(stdout);
		if(strcmp(bufferSym,table[i]) == 0){
			
			storeLexTokenValue(lexTokenHead, bufferSym, i,0);
			printf("%d %s\n", i, bufferSym);
			//fprintf(ofp, "%d %s\n", i, bufferSym);
			return temporaryListyHead->next;
		}						
	}
	if(i == TABLE_SIZE){
		storeLexTokenValue(lexTokenHead, bufferSym, i,5);
		printf("error Invalid symbol: %s\n", bufferSym);
		//fprintf(ofp, "error Invalid symbol: %s\n", bufferSym);
	}
	return temporaryListyHead->next;
}

 void *strorelexValue(lexToken *lexTokenHead ,char* lexme, int token, int error){

	if(lexTokenHead == NULL){
		
		printf("strorelexValueerror lextoken head null\n");	
		exit(0);
	}
	
	while (lexTokenHead != NULL){
				
				lexTokenHead = lexTokenHead->next;				
			}
			
			lexTokenHead->lexme malloc(sizeof(lexToken));
			lexTokenHead->lexme = malloc(sizeof(char));
			
			lexTokenHead->lexme = lexme;
			lexTokenHead->token = token;
			lexTokenHead->error = error;
}

void printFunction(lexToken *lexTokenHead, FILE ofp, int type){
	
	lexToken *lexTokenHead;
	lexTokenHead = lexTokenHead;
	
	if(lexTokenHead == NULL){
		
		printf(" printFunction lexTokenHead is null\n");	
		exit(0;)
	}
	
	
	if(type == 1){
		
		while(lexTokenHead != NULL){
			
			
			if(lextokenHead->error > 0){
				
				/*
				switch(lexTokenHead->error){
					
					case (1):
						
					break;										
				}
				*/
				fprintf(ofp, "printFunction error:%s \t %d\n", lexTokenHead->lexme, lexTokenHead->token)
			}
				
			else{

					fprintf(ofp, "%s \t %d\n",lexTokenHead->lexme, lexTokenHead->token);
			}		
		}
	}
	else if(type == 2){
		
		while(lexTokenHead != NULL){
			
			
			if(lextokenHead->error > 0){
				/*
				switch(lexTokenHead->error){
					
					case (1):
						
					break;										
				}
				*/
				fprintf(ofp, "printFunction error:%s \t %d\n", lexTokenHead->lexme, lexTokenHead->token)
			}
				
			else{
					fprintf(ofp, "%d ",lexTokenHead->lexme, lexTokenHead->token);
					
					if(lexTokenHead->token == 2){
						
						fprintf(ofp, "%s ",lexTokenHead->lexme);
					}
			}			
		}		
	}		
}
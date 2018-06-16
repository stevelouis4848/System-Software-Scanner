// Name: Steve Louis
// Class: COP 3402 summer 2018
// Assignment: Homework #2 (Scanner)
// 06/15/2018

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int IDENTIFIER_MAX_LENGTH = 11;
int NUMBER_MAX_LENGTH = 5;
int TABLE_SIZE = 34;

typedef struct listyString{
							int c;
							struct listyString *next;						
}listyString;

char *table[] = {"0", "\0", "2", "3", "+", "-", "*", "/", "%", "=", "!=", "<", "<=", ">", ">=",
					"(", ")", ",", ";", ".", ":=", "begin", "end", "if", "then", "while", "do",
					"call", "const", "var", "procedure", "write", "read", "else"
				};
					
void scanner(char *fileName);
void encoder(listyString* inputHead, FILE *ofp, FILE *ofp2);
listyString *intEncoder(listyString *inputHead,FILE *ofp, FILE *ofp2);
listyString *wordVarEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2);
listyString *symEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2);

int main(int argc, char **argv){
	
	int i;

	for(i = 1;i < argc; i++){
		
		scanner(argv[i]);				
	}
	return 0;
}

void scanner(char *fileName){
	
	FILE *ifp, *ofp, *ofp2;
	int buffer;
	listyString *inputHead, *newNode, *prevNode, *temporaryHead;
	
	if(fileName == NULL){
		
		fprintf(ofp,"Invalid file name");
		exit(0);			
	}
	
	inputHead = malloc(sizeof(listyString));
		
	ifp = fopen(fileName,"r");
	ofp = fopen("outputFile.txt","w");
	ofp2 = fopen("outputFile2.txt","w");
	
	if (ifp == NULL || ofp == NULL){
		
		fprintf(ofp, "Invalid file pointers");
		remove("outputFile2.txt");
		exit(0);
	}

	fprintf(ofp, "Source Program:%s\n",fileName);
	
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
		fprintf(ofp, "%c", buffer);
	}
	
	
	prevNode->next = NULL;
	temporaryHead = inputHead;
	
	while(temporaryHead != NULL){
		
		temporaryHead = temporaryHead->next;		
	}
	
	fprintf(ofp,"\n\nLexeme Table:\nLexme\t\ttoken type\n" );
	
	encoder(inputHead, ofp, ofp2);
	
	fclose(ofp2);
	
	ofp2 = fopen("outputFile2.txt","r");
	
	fprintf(ofp,"\nLexeme List\n" );
	
	while((buffer = fgetc(ofp2)) != EOF){
				
			fprintf(ofp,"%c",buffer);				
	}
	fprintf(ofp,"\n");	
	fclose(ofp);
	
	ofp = fopen("outputFile.txt", "r");
	
	while((buffer = fgetc(ofp)) != EOF){
				
			printf("%c",buffer);			
	}
	
	fclose(ifp);
	fclose(ofp);
	fclose(ofp2);
	
	remove("outputFile2.txt");
}

void encoder(listyString* inputHead, FILE *ofp, FILE *ofp2){
	
	int i, j;
	char *bufferChar, *prevBufferChar;
	int *bufferInt, *prevbufferInt;
	
	if(inputHead == NULL){

			remove("outputFile2.txt");
			return;
		}
	
	while(inputHead != NULL){
		
		if(isalpha(inputHead->c ) != 0){
				
			inputHead = wordVarEncoder(inputHead, ofp, ofp2);
		}
		else if(isdigit(inputHead->c ) != 0){
			
			inputHead = intEncoder(inputHead, ofp, ofp2);
		}
		
		else{
			
			inputHead = symEncoder(inputHead, ofp, ofp2);				
		}	
	}	
}

listyString *wordVarEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2){
	
	int i = 0, j = 0, strLength;
	
	char *bufferChar;
	listyString *temporaryHead;
	
	if(inputHead == NULL){
	
		return NULL;
	}
				
	temporaryHead = inputHead;
	
	strLength = 0;
		
	while((isdigit(temporaryHead->c) != 0) || (isalpha(temporaryHead->c ) != 0)){
		
			temporaryHead = temporaryHead->next;	
			strLength++;
			
			if(temporaryHead == NULL){	
				break;		
			}			
	}
	
	if(strLength == 0){
		
		return NULL;
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
				
				fprintf(ofp, "%s\t\t %d\n", bufferChar, i);
				fprintf(ofp2, "%d ", i);
				return temporaryHead;
			}			
		}		
		
		fprintf(ofp, "%s\t\t2\n", bufferChar);			
		fprintf(ofp2, "2 %s ", bufferChar);
		return temporaryHead;
		
	}
	else{
			fprintf(ofp, "error:Identifier too long %s", bufferChar);
			return NULL;
	}	
}

listyString *intEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2){
	
	int i, j,strLength;
	
	char *bufferInt;
	listyString *temporaryHead;
	
	if(inputHead == NULL){
		
		return NULL;
	}
	
	temporaryHead = inputHead;
	
	strLength = 0;
	
	while((isdigit(temporaryHead->c) != 0) || (isalpha(temporaryHead->c ) != 0)){
		
			
			temporaryHead = temporaryHead->next;	
			
			strLength++;
			
			if(temporaryHead == NULL){	
				break;		
			}			
	}
	
	if(strLength == 0){
		
		return NULL;
	}
	
	temporaryHead = inputHead;

	bufferInt = malloc(strLength * sizeof(char));
	
	for( i = 0; i < strLength; i++){

		bufferInt[i] = temporaryHead->c;
		temporaryHead = temporaryHead->next;
	}	
	
	for(i = 0; i < strLength; i++){
		
		if (isdigit(bufferInt[i]) ==  0){
			
			fprintf(ofp, "error invalid character: %s\n", bufferInt);
			return NULL;		
		}
	}
	
	if(strLength <= NUMBER_MAX_LENGTH){	
		
		fprintf(ofp2, "3 ");
		
		for(i = 0;i < strLength; i++){
			
			fprintf(ofp, "%c", bufferInt[i]);
			fprintf(ofp2, "%c", bufferInt[i]);
		}				
		fprintf(ofp2, " ");
		fprintf(ofp, "\t\t3\n");
		
		return temporaryHead;
	}
		
	else{
		
		fprintf(ofp, "ERROR:number too long ");
		return NULL;
	}
	
	return temporaryHead;
}

listyString *symEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2){

	int i = 0;
	char *bufferSym, *nextBufferSym;;
	listyString *temporaryHead;
				
	temporaryHead = inputHead;
		
	bufferSym = malloc(2 * sizeof(char));
	nextBufferSym = malloc(2 * sizeof(char));
	
	bufferSym[0] = temporaryHead->c;
	bufferSym[1] = '\0';
	
	if(isspace(*bufferSym) != 0){
	
		return temporaryHead->next;
	}

	else if(temporaryHead->next != NULL && strcmp(bufferSym,":") == 0 || strcmp(bufferSym,"<") == 0 
				|| strcmp(bufferSym,">") == 0 || strcmp(bufferSym,"!") == 0){

		nextBufferSym[0] = temporaryHead->next->c;
		nextBufferSym[1] = '\0';
		
		
		if(strcmp(nextBufferSym,"=") == 0){
			
			bufferSym[1] = nextBufferSym[0];
			temporaryHead = temporaryHead->next;
		}				
	}
		
	else if((temporaryHead->next != NULL) && strcmp(bufferSym,"/") == 0){
		
		nextBufferSym[0] = temporaryHead->next->c; 
		
		if(strcmp(nextBufferSym,"*") == 0){

			temporaryHead = temporaryHead->next;
					
			while(temporaryHead->next != NULL){
				
				bufferSym[0] = temporaryHead->next->c;
				bufferSym[1] = '\0';
				
				
				if((strcmp(bufferSym, "*") == 0) && (temporaryHead->next != NULL)){
					
					temporaryHead = temporaryHead->next;
					
					bufferSym[1] = temporaryHead->next->c;
					
					if(strcmp(bufferSym, "*/") == 0){
						
						temporaryHead = temporaryHead->next;
						
						return temporaryHead->next;	
						
					}		
				}									
				temporaryHead = temporaryHead->next;
			}
			fprintf(ofp, "Invalid comment\n");
			return NULL;
		}
	}
	
	for(i = 0; i < TABLE_SIZE; i++){
		
		if(strcmp(bufferSym,table[i]) == 0){
	
			fprintf(ofp, "%s\t\t %d\n",bufferSym, i);
			fprintf(ofp2, "%d ", i);
			return temporaryHead->next;
		}						
	}
	fprintf(ofp, "error Invalid symbol: %s\n", bufferSym);
	return NULL;
}
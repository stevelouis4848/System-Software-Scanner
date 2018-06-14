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
int MAX_STRING_LENGTH =  2000;

char *table[] = {"0","\0","2","3","+","-","*","/","%","=","!=","<","<=",">",">=",
					"(",")",",",";".":=","begin","end","if","then","while","do",
					"call","const","var","procedure","write","read","else"
				};
					
void scanner(char *fileName);
void encoder(char* buffer, FILE *ofp);
void symEncoder(char *buffer, FILE *ofp);
void wordVarTable(char *temporaryHead, char *bufferChar,FILE *ofp, int length);

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
	char *buffer[MAX_STRING_LENGTH];
	int strLength;
		
	ifp = fopen(fileName,"r");
	ofp = fopen("outputFile.txt","w");
	//ofp2 = ("r");

	
	while(fscanf(ifp, "%s", buffer ) != EOF){		
		
		printf("inside while Input: %s/n",buffer);
		
		strLength = strlen(buffer);
		if(strcmp(buffer, "\\") == 0){
			
			while( (c = fgetc(ifp)) != EOF && c != "\n" ){
			
				fgetc(ifp);
			}
		}
			
		else if(strcmp(buffer, "/*") == 0){
			
			while(fscanf(ifp, "%s", buffer ) != EOF){
				if(strcmp(buffer,"*/") == 0){
					break;
				}			
			}		
		}
		
		printf("inside while Input: %S/n",buffer);
		encoder(buffer,ofp);		
	}

}

void encoder(char *buffer, FILE *ofp){
	printf("Encoder: %s\n",buffer);
	int i, j,strLength;
	
	strLength = strlen(buffer);
	
	if(*buffer == NULL){
		
		printf("buffer is NULL\n");
		fflush( stdout );
		return;
		
	}
	if(isalpha(buffer[0] ) != 0){
		
		printf("wordVarEncoder\n");		
		fflush( stdout );
		
		for (i = 1; i < strLength && buffer[i] != NULL; i++){
			
			if((isalpha(buffer[i]) == 0) || (isdigit(buffer[i] == 0))){
				
				printf("Error:variable name contains improper charater");
				return;
			}
		}
		for(i = 0; i < TABLE_SIZE; i++){
			
			if(strcmp(buffer, table[i]) == 0){
				
				printf(" %d ",i);
				printf("%s\n",buffer);
				return;				
			}
			else{
				
				printf("2 %s\\n",buffer);
				
			}			
		}
		return;
		//wordVarEncoder(buffer, ofp);
	}
	
	else if(isdigit(buffer[0] ) != 0){
		
		printf("intEncoder\n");
		fflush( stdout );
		for (i = 0; i < strLength; i++){
			
			if(idigit(buffer[i]) == 0 ){
				
				printf("Error:Number contains improper charater");
				return;
			}
		}
		
		if(strLength <= MAX_STRING_LENGTH){
		
			printf("3 %s\n",buffer);
		}
		else{
			printf("Error:Number exceeds max length\n");			
		}
		//intEncoder(buffer, ofp);
	}
	
	else{
		
		printf("SymEncoder\n");
		fflush( stdout );
		
		checkTable(buffer, ofp);
		//symEncoder(buffer, ofp);	
		
	}	 
}

check


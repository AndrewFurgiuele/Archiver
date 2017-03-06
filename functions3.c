#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "header3.h"


//gets size of file
int getSize(char* file){
	/*
	goes to end of file
	gets current file pointer location
	rewinds file pointer
	*/
	
	FILE *fp;
	
	if((fp = fopen(file, "rb")) == NULL){
		printf("Cannot open file \n");
	}


	fseek(fp, 0, SEEK_END);
	unsigned int numberBytes = ftell(fp);
	rewind(fp);

	fclose(fp);

	return numberBytes;
	
}
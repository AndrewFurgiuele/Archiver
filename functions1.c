#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "header1.h"

//-a function
void archive(char** fileNames, int numFiles, char* archiveName){
		/*
		For every file, reads bytes and creates archvie according to assignment 
		*/
		
		FILE *fp;
		FILE *arc;
		
		unsigned int numFilesUI = numFiles-3;
		if((arc = fopen(archiveName, "wb")) == NULL){
				printf("Cannot open file \n");
			}
			
		fwrite(&numFilesUI, sizeof(int), 1, arc);

		int	i =3;
		for(i; i < numFiles;i++){
				
			char* fName = fileNames[i];
			char fileNameLength = strlen(fName);
			char temp[fileNameLength+1];
			int j =0;
			for(j;j< fileNameLength+1;j++){
				temp[j]= fName[j];
			}
			temp[fileNameLength+1]= '\0';
					
		
			if((fp = fopen(fName, "rb")) == NULL){
				printf("Cannot open file \n");
			}
			
			fseek(fp, 0, SEEK_END);
			unsigned int numberBytes = ftell(fp);
			rewind(fp);
			
			char* bytes = malloc(numberBytes +1);
			fread(bytes, numberBytes, 1, fp);
			
			
			fwrite(&fileNameLength, sizeof(char),1, arc);
			fwrite(temp, fileNameLength+1, 1, arc);
			fwrite(&numberBytes, sizeof(unsigned int), 1, arc);
			fwrite(bytes, numberBytes, 1, arc);
			
			
			fclose(fp);
			
	}	
	
	
	fclose(arc);
	
}

//-u function
void unarchive(char* archiveFile){
	/*
	Does opposite of archive function
	Breaks apart archive into different files as specified by assignment
	*/
	
	
	FILE *fp;
		
	if((fp = fopen(archiveFile, "rb")) == NULL){
				printf("Cannot open file \n");
		}
		
	unsigned int const numFiles =0;	
	fread(&numFiles, 4, 1, fp);
		
	int i =0;
	char nameLength;
	char* name;
	unsigned int fileSize;
	char* bytes;
	FILE* newFile;
	
	int nF = numFiles;
	
	for(i; i < nF;i++){
			
		fread(&nameLength, sizeof(char),1, fp);
		nameLength++;
		name = malloc(nameLength);
		fread(&name,nameLength,1, fp);
		fread(&fileSize, sizeof(unsigned int), 1, fp);
		int x = fileSize;
		
		if((newFile = fopen(&name, "wb")) == NULL){
				printf("Cannot open file \n");
		}
		
		bytes = malloc(fileSize);
		fread(&bytes, fileSize,1, fp);
		
	
		fwrite(&bytes, x,1,newFile);
		fclose(newFile);
			
		
		
	}
	
	
		
		
		
		fclose(fp);
		
	
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "header2.h"



//-l function
void listStats(char* archiveFile){
	/*
	Opens file
	Goes through and prints name and size
	closes file
	*/


	FILE *fp;
	
	if((fp = fopen(archiveFile, "rb")) == NULL){
				printf("Cannot open file \n");
		}


		
	fseek(fp, 0, SEEK_END);
	unsigned int size = ftell(fp);
	rewind(fp);
				
	unsigned int numberFiles;	
	fread(&numberFiles, sizeof(unsigned int), 1, fp);
	
	
	printf("Size of Archive file: %d bytes\n", size);
	printf("Number of files in Archive file: %d files\n", numberFiles);
	
	
	int i =0;
	char nameLength;
	char* name;
	unsigned int fileSize;
	for(i; i < numberFiles;i++){
		
		fread(&nameLength, sizeof(char),1, fp);
		nameLength++;
		name = malloc(nameLength);
		fread(&name,nameLength,1, fp);
		fread(&fileSize, sizeof(unsigned int), 1, fp);
		fseek(fp, fileSize, SEEK_CUR);
		
		printf("File Name: %s Size: %u\n", &name, fileSize); 
		
	}

}


//-v function
void verifiyArchive(char** fileNames, int numFiles, char* archiveName){
	/*
	Creates a new archive called new_archive
	goes step by step and checks the bytes of the new archive with the given one
	deltes new_archive
	*/
	
	
		FILE *fp;
		FILE *arc;
		
		unsigned int numFilesUI = numFiles-3;
		if((arc = fopen("new_archive", "wb")) == NULL){
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
	
	FILE* arcOrig;
	FILE* arcNew;
	
	if((arcNew = fopen("new_archive", "rb")) == NULL){
				printf("Cannot open file \n");
			}
			
			
	if((arcOrig = fopen(archiveName, "rb")) == NULL){
				printf("Cannot open file \n");
			}		
	
	int j =0;
	
	fseek(arcOrig, 0, SEEK_END);
	unsigned int sizeArcOrig = ftell(arcOrig);
	rewind(arcOrig);
			
	fseek(arcNew, 0, SEEK_END);
	unsigned int sizeArcNew = ftell(arcNew);
	rewind(arcNew);		
	

	if(sizeArcNew != sizeArcOrig){
		int diff = fabs(sizeArcNew - sizeArcOrig);
		printf("Archive is missing %d bytes\n", diff);
	}else{
		int corrupt = 0;
		for(j;j < sizeArcNew;j++){
			char a;
			char b;
			fread(&a, 1,1, arcOrig);
			fread(&b,1,1, arcNew);

			
			if(a != b){
				puts("Archive is Corrupted");
				corrupt =1;
				break;
			}
		}
		
		if( corrupt ==0){
		puts("Archive verified");
		}
	}
	
	
	


	
	fclose(arcOrig);
	fclose(arcNew);
	remove("new_archive");
	
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "header1.h"
#include "header2.h"
#include "header3.h"
#include "constants.h"

//main function
int main(int argc, char** argv)  {
	//checks the flag and calls correct function
	//checks for correct amount of arguements according to flag
	if(strcmp(argv[1], "-a")==0){
		if(argc >= 4){
		archive(argv, argc, argv[2]);
		}
		else if(argc == 3){
			puts("-a flag specified by no files given");
		}
		else{
			puts("Incorrect number of command line arguments for this flag");
		}
	}
	else if(strcmp(argv[1], "-u")==0){
		if(argc == 3){
			unarchive(argv[2]);
		}else{
			puts("Incorrect number of command line arguments for this flag");
		}
	}
	else if(strcmp(argv[1], "-l")==0){
		if(argc == 3){ 
			listStats(argv[2]);
			
		}else{
			puts("Incorrect number of command line arguments for this flag");
		}
	}
	
	else if(strcmp(argv[1], "-v")==0){
		if(argc >= 4){
			verifiyArchive(argv, argc, argv[2]);
		}else{
			puts("Incorrect number of command line arguments for this flag");
		}
	}else{
		puts("incorrect flag");
	}


	return 1;
}




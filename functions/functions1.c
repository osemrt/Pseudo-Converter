#include "functions.h"

int checkArg(int argc, char** argv) {
	// let's control the number of the arguments.
	if (argc != 3) {
		printf("Please, check the number of your arguments!");
		return FALSE;
	}

	// let's control the source code extension
	char* fileExtension2 = argv[2] + strlen(argv[2]) - 2;
	if (strcmp(fileExtension2, ".c") != 0) {
		printf("Please, enter the right format in order to create the source code!");
		return FALSE;
	}

	return TRUE;
}

int openFile(char** argv, FILE** fp) {
	// let's open the pseudo text file.
	*fp = fopen(argv[1], "r");
	if (*fp == NULL) {
		printf("An error has occured while the opening the pseudo file!");
		return FALSE;
	}

	return TRUE;
}

int createFile(char**argv, FILE** fp) {
	// lets' create our source file.
	*fp = fopen(argv[2], "w");
	if (*fp == NULL) {
		printf("An error has occured while the creating the source file!");
		return FALSE;
	}

	return TRUE;
}



// read a string from the stream and return it.
char* readString(FILE* fp) {
	char buffer[20];
	fscanf(fp, "%s", buffer);
	char* s = malloc(sizeof(char)*(strlen(buffer) + 1));
	// every time lowecase
	strcpy(s, strLower(buffer));
	return s;

}


int closeStreams(FILE* fp1, FILE* fp2) {
	// let's close all streams before non-terminating the program.
	if (fclose(fp1) + fclose(fp2) != 0) {
		printf("An error has occured while the closing the streams!");
		return FALSE;
	}

	return TRUE;
}

// convert a string to uppercase.
char* strUpper(char* s) {
	char* buffer = malloc(sizeof(char)*(strlen(s) + 1));
	char* upper = buffer;
	while (*s != '\0') {
		if (*s >= 'a' && *s <= 'z') {
			*buffer = *s - 32;
		}
		else {
			*buffer = *s;
		}
		s++; buffer++;
	}
	*buffer = NULL;
	return upper;
}

// convert a string to lowecase.
char* strLower(char* s) {
	char* buffer = malloc(sizeof(char)*(strlen(s) + 1));
	char* lower = buffer;
	while (*s != '\0') {
		if (*s >= 'A' && *s <= 'Z') {
			*buffer = *s + 32;
		}
		else {
			*buffer = *s;
		}
		s++; buffer++;
	}
	*buffer = NULL;
	return lower;
}



// sum up the ascii of all characters in a string.
int asciiVal(char*s) {

	int count = 0;
	while (*s != NULL) {
		count += *s;
		s++;
	}

	return count;
}

// to skip unwanted characters.
void skipCh(FILE* fp) {
	char buffer;
	do {
		buffer = fgetc(fp);
	} while (buffer != '“'&& buffer != '”'&&buffer != ' '&&buffer != '"'&&buffer != '$');
	fseek(fp, +1, SEEK_CUR);

}





// let's print the source code.
void printFile(FILE* fp) {

	while (!feof(fp)) {
		printf("%c", fgetc(fp));
	}

}
#ifndef functions
#define functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define TRUE 1
#define FALSE 0

struct variableInfo {
	char* datatype;
	char* name;
	struct variableInfo* next; };


void(*func[500])(FILE*, FILE*);
extern struct variableInfo* HEAD;


// functions in the group1.
int checkArg(int argc, char** argv);
int openFile(char** argv, FILE** fp);
int createFile(char**argv, FILE** fp);
int closeStreams(FILE* fp1, FILE* fp2);
char* readString(FILE* fp);
int asciiVal(char*s);
char* strUpper(char* s);
char* strLower(char* s);
void printFile(FILE* fp);
void skipCh(FILE* fp);

// functions in the group2.
void assignFunctions();
void VARIABLE(FILE* fp1, FILE* fp2);
void PROCEDURE(FILE* fp1, FILE* fp2);
void BEGIN(FILE* fp1, FILE* fp2);
void END(FILE* fp1, FILE* fp2);
void RETURN(FILE* fp1, FILE* fp2);
void FOR(FILE* fp1, FILE* fp2);
void WHILE(FILE* fp1, FILE* fp2);
void IF(FILE* fp1, FILE* fp2);
void PRINT_LINE(FILE* fp1, FILE* fp2);
void GET_VAL(FILE* fp1, FILE* fp2);
void c(FILE* fp1, FILE* fp2);
void f(FILE* fp1, FILE* fp2);
void i(FILE* fp1, FILE* fp2);
void l(FILE* fp1, FILE* fp2);
void d(FILE* fp1, FILE* fp2);
void ld(FILE* fp1, FILE* fp2);
void file(FILE* fp1, FILE* fp2);
void cp(FILE* fp1, FILE* fp2);
void fp(FILE* fp1, FILE* fp2);
void ip(FILE* fp1, FILE* fp2);
void lp(FILE* fp1, FILE* fp2);
void dp(FILE* fp1, FILE* fp2);
void PARSING(FILE* fp2, char* var);

// functions in the group3.
char* formatSpecifier(char specifier);
void initial(FILE* fp1, FILE* fp2);
void condition(FILE* fp2, char* condition);
void includeLibraries(FILE* fp1);
void variableList(struct variableInfo** head, char* type, char* variable);
void printLinkedList();

#endif
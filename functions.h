#ifndef functions
#define functions

#define TRUE 1
#define FALSE 0


int checkArg(int argc, char** argv);
int openFile(char** argv, FILE** fp);
int createFile(char**argv, FILE** fp);
int closeStreams(FILE* fp1, FILE* fp2);

char* readString(FILE* fp);



#endif
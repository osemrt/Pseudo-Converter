#include <stdio.h>
#include "functions.h"


int main(int argc, char* argv[]) {

	// let's check the arguments conditions.
	if (checkArg(argc, argv) == FALSE)
		return 0;

	// let's check that the file is exists or not, if it is exist, let's give file address to fp stream.
	FILE* fp1 = NULL;
	if (openFile(argv, &fp1) == FALSE)
		return 0;

	// let's check that the file is created or not, if it is created, let's give file address to fp stream.
	FILE* fp2 = NULL;
	if (createFile(argv, &fp2) == FALSE)
		return 0;


	includeLibraries(fp2);
	assignFunctions();
	char*s; int k; long cursor;
	while (!feof(fp1)) {

		cursor = ftell(fp1);
		s = readString(fp1);
		k = asciiVal(s) % 513;
		if (func[k] == NULL) {
			fseek(fp1, cursor, SEEK_SET);
			(*func[000])(fp1, fp2);
		}
		else {
			(*func[k])(fp1, fp2);
		}
	}

	initial(fp2);



	if (closeStreams(fp1, fp2) == FALSE)
		return 0;

	

	return 0;
}
#include "functions.h"

struct variableInfo* HEAD = NULL;


// let's print the format specifier to the fp stream.
char* formatSpecifier(char specifier) {
	specifier = toupper(specifier);

	switch (specifier) {
	case 73: return "%d";
		break;
	case 67: return "%c";
		break;
	case 70: return "%f";
		break;
	default: printf("An error has occurred while finding the specifier! ");
		break;
	}

	return specifier;
}

void condition(FILE* fp2, char* condition) {

	char  *variable1, *variable2, *type1, *type2, *sign, *arrName, *arrType, *arrVar, *arrVarType;
	variable1 = strtok(condition, " ");
	sign = strtok(NULL, " ");
	variable2 = strtok(NULL, " ");

	if (strcmp(sign, "EQUAL") == 0) {
		sign = "==";
	}
	else if (strcmp(sign, "NOT_EQUAL") == 0) {
		sign = "!=";
	}


	// the parsing of variable1 starts here.
	if (strstr(variable1, "[") != NULL) { // if first variable is an array.
		arrName = strtok(variable1, "_");
		arrType = strtok(NULL, "[");

		arrVar = strtok(NULL, "\0");
		arrVar = strtok(arrVar, "_");
		arrVarType = strtok(NULL, "]");

		//arrName++; // to pass the '('.
		fprintf(fp2, "(%s[%s]%s", arrName, arrVar, sign);


	}
	else {
		variable1 = strtok(variable1, "_");
		type1 = strtok(NULL, " ");
		variable1++;

		fprintf(fp2, "(%s %s", variable1, sign);

	}
	// the parsing of variable1 ends here.

	// the parsing of variable2 starts here.
	if (strstr(variable2, "[") != NULL) { // if second variable is an array.
		arrName = strtok(variable2, "_");
		arrType = strtok(NULL, "[");

		arrVar = strtok(NULL, "\0");
		arrVar = strtok(arrVar, "_");
		arrVarType = strtok(NULL, "]");

		fprintf(fp2, " %s[%s])", arrName, arrVar);


	}
	else {
		variable2 = strtok(variable2, "_");
		type2 = strtok(NULL, " ");
		type2[strlen(type2) - 1] = '\0'; // to pass the ')'.

		fprintf(fp2, " %s)", variable2);

	}
	// the parsing of variable2 ends here.


}



// let's create a linked list to store the variable name and their types.-> ERROR!
void variableList(struct variableInfo** head, char* type, char* variable) {


	if (HEAD != NULL) {
		struct variableInfo* temp = *head;
		while (((temp) != NULL) && (strcmp(temp->datatype, type) != 0 || strcmp(temp->name, variable) != 0)) {
			(temp) = (temp)->next;
		}
		if (temp == NULL) {
			struct variableInfo* buffer = (struct variableInfo*)malloc(sizeof(struct variableInfo));
			(buffer)->name = variable;
			(buffer)->datatype = type;
			(buffer)->next = NULL;

			struct variableInfo* temp = *head;
			while ((temp)->next != NULL) {
				(temp) = (temp)->next;
			}

			(temp)->next = buffer;

		}



	}
	else {
		struct variableInfo* buffer = (struct variableInfo*)malloc(sizeof(struct variableInfo));
		(buffer)->name = variable;
		(buffer)->datatype = type;
		(buffer)->next = NULL;

		*head = buffer;

	}



}


// let's add the necessary libraries to the source code.
void includeLibraries(FILE* fp1) {

	fseek(fp1, 0, SEEK_CUR);
	fprintf(fp1, "#include <stdio.h>\n ");


}


// let's print all variables with their types.-> ERROR!
void initial(FILE* fp1) {

	fseek(fp1, 48, SEEK_SET);
	struct variableInfo* p = HEAD;

	while (p != NULL) {
		if (*(p->datatype) == 'i') {
			char* type = "int";
			fprintf(fp1, "%s %s; \t", type, p->name);

		}

		if (*(p->datatype) == 'c') {
			char* type = "char";
			fprintf(fp1, "%s %s; \t", type, p->name);

		}

		if (*(p->datatype) == 'f') {
			char* type = "float";
			fprintf(fp1, "%s %s; \t", type, p->name);

		}

		p = p->next;
	}

	fprintf(fp1, "%s; \t", "int arr[100]");


}


// let's print all variables with their types.-> ERROR!
void printLinkedList() {

	struct variableInfo* p = HEAD;

	while (p != NULL) {
		printf("%s %s-> \n", p->datatype, p->name);
		p = p->next;
	}


}

#include "functions.h"

extern void(*func[500])(FILE*, FILE*) = { NULL };

void assignFunctions() {
	func[000] = VARIABLE;
	func[456] = PROCEDURE;
	func[4] = BEGIN;
	func[311] = END;
	func[159] = RETURN;
	func[327] = FOR;
	func[24] = WHILE;
	func[207] = IF;
	func[50] = PRINT_LINE;
	func[225] = GET_VAL;
	func[99] = c;
	func[102] = f;
	func[105] = i;
	func[108] = l;
	func[100] = d;
	func[208] = ld;
	func[416] = file;
	func[214] = fp;
	func[211] = cp;
	func[217] = ip;
	func[220] = lp;
	func[212] = dp;

}


void PARSING(FILE* fp2, char* var) {

	if (strstr(var, "[") != 0) {
		char* arrName = strtok(var, "[");
		char* arrVar = strtok(NULL, "]");

		arrName = strtok(arrName, "_");
		char* arrType = strtok(NULL, "\0");

		arrVar = strtok(arrVar, "_");
		char* arrVarType = strtok(NULL, "\0");

		fprintf(fp2, "%s[%s]", arrName, arrVar);

		variableList(&HEAD, arrVarType, arrVar);

	}
	else if (strstr(var, "_") != 0) {

		char* varName = strtok(var, "_");
		char* varType = strtok(NULL, "\0");
		variableList(&HEAD, varType, varName);
		fprintf(fp2, "%s", varName);
	}
	else {
		fprintf(fp2, "%s", var);
	}


}


void VARIABLE(FILE* fp1, FILE* fp2) {

	char* buffer = readString(fp1);
	PARSING(fp2, buffer);
	char* sign = readString(fp1);
	fputc('=', fp2);
	buffer = readString(fp1);
	PARSING(fp2, buffer);
	fprintf(fp2, ";\n");

}

void PROCEDURE(FILE* fp1, FILE* fp2) {

	char temp[30];
	long cur = ftell(fp1);
	int flag = 1;
	while (!feof(fp1) && flag) {
		fscanf(fp1, "%s", temp);
		if (strcmp(temp, "RETURN") == 0)
			flag = 0;
	}

	char* ret = readString(fp1), *retValueType;
	if (strcmp(ret, "void") == 0 || flag == 1) {
		fputs("\n\nvoid ", fp2);
	}
	else {
		retValueType = strtok(ret, "_");
		retValueType = strtok(NULL, "\0");
		func[asciiVal(retValueType)](fp1, fp2);
	}

	fseek(fp1, cur, SEEK_SET);

	char* functionName = strLower(readString(fp1));
	fprintf(fp2, "%s\n", functionName);

}

void BEGIN(FILE* fp1, FILE* fp2) {
	fputs("{\n                                                                                                                     \n", fp2);
	//printf("%d", ftell(fp2));
}

void END(FILE* fp1, FILE* fp2) {
	fputs("{\n", fp2);
}

void RETURN(FILE* fp1, FILE* fp2) {

	char* temp = readString(fp1);
	if (strcmp(temp, "void") != 0) {
		char* retVal = strtok(temp, "_");
		fprintf(fp2, "return %s;", retVal);
	}

}


void FOR(FILE* fp1, FILE* fp2) {

	char* loopVar = readString(fp1);
	char* loopVarType = strtok(loopVar, "_");
	loopVarType = strtok(NULL, "\0");

	variableList(&HEAD, loopVarType, loopVar);
	fprintf(fp2, "for(%s= ", loopVar);

	char* sign = readString(fp1);
	char* limit1 = readString(fp1);
	char* limit2 = strtok(limit1, ".");
	limit2 = strtok(NULL, " ");
	limit2++;

	fprintf(fp2, "%s; %s < ", limit1, loopVar);


	char* loopVar2 = strtok(limit2, "_");
	char* loopVar2Type = strtok(NULL, "\0");

	variableList(&HEAD, loopVar2Type, loopVar2);

	fprintf(fp2, "%s; %s++)\n", limit2, loopVar);
	loopVar = readString(fp1);

}

void WHILE(FILE* fp1, FILE* fp2) {
	char buffer[100], tmp;
	int i = 0;
	skipCh(fp1);
	do {
		tmp = fgetc(fp1);;
		buffer[i++] = tmp;
	} while (tmp != '\n');
	buffer[--i] = NULL;


	char *condition1, *condition2;

	if (strstr(buffer, "AND") != NULL) {
		condition1 = strtok(buffer, "AND"); // first condition
		condition2 = strtok(NULL, "DO");
		condition2 = strtok(NULL, "DO"); // second condition		

		fprintf(fp2, "%s", "while( ");
		condition(fp2, condition1);
		fprintf(fp2, "%s", " && ");
		condition(fp2, condition2);
		fprintf(fp2, "%s", " )\n");

	}
	else if (strstr(buffer, "OR") != NULL) {
		condition1 = strtok(buffer, "OR"); // first condition
		condition2 = strtok(NULL, "DO");
		condition2++; // second condition

		fprintf(fp2, "%s", "while( ");
		condition(fp2, condition1);
		fprintf(fp2, "%s", " || ");
		condition(fp2, condition2);
		fprintf(fp2, "%s", " )\n");

	}

	else {
		condition1 = strtok(buffer, "DO");
		fprintf(fp2, "%s", "while( ");
		condition(fp2, condition1);
		fprintf(fp2, "%s", " )\n");

	}

}

void IF(FILE* fp1, FILE* fp2) {
	char buffer[100], tmp;
	int i = 0;
	skipCh(fp1);
	do {
		tmp = fgetc(fp1);;
		buffer[i++] = tmp;
	} while (tmp != '\n');
	buffer[--i] = NULL;


	char *condition1, *condition2;

	if (strstr(buffer, "AND") != NULL) {
		condition1 = strtok(buffer, "AND"); // first condition
		condition2 = strtok(NULL, "THEN");
		condition2++;

		fprintf(fp2, "%s", "if( ");
		condition(fp2, condition1);
		fprintf(fp2, "%s", " && ");
		condition(fp2, condition2);
		fprintf(fp2, "%s", " )\n");

	}
	else if (strstr(buffer, "OR") != NULL) {
		condition1 = strtok(buffer, "OR"); // first condition
		condition2 = strtok(NULL, "THEN");
		condition2++; // second condition

		fprintf(fp2, "%s", "if( ");
		condition(fp2, condition1);
		fprintf(fp2, "%s", " || ");
		condition(fp2, condition2);
		fprintf(fp2, "%s", " )\n");

	}

	else if (strstr(buffer, "NOT_EQUAL") != NULL) {
		condition1 = strtok(buffer, "H");
		fprintf(fp2, "%s", "if( ");
		condition(fp2, ++condition1);
		fprintf(fp2, "%s", " )\n");

	}

	else if (strstr(buffer, "EQUAL") != NULL) {
		condition1 = strtok(buffer, "T");
		fprintf(fp2, "%s", "if( ");
		condition(fp2, condition1);
		fprintf(fp2, "%s", " )\n");

	}

	else {
		condition1 = strtok(buffer, "THEN");
		fprintf(fp2, "%s", "if( ");
		condition(fp2, condition1);
		fprintf(fp2, "%s", " )\n");

	}


}

void PRINT_LINE(FILE* fp1, FILE* fp2) {
	// let's read the text until we see \n.
	char buffer[100], tmp;
	int i = 0;
	skipCh(fp1);
	do {
		tmp = fgetc(fp1);;
		buffer[i++] = tmp;
	} while (tmp != '\n');
	i -= 2;
	buffer[i] = NULL;
	// and store it buffer array.


	fprintf(fp2, "printf(%c", '"');


	if (strstr(buffer, "$") != NULL) {
		char* s[10]; i = 0;
		char* buffer2 = malloc(sizeof(char)*(strlen(buffer) + 1));
		strcpy(buffer2, buffer);



		char *type, *var, *temp = strtok(buffer, "$");
		while (temp != NULL) {
			// let's hold the variables and their types when see the dollar sign.
			if (strstr(temp, "_") == NULL) {
				temp = strtok(NULL, "$");
			}
			else {
				var = malloc(sizeof(char)* (strlen(temp) + 1));
				strcpy(var, temp);
				s[i++] = var;
				temp = strtok(NULL, "$");
			}

		}
		s[i] = NULL; i = 0;

		while (s[i] != NULL) {
			var = strtok(s[i], " ,.");
			i++;
		}

		i = 0;
		while (*buffer2 != NULL) {
			if (*buffer2 == '$') {
				buffer2 += strlen(s[i]) + 1;
				var = strtok(s[i++], "_");
				type = strtok(NULL, "\0");
				fputs(formatSpecifier(*type), fp2);

			}

			fputc(*(buffer2++), fp2);
		}

		fputc('"', fp2);
		i = 0;
		while (s[i] != NULL) {
			fprintf(fp2, ",%s ", s[i++]);
		}
	}
	else {
		i = 0;
		while (buffer[i] != NULL) {
			fputc(buffer[i++], fp2);
		}

		fputc('"', fp2);
	}




	fprintf(fp2, ");\n", '"');


}

void GET_VAL(FILE* fp1, FILE* fp2) {

	char* s = readString(fp1);

	if (strstr(s, "]") != NULL) {
		char* arrName = strtok(s, "[");
		char* var = strtok(NULL, "”");
		var = strtok(var, "]");

		arrName = strtok(arrName, "_");
		char* arrType = strtok(NULL, "[");
		arrName += 2;


		var = strtok(var, "_");
		char* varType = strtok(NULL, "]");

		variableList(&HEAD, varType, var);

		fprintf(fp2, "scanf(%c%s%c, &%s[%s]);\n", '"', formatSpecifier(*varType), '"', arrName, var);



	}
	else {
		char* var = strtok(s, "_");
		char* type = strtok(NULL, "”");
		var += 2;
		variableList(&HEAD, type, var);
		fprintf(fp2, "scanf(%c%s%c, &%s);\n", '"', formatSpecifier(*type), '"', var);

	}


}

void c(FILE* fp1, FILE* fp2) {
	fputs("char ", fp2);
}

void f(FILE* fp1, FILE* fp2) {
	fputs("float ", fp2);
}

void i(FILE* fp1, FILE* fp2) {
	fputs("int ", fp2);
}

void l(FILE* fp1, FILE* fp2) {
	fputc('=', fp2);
}

void d(FILE* fp1, FILE* fp2) {
	fputs("double ", fp2);
}

void ld(FILE* fp1, FILE* fp2) {
	fputs("long double", fp2);
}

void file(FILE* fp1, FILE* fp2) {
	fputs("FILE* ", fp2);
}

void cp(FILE* fp1, FILE* fp2) {
	fputs("char* ", fp2);
}

void fp(FILE* fp1, FILE* fp2) {
	fputs("float* ", fp2);
}

void ip(FILE* fp1, FILE* fp2) {
	fputs("int* ", fp2);
}

void lp(FILE* fp1, FILE* fp2) {
	fputs("long* ", fp2);
}

void dp(FILE* fp1, FILE* fp2) {
	fputs("double* ", fp2);
}


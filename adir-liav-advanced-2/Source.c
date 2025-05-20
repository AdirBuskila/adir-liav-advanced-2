/*
	Assigned by:
	Liav Weizman 324926898
	Adir Buskila 209487727
*/

#define _CRT_SECURE_NO_WARNINGS

/* Libraries */

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

/* Constant definitions */

#define N 3

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

char** split(char letter, char* str, int* p_size);
void createFile(char* filename);
char commonestLetter(char* filename);
void decode(char* text);

/* Declarations of auxiliary functions */

char* getStr(char* str, int startI, int endI);
void printStringsArray(char** str_arr, int size);
void freeMatrix(void** A, int rows);

/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= N; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-%d : ", N);
				scanf("%d", &select);
			} while ((select < 0) || (select > N));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			}
		} while (all_Ex_in_loop && select);
	return 0;
}


/* Function definitions */

void Ex1()
{
	char* str = { "Rony     Goodman got a good mark" };
	int size = 0;
	char letter = 'g';
	char** arr = split(letter, str, &size);
	printStringsArray(arr, size);
	/* Called functions:
		split, printStringsArray, freeMatrix */
		/* Write Code Here! */
}

void Ex2()
{
	createFile("C:\\Users\\Adir\\Desktop\\Adir-Liav\\output.txt");
	/* Called functions:
		createFile, commonestLetter */
		/* Write Code Here! */
}

void Ex3()
{
	/* Called functions:
		decode */
		/* Write Code Here! */
}

char** split(char letter, char* str, int* p_size)
{
	char** arr = NULL;
	int startI = 0, endI = 0;
	int i = 0;
	*p_size = 0;
	int insideWord = 1;
	int firstLetter = 1;

	while (str[startI] != '\0') {
		char c = str[startI];
		// if we are inside a word, and its the first letter
		if (insideWord && firstLetter) {
			if (tolower(c) == letter) {
				*p_size += 1;
			}
			firstLetter = 0;
		}
		// if we are inside a word and its not the first letter
		if (insideWord && !firstLetter) {
			while (str[startI] != '\0' && !isspace(str[startI]))
				startI++;
			insideWord = 0;
		}
		/// we are not inside the word
		if (!insideWord && !firstLetter) {
			while (str[startI] != '\0' && isspace(str[startI]))
				startI++;
			insideWord = 1;
			firstLetter = 1;
		}
	}
	arr = (char**)malloc(sizeof(char*) * (*p_size));

	if (!arr) {
		*p_size = 0;
		return NULL;
	}

	startI = endI = 0;
	insideWord = 1;
	while (str[endI] != '\0') {
		if (insideWord) {
			while (str[endI] != '\0' && !isspace(str[endI + 1]))
				endI++;

			if (tolower(str[startI]) == letter) {
				arr[i++] = getStr(str, startI, endI);
			}
			insideWord = 0;
			endI++;
		}
		else {
			while (str[endI] != '\0' && isspace(str[endI])) endI++;
			startI = endI;
			insideWord = 1;
		}
	}
	return arr;
}

void createFile(char* filename) {
	FILE* fp = fopen(filename, "w");
	if (!fp)return;
	char c;
	printf("Enter text (Ctrl+Z then Enter to stop on Windows, or Ctrl+D on Linux/Mac):\n");
	while ((c = fgetc(stdin)) != EOF) {
		if (c != '\n')
			fputc(c, fp);
	}
	fclose(fp);
}
char commonestLetter(char* filename)
{
	/* Write Code Here! */
}

void decode(char* text)
{
	/* Write Code Here! */
}

/* Definitions of auxiliary functions */


/* Write Definitions Here! */
char* getStr(char* str, int startI, int endI) {
	int size = (endI - startI + 2);
	char* newStr = (char*)malloc(sizeof(char) * size);
	int i = 0;
	if (!newStr) return NULL;
	while (startI <= endI) {
		newStr[i++] = str[startI++];
	}
	newStr[i] = '\0';
	return newStr;
}
void printStringsArray(char** str_arr, int size) {
	for (int i = 0; i < size; i++)
	{
		printf("%s\n", str_arr[i]);
	}
}
void freeMatrix(void** A, int rows) {
	for (int i = 0; i < rows; i++)
	{
		free(A[i]);
	}
	free(A);
}

/* ------------------- */
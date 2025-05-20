/*
	Assigned by:
	Liav Weizman 324926898
	Adir Buskila 209487727
*/

#define _CRT_SECURE_NO_WARNINGS

/* Libraries ---------------------------------------------------------------- */
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

/* Constant definitions ------------------------------------------------------*/
#define N 3

/* Function declarations -----------------------------------------------------*/
void Ex1();
void Ex2();
void Ex3();

char** split(char letter, char* str, int* p_size);
void createFile(char* filename);
char commonestLetter(char* filename);
void decode(char* text);

/* Auxiliary declarations ----------------------------------------------------*/
char* getStr(char* str, int startI, int endI);
void  printStringsArray(char** str_arr, int size);
void  freeMatrix(void** A, int rows);

/* ------------------------------- MAIN ------------------------------------- */
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

/* -------------------------------------------------------------------------- */
/* Ex1
   ----
   • Reads a full line from the user and a single letter.
   • Uses split() to collect every word whose first character matches
	 the given letter (case-insensitive).
   • Prints those words, then frees the allocated memory.                     */
void Ex1()
{
	char str[100];
	int size = 0;
	char letter;
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
	printf("Please enter your string:\n");
	fgets(str, sizeof(str), stdin);
	printf("Please enter your letter:\n");
	scanf_s("%c", &letter);
	char** arr = split(letter, str, &size);
	printStringsArray(arr, size);
	freeMatrix(arr, size);
}

/* -------------------------------------------------------------------------- */
/* Ex2
   ----
   • Prompts the user to type arbitrary text that is saved into "input.txt".
   • Scans that file and reports the most frequent alphabetic character.      */
void Ex2()
{
	char* file = "input.txt";
	createFile(file);
	char c = commonestLetter(file);
	printf("The most common letter in the file is:%c\n", c);
}

/* -------------------------------------------------------------------------- */
/* Ex3
   ----
   • Demonstrates decode() on a fixed encrypted sentence and prints the result.*/
void Ex3()
{
	char str[56] = "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt";
	decode(str);
	printf("%s\n", str);
}

/* -------------------------------------------------------------------------- */
/* split
   -----
   • Counts and extracts all words in 'str' whose first letter equals 'letter'.
   • Returns a dynamically-allocated array of strings; *p_size holds its size.
   • Two passes are performed: first to count matches, second to copy words.  */
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

/* -------------------------------------------------------------------------- */
/* createFile
   ----------
   • Opens/creates 'filename' for writing.
   • Copies every character typed on stdin until EOF (Ctrl+Z / Ctrl+D).
   • Currently omits newline characters to produce a single-line file.        */
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

/* -------------------------------------------------------------------------- */
/* commonestLetter
   ----------------
   • Reads the file and counts occurrences of each letter (case-insensitive).
   • Returns the most frequent letter as an uppercase char.
   • If file is empty or unreadable, returns '\0'.                            */
char commonestLetter(char* filename)
{
	FILE* fPtr = fopen(filename, "r");
	if (!fPtr)
	{
		return '\0';
	}

	char c;
	int count[26] = { 0 };
	while ((c = fgetc(fPtr)) != EOF)
	{
		if (isalpha(c))
		{
			int index = tolower(c) - 'a';
			count[index]++;
		}
	}
	int maxI = -1;
	int max = -1;
	for (int i = 0; i < 26; i++)
	{
		if (count[i] >= max) {
			maxI = i;
			max = count[i];
		}
	}
	fclose(fPtr);
	char common = maxI + 'A';
	return common;
}

/* -------------------------------------------------------------------------- */
/* decode
   ------
   • Progressive Caesar-shift decrypt: starting with shift=1, subtracts an
	 increasing value from every non-space character.  Shift resets after a
	 space, resulting in words being decoded independently.                    */
void decode(char* text)
{
	int decoder = 1;
	int i = 0;
	while (text[i] != '\0') {
		if (!isspace(text[i])) {
			char c = text[i] - decoder;
			text[i] = c;
			decoder++;
		}
		else {
			decoder = 1;
		}
		i++;
	}
}

/* ---------------- Auxiliary utilities ------------------------------------- */
/* getStr
   -------
   • Allocates and returns a new substring str[startI..endI] (inclusive).     */
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

/* printStringsArray
   -----------------
   • Prints each string in the array on its own line.                         */
void printStringsArray(char** str_arr, int size) {
	for (int i = 0; i < size; i++)
	{
		printf("%s\n", str_arr[i]);
	}
}

/* freeMatrix
   ----------
   • Frees a 1-D array of pointers, each pointing to dynamically
	 allocated memory (i.e., a "matrix" by rows).                             */
void freeMatrix(void** A, int rows) {
	for (int i = 0; i < rows; i++)
	{
		free(A[i]);
	}
	free(A);
}

/* -------------------------------------------------------------------------- */

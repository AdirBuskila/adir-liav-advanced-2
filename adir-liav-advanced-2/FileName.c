#include <stdio.h>

void createFile(char* filename)
{
    FILE* fPtr = fopen(filename, "w");
    if (fPtr == NULL)
    {
        printf("Could not create file.\n");
        return;
    }

    printf("Enter text (Ctrl+Z then Enter to stop on Windows, or Ctrl+D on Linux/Mac):\n");

    char ch;
    while ((ch = getchar()) != EOF)
    {
        fputc(ch, fPtr);
    }

    fclose(fPtr);
    printf("File '%s' created successfully.\n", filename);
}
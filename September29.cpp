#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE1 "start.txt"
#define FILE2 "end.txt"

#define MAXSTRING 256

int countSpaces(char str[])
{
    int count = 0;

    for(int i = 0; i < strlen(str); i++) if (str[i] == ' ') count++;

    return count;
}

int countWords(char name[])
{
    FILE* pF;
    int count = 0;

    if (pF = fopen(name, "r+t"))
    {
        char str[MAXSTRING];
        fgets(str, MAXSTRING, pF) + 1;

        while (!feof(pF) && strcmp(str, ""))
        {
            count += countSpaces(str) + 1;
            fgets(str, MAXSTRING, pF);
        }

        fclose(pF);
    }

    return count;
}

void removeSpaces(char dst[], char src[])
{
    FILE *pF1, *pF2;

    if (pF1 = fopen(src, "rt"))
    {
        char str[MAXSTRING];
        fgets(str, MAXSTRING, pF1);
        while (!feof(pF1) && strcmp(str, ""))
        {
            while (str[0] == ' ' && str[1] && str[0])
                strcpy(str, str + 1);

            for (int i = 0; i < strlen(str); i++)
                if(str[i] == ' ' && str[i + 1] == ' ')
                    strcpy(str + i--, str + i + 1);
            if (pF2 = fopen(dst, "at"))
            {
                fputs(str, pF2);
                fclose(pF2);
            }
            fgets(str, MAXSTRING, pF1);
        }
        fclose(pF1);
    }
}

void writeText(char name[])
{
    FILE* pF;

    if (pF = fopen(name, "w+t"))
    {
        char str[MAXSTRING];
        printf(">>> ");
        fflush(stdin);
        gets_s(str);
        while(strcmp(str, ""))
        {
            fputs(str, pF);
            fputc('\n', pF);
            printf(">>> ");
            fflush(stdin);
            gets_s(str);
        }

        fclose(pF);
    }
}

int main()
{
    writeText(FILE1);
    removeSpaces(FILE2, FILE1);
    printf("%d\n", countWords(FILE2));
    remove(FILE1);
    remove(FILE2);

    

    return 0;
}
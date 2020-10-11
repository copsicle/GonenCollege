#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STRUCTS 3

#define FILE1 "filedata.dat"
#define FILE2 "resultdata.dat"

typedef struct Student
{
    char name[20];
    int grade;
};

void FileExperiment()
{
    FILE* pFile;

    Student sArr[STRUCTS] = {{"Gonen", 69}, {"Yona", 42}, {"Reuven", 100}};
    Student sSingle;

    if ((pFile = fopen(FILE1, "w+b")) != NULL)
    {
        fwrite(&sArr, sizeof(Student), STRUCTS, pFile);
        fclose(pFile);
    }

    if ((pFile = fopen(FILE1, "rb")) != NULL)
    {
        for (int i = 0; i < STRUCTS; i++)
        {
            fread(&sSingle, sizeof(Student), 1, pFile);
            printf("Name: %s Grade: %d\n", sSingle.name, sSingle.grade);
        }
        fclose(pFile);
        remove(FILE1);
    }
}

FILE* RandomlyGenerateFile(char* sFileName)
{
    FILE* pFile;
    
    srand((unsigned)time(NULL));
    int arrnNumbers[100];

    for (int i = 0; i < 100; i++)
    {
        arrnNumbers[i] = (int) (rand() % 100) + 1;
        printf("%d: %d\n", i, arrnNumbers[i]);
    }
    if (pFile = fopen(sFileName, "wb"))
    {    
        fwrite(&arrnNumbers, sizeof(int), 100, pFile);
        fclose(pFile);
    }
    return fopen(sFileName, "r+b");
}

void SortFile()
{
    FILE* pData = RandomlyGenerateFile(FILE1);
    FILE* pResult;

    int temp;

    while(fread(&temp, sizeof(int), 1, pData))
        printf("%d \n", temp);

    fclose(pData);
    remove(FILE1);
}

int main()
{
    SortFile();    

    return 0;
}
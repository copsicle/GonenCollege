#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STRUCTS 3

#define FILE1 "STUDENT.DAT"
#define FILE2 "BOGRIM.DAT"

typedef enum Class {YUD=10, YUDA, YUDB};

typedef struct Student
{
    char address[20];
    char firstname[20];
    char lastname[20];
    Class sclass;
    char phonenum[20];
    int status;
};

typedef struct PostStudent
{
    char address[20];
    char firstname[20];
    char lastname[20];
    char phonenum[20];
};

typedef struct person
{
    char name[20];
    int age;
    int id;
};

int inputData()
{
    FILE* pFile;
    Student sStudent;
    int nCounter;

    printf("Enter number of students: ");
    scanf("%d", &nCounter);

    for (int i = 1; i <= nCounter; i++)
    {   
        printf("Enter info about student #%d: ", i);
        scanf("%s\n%s\n%s\n%d\n%s\n%d",
            sStudent.address, sStudent.firstname,sStudent.lastname,
            sStudent.sclass, sStudent.phonenum, sStudent.status);
        if (pFile = fopen(FILE1, "ab"))
        {
            fwrite(&sStudent, sizeof(Student), 1, pFile);
            fclose(pFile);
        }
    }

    return nCounter;
}

void rumFileTxt1() {
    person parr[3];
    FILE* fin;

    fin = fopen("persons.txt", "wt");
    person temp[3] =
    {
        {"Danielle", 18, 316359l},
        {"Niv", 15, 533892l},
        {"Shaked", 10, 586151l}
    };

    for (int i = 0; i < 3; i++) {
        fprintf(fin, "%s %d %ld\n", temp[i].name, temp[i].age, temp[i].id);
    }
    fclose(fin);
    fin = fopen("persons.txt", "rt");
    if (fin == NULL)perror("");
    else
    {
        for (int i = 0; i < 3; i++) {
            fscanf(fin, "%s %d %ld\n", parr[i].name, &parr[i].age, &parr[i].id);

        }
        fclose(fin);
        for (int i = 0; i < 3; i++) {
            printf("%-12s %3d %9ld\n", parr[i].name, parr[i].age, parr[i].id);
        }
    }

    remove("persons.txt");

}

int main()
{
    FILE* pFile, pResult;

    Student sarrStudents[3] = {
        {"123 Bruh Drive", "Gonen", "Cohen", YUDA, "0524206969", 1},
        {"456 Moment Avenue", "Yona", "Seadia", YUDB, "0536036069", 1},
        {"789 Lidl Street", "Reuven", "Hotoveli", YUD, "0542042069", 1}};

    Student sRead;
    PostStudent sWrite;

    int nOffset = 0;

    if (pFile = fopen(FILE1, "w+b"))
    {
        fwrite(sarrStudents, sizeof(Student), 3, pFile);
        fclose(pFile);
    }

    if (pFile = fopen(FILE1, "w+b"))
    {
        while (!feof(pFile))
        {
            fread(&sRead, sizeof(Student), 1, pFile);
            if (sRead.sclass == YUDB)
            {
                sRead.status = 0;
                fseek(pFile, nOffset++, SEEK_SET);
                fwrite(&sRead, sizeof(Student), 1, pFile);
                if (fopen(FILE2, "ab"))
                {
                    
                    //fwrite();
                }
            }
        }
    }
    
    remove(FILE1);

    return 0;
}
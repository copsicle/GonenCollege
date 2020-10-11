#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 3
#define MAX 7
#define LEN 20

typedef struct
{
	int day;
	int month;
	int year;
}Date;

typedef struct
{
	int serial_num;
	char full_name[LEN];
	Date* pDate;
}Person;

void printList(Person* arr, int count);
void freeList(Person** arr, int* count);
void addToList(const char* names[], const int dates[][COLS], int* count, Person** arr);
void sortList(Person* arr, int count);
void writeFile(const char* fn, Person* arr, int count);
void readFile(const char* fn, Person** arr, int* count);
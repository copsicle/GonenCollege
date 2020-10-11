#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATROW 10
#define MATCOL 10
#define WALLSIZE 1
#define DIRECTIONS 8

typedef struct polynom
{
	int base;
	int exp;
	struct polynom* next;
}poly, *polyPtr;

typedef struct coords
{
	int nRow;
	int nCol;
};

void polyMain();
void bulkMain();
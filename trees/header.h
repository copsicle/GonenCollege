#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum boolean{FALSE, TRUE};

typedef int itemType;

typedef struct treeType
{
	itemType info;
	treeType* left;
	treeType* right;
}	tree, * treePtr;

void buildTree(treePtr* t, itemType val);
void insertTree(treePtr* t, itemType val);
void freeTree(treePtr* t);
void levelScan(treePtr t);
void printMaxInLevels(treePtr t);
int balanceCheck(treePtr t);
void printBiggestLevel(treePtr t);
void printLevel(treePtr t, int level);
void insertIntoAVL(treePtr* t, itemType val);
void inScan(treePtr* t);
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE1 "C:\\Users\\Gonen\\source\\repos\\Project1\\PROJECT1.DAT"
#define STRMAX 50

typedef enum {
	FAILURE, SUCCESS, INVALID_INPUT, FILE_ERROR,
	DUPLICATE_RECORD, MISSING_RECORD, EXIT
} statusType;

typedef enum { FALSE, TRUE } boolean;

typedef struct Player
{
	char* plyrID;
	char* firstName;
	char* lastName;
	int age;
};

typedef struct PlayerNode
{
	struct Player PL;
	struct Team* tmptr;
	struct PlayerNode* next;
};

typedef struct Team
{
	char* teamName;
	int num;
	struct Player** players;
	struct Team* next;
};

typedef struct headType
{
	struct Team* teamList;
	struct PlayerNode* playerList;
}
headder, * headPtr;

extern headder head;

statusType readFromFile();
boolean handleStatus(statusType s);
statusType select(int selection);
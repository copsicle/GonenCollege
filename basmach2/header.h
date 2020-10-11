#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAPROW 100
#define MAPCOL 200
#define WALLSIZE 1

#define DIRECTIONS 4

typedef struct Direction
{
    int nLine;
    int nCol;
};

typedef struct Trof
{
    int nIT;
    int nJT;

    int nSx;
    Direction sDx[DIRECTIONS + 1];
};

int TestTrons(Trof* sTrof, Direction sDrc,
    int* nTronAmount, int mMat[][MAPCOL + WALLSIZE * 2]);
int TrofCheckCells(int mMat[][MAPCOL + WALLSIZE * 2],
    Trof* sTrof, int* nTronAmount, Direction sDrc);
void GetTrof(Trof* sTrof);
void TrofLoop(Trof sTrof, int mMat[][MAPCOL + WALLSIZE * 2], int nTronAmount);
void GetTrons(int mMat[][MAPCOL + WALLSIZE * 2], int* nTronAmount);
void TickInt(int* nNum, int* bRising);
void SetDirections(Trof* sTrof, int nX, int nY, int nModX, int nModY);
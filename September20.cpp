#define CRT_SECURE_NO_WARNINGS

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
int TrofCheckCell(int mMat[][MAPCOL + WALLSIZE * 2],
                 Trof* sTrof, int* nTronAmount, Direction sDrc);
void GetTrof(Trof* sTrof);
void TrofLoop(Trof sTrof, int mMat[][MAPCOL + WALLSIZE * 2], int nTronAmount);
void GetTrons(int mMat[][MAPCOL + WALLSIZE * 2], int* nTronAmount);
void TickInt(int* nNum, int* bRising);
void SetDirections(Trof* sTrof);

//-----------------------------------------------------------------------------
// TRON AND TROF
// -----------
//
// General : This is a simulation of the TRON and TROF war.
//
// Input : Infromation about the TRONs and TROF.
//
// Process : Simulate the war.
//
// Output : Prints events in the war and the results.
//
//-----------------------------------------------------------------------------
// Programmer : Gonen Cohen
// Student No : N/A
// Date : 20.09.2020
//-----------------------------------------------------------------------------

int main()
{
    int mMap[MAPROW + WALLSIZE * 2][MAPCOL + WALLSIZE * 2] = {0};
    int nTronAmount = 0;

    Trof sTrof;

    SetDirections(&sTrof);
    GetTrons(mMap, &nTronAmount);
    TrofLoop(sTrof, mMap, nTronAmount);

    return 0;
}


//-----------------------------------------------------------------------------
// TestTrons
// ---------
//
// General : Checks if the next point has TRONs and outputs relevant results
//
// Parameters :
//
// sTrof - TROF structure (I\O)
// sDrc - The structure for the wanted direction with the next point.
// nTronAmount - The total amount of trons on the map (Out)
// mMat - The general matrix for the map (I\O)
//
// Return value - Boolean that indicates if TROF is alive
//
//-----------------------------------------------------------------------------

int TestTrons(Trof* sTrof, Direction sDrc,
                int* nTronAmount, int mMat[][MAPCOL + WALLSIZE * 2])
{
    int nTrons;

    int nYOffset = sTrof->nIT + sDrc.nLine;
    int nXOffset = sTrof->nJT + sDrc.nCol;
            
    if (nXOffset >= WALLSIZE && nXOffset <= MAPROW + WALLSIZE - 1 &&
        nYOffset >= WALLSIZE && nYOffset <= MAPCOL + WALLSIZE - 1)        
        {
            nTrons = mMat[nXOffset][nYOffset];
            printf("\nTROF advanced to (%d, %d) and encountered %d TRONS\n",
                    nXOffset, nYOffset, nTrons);
            if (nTrons > 2)
            {
                printf("\nTROF tried to eat too many TRONs and died.\n");
                mMat[nXOffset][nYOffset] = nTrons - 2;
                *nTronAmount -= 2;
                printf("%d TRONs were left. Game Over.\n", *nTronAmount);
                return 0;
            }
            else 
            {
                printf("TROF ate %d TRONs and decided to keep going.\n", nTrons);
                mMat[nXOffset][nYOffset] = 0;
                *nTronAmount -= nTrons;
            }

            sTrof->nIT = nYOffset;
            sTrof->nJT = nXOffset;
        }
        else
        {
            printf("\nTROF stopped at the border of the planet.\n");
        }
    
    return 1;
}

//-----------------------------------------------------------------------------
// TrofCheckCell
// ---------
//
// General : Checks if TROFs path has TRONs and outputs relevant results
//
// Parameters :
//
// mMat - The general matrix for the map (I\O)
// sTrof - TROF structure (I\O)
// nTronAmount - The total amount of trons on the map (Out)
// sDrc - The structure for the wanted direction with the next point.
//
// Return value - Boolean that indicates if TROF is alive
//
//-----------------------------------------------------------------------------

int TrofCheckCell(int mMat[][MAPCOL + WALLSIZE * 2],
                 Trof* sTrof, int* nTronAmount, Direction sDrc)
{
    if (sTrof->nSx)
    {
        for (int i = 1; i <= sTrof->nSx; i++)
        {
            if (!TestTrons(sTrof, sDrc, nTronAmount, mMat)) return 0;
        }
    }
    else
    {
        TestTrons(sTrof, sDrc, nTronAmount, mMat);
    }
    return 1;
}

//-----------------------------------------------------------------------------
// GetTrof
// ---------
//
// General : Get initial info about TROF
//
// Parameters :
// sTrof - TROF structure (I\O)
//
//-----------------------------------------------------------------------------

void GetTrof(Trof* sTrof)
{
    printf("\nInsert X location (1 - %d) for TROF: ", MAPROW);
    scanf("%d", &sTrof->nIT);
    printf("Insert Y location (1 - %d) for TROF: ", MAPCOL);
    scanf("%d", &sTrof->nJT);
}

//-----------------------------------------------------------------------------
// TrofLoop
// ---------
//
// General : The main loop of input and output about TROF
//
// Parameters :
// sTrof - TROF structure (I\O)
// mMat - The general matrix for the map (I\O)
// nTronAmount - The total amount of trons on the map (Out)
//
//-----------------------------------------------------------------------------

void TrofLoop(Trof sTrof, int mMat[][MAPCOL + WALLSIZE * 2], int nTronAmount)
{
    GetTrof(&sTrof);

    int nDirection = 0, nTrons = mMat[sTrof.nIT][sTrof.nJT];    
    sTrof.nSx = 0;
    char c;

    do
    {
        if(!TrofCheckCell(mMat, &sTrof, &nTronAmount, sTrof.sDx[nDirection])) 
            return;

        printf("\nInsert number of steps to take: ");
        scanf("%d", &sTrof.nSx);
        printf("Insert direction for steps (1 - 4 clockwise): ");
        scanf(" %c", &c);
        nDirection = c - '0';
    } while (sTrof.nSx && nDirection);

    printf("\nTROF got tired and doesn't want to move anymore.\n");
    printf("%d TRONs are left. Game Over.\n", nTronAmount);
}

//-----------------------------------------------------------------------------
// GetTrons
// ---------
//
// General : Process input of number of TRONs and their locations.
//
// Parameters :
// mMat - The general matrix for the map (I\O)
// nTronAmount - The total amount of trons on the map (Out)
//
//-----------------------------------------------------------------------------

void GetTrons(int mMat[][MAPCOL + WALLSIZE * 2], int* nTronAmount)
{
    int nIx, nJx;

    printf("Insert number of TRONs: ");
    scanf("%d", nTronAmount);
    printf("\nThe map size is %d rows and %d columns\n", MAPROW, MAPCOL);

    for(int i = 1; i <= *nTronAmount; i++)
    {
        printf("\nInsert X location (1 - %d) for TRON #%d: ", MAPROW, i);
        scanf("%d", &nIx);
        printf("Insert Y location (1 - %d) for TRON #%d: ", MAPCOL, i);
        scanf("%d", &nJx);

        mMat[nIx + WALLSIZE - 1][nJx + WALLSIZE - 1]++;
    }
}

//-----------------------------------------------------------------------------
// TickInt
// ---------
//
// General : Generates the pattern needed to generate directions.
//
// Parameters :
// nNum - Direction value to modify (I\O)
// bRising - Boolean modifier for nNum to check if it's rising or falling
//
//-----------------------------------------------------------------------------

void TickInt(int* nNum, int* bRising)
{
    switch (*nNum)
    {
        case 0:
            if (*bRising) *nNum = 1;
            else *nNum = -1;

            break;
        case 1:
            *nNum = 0;
            *bRising = 0;

            break;
        case -1:
            *nNum = 0;
            *bRising = 1;

            break;
        default:

            break;
    }
}

//-----------------------------------------------------------------------------
// SetDirections
// ---------
//
// General : Generates the direction array for TROF
//
// Parameters :
// sTrof - TROF structure (I\O)
//
//-----------------------------------------------------------------------------

void SetDirections(Trof* sTrof)
{
    
    int nX = -1, nY = 0, nModX = 0, nModY = 1;

    sTrof->sDx[0].nLine = 0;
    sTrof->sDx[0].nCol = 0;

    for (int i = 1; i <= DIRECTIONS; i++)
    {
        sTrof->sDx[i].nLine = nX;
        sTrof->sDx[i].nCol = nY;

        TickInt(&nX, &nModX);
        TickInt(&nY, &nModY);
    }
}

#include "header.h"

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

    // Check if cell is inside the wall
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
// TrofCheckCells
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

int TrofCheckCells(int mMat[][MAPCOL + WALLSIZE * 2],
    Trof* sTrof, int* nTronAmount, Direction sDrc)
{
    // Check if this is the first arrival of TROF or taking steps
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
        // Check if TROF is still alive after taking steps or arriving
        if (!TrofCheckCells(mMat, &sTrof, &nTronAmount, sTrof.sDx[nDirection]))
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

    for (int i = 1; i <= *nTronAmount; i++)
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
        // If rising rise until 1 and start to fall again
        // Like a clockwise motion in a matrix
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
// nX - Initial X value for pattern (In)
// nY - Initial Y value for pattern (In)
// nModX - Initial X Modifier for pattern (In)
// nModY - Initial Y Modifier for pattern (In)
//
//-----------------------------------------------------------------------------

void SetDirections(Trof* sTrof, int nX, int nY, int nModX, int nModY)
{
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
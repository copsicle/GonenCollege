#include "header.h"

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
    int mMap[MAPROW + WALLSIZE * 2][MAPCOL + WALLSIZE * 2] = { 0 };
    int nTronAmount = 0;

    Trof sTrof;

    SetDirections(&sTrof, -1, 0, 0, 1);
    GetTrons(mMap, &nTronAmount);
    TrofLoop(sTrof, mMap, nTronAmount);

    return 0;
}
#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE1 "PROJECT1.DAT"

typedef enum {FAILURE, SUCCESS, INVALID_INPUT,
            DUPLICATE_RECORD, MISSING_RECORD} statusType;

typedef enum {FALSE, TRUE} boolean;

typedef struct playerType
{
    long plyrID;
    
    int age;
    
    char firstName[15];
    char lastName[20];

    struct teamType *tmptr;
    struct playerType *next;    
}
playerRec, *playerPtr;

typedef struct teamType
{
    char teamName[20];

    int num;

    playerPtr *plarray;

    struct teamType *next;
}
teamRec, *teamPtr;

playerPtr players;

teamPtr teams;

playerPtr findPlayer(long playerID)
{
    playerPtr p = players;

    while (p)
    {
        if (p->plyrID == playerID) return p;
        p = p->next;
    }

    return NULL;
}

teamPtr findTeam(char teamName[])
{
    teamPtr t = teams;

    while (t)
    {
        if (!strcmp(t->teamName, teamName)) return t;
        t = t->next;
    }

    return NULL;
}

statusType insertPlayer(long playerID, char lastName[], char firstName[], int age)
{
    statusType status = SUCCESS;
    playerPtr p, q;
    q = findPlayer(playerID);
    if (q)
    {
        status = DUPLICATE_RECORD;
        return status;
    }
    p = (playerPtr) malloc(sizeof(playerRec));
    p -> plyrID = playerID;
    strcpy(p->firstName, firstName);
    strcpy(p->lastName, lastName);
    p -> age = age;
    p -> tmptr = NULL;
    p -> next = players;
    players = p;
    return status;
}

statusType deletePlayer(long playerID)
{
    playerPtr p, q;
    statusType status = SUCCESS;
    p = findPlayer(playerID);
    if (p == NULL) status = MISSING_RECORD;
    else
    {
        if (p->tmptr) status = deletePlayerFromTeam(playerID);
        q = players;
        if (players == p)
        {
            players = q->next;
            free(p);
        }
        else
        {
            while (q->next)
            {
                if (q->next == p)
                {
                    q->next = p->next;
                    free(p);
                    break;
                }
                q = q->next;
            }
        }
    }
    return status;
}

statusType deletePlayerFromTeam(long playerID)
{
    playerPtr p;
    teamPtr t;
    int i, k;
    statusType status = SUCCESS;
    p = findPlayer(playerID);
    if ((p == NULL) || (p->tmptr==NULL)) status = MISSING_RECORD;
    else
    {
        t = p->tmptr;
        p->tmptr = NULL;
        for (i = 0; i < t -> num; i++)
        {
            if (t->plarray[i]->plyrID == playerID)
            {
                k = i;
                break;
            }
        }
        for (i = k + 1; i < t -> num; i++)
            t -> plarray[i-1] = t->plarray[i];
        t->num = t->num - 1;
        t->plarray = (playerPtr*) realloc(t->plarray, (t->num) * sizeof(playerPtr));
    }
    return status;
}

statusType deleteTeam(char teamName[])
{
    statusType status = SUCCESS;
    int i;
    teamPtr t, s;
    t = findTeam(teamName);
    if (t == NULL) status = MISSING_RECORD;
    else
    {
        if (t->plarray)
            for(i = 0; i < t->num; i++)
                t->plarray[i]->tmptr = NULL;
        if (t == teams)
            teams = t->next;
        else
        {
            s = teams;
            while (s->next != t)
                s = s->next;
            s->next = t->next;
        }
        free(t);
    }
    return status;
}

statusType joinPlayerToTeam(long playerID, char team[])
{
    statusType status = SUCCESS;
    playerPtr p;
    teamPtr t;
    p = findPlayer(playerID);
    t = findTeam(team);
    if ((p == NULL) || (t == NULL)) status = MISSING_RECORD;
    else
    {
        if (p->tmptr) status = MISSING_RECORD;
        else
        {
            p->tmptr = t;
            if (t->num == 0)
            {
                t->plarray = (playerPtr*) realloc(NULL, sizeof(playerPtr));
                t->plarray[0] = p;
                t->num = 1;
            }
            else
            {
                t -> plarray = (playerPtr*) realloc
                    (t->plarray,(t->num + 1) * sizeof(playerPtr));
                t->plarray[t->num] = p;
                t -> num = t->num + 1;
            }
        }   
    }
    return status;
}

int main()
{

    return 0;
}
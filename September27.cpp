#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE1 "PROJECT1.DAT"

typedef enum {FAILURE, SUCCESS, INVALID_INPUT,
            DUPLICATE_RECORD, MISSING_RECORD} statusType;

typedef enum {FALSE, TRUE} boolean;

typedef struct Player
{
    long plyrID;
    char firstName[15];
    char lastName[20];
    int age;
};

typedef struct PlayerNode
{
    Player PL;
    struct teamType *tmptr;
    struct PlayerNode *next;
};

typedef struct Team
{
    char teamName[20];
    int num;
    Player **players;
    struct Team *next;
};

typedef struct headType
{
    struct Team *teamList;
    struct PlayerNode *playerList;
}
headder, *headPtr;

PlayerNode* findPlayer(long playerID, headPtr head)
{
    PlayerNode *p = head->playerList;

    while (p)
    {
        if (p->PL.plyrID == playerID) return p;
        p = p->next;
    }

    return NULL;
}

Team* findTeam(char name[], headPtr head)
{
    Team *t = head->teamList;

    while (t)
    {
        if (!strcmp(t->teamName, name)) return t;
        t = t->next;
    }

    return NULL;
}

statusType insertPlayer(
    long playerID,char lastName[], char firstName[], int age, headPtr head
    )
{
    statusType status = SUCCESS;
    PlayerNode *p, *q;
    q = findPlayer(playerID, head);
    if (q)
    {
        status = DUPLICATE_RECORD;
        return status;
    }
    p = (PlayerNode*) malloc(sizeof(PlayerNode));
    p->PL.plyrID = playerID;
    strcpy(p->PL.firstName, firstName);
    strcpy(p->PL.lastName, lastName);
    p->PL.age = age;
    p->tmptr = NULL;
    p -> next = head->playerList;
    head->playerList = p;
    return status;
}

statusType insertTeam(char name[])
{
    statusType status = SUCCESS;
    teamPtr t = findTeam(name);
    if (t)
    {
        status = DUPLICATE_RECORD;
        return status;
    }
    t = (teamPtr) malloc(sizeof(teamRec));
    strcpy(t->teamName, name);
    t->num = 0;
    t->plarray = NULL;
    t->next = teams;
    teams = t;
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

void createFile()
{
    FILE* pFile = fopen(FILE1, "w+b");
    
    teamRec t;

    char name[20];
    int size = 1;

    printf("Enter name for team 1: ");
    flushall();
    gets(name);

    t.num = 0;

    while(strcmp("",name))
    {
        strcpy(t.teamName, name);
    }

}

int main()
{

    createFile();

    return 0;
}
#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE1 "PROJECT1.DAT"
#define MAXSTR 50

typedef enum {FAILURE, SUCCESS, INVALID_INPUT,
            DUPLICATE_RECORD, MISSING_RECORD, FILE_ERROR} statusType;

typedef enum {FALSE, TRUE} boolean;

typedef struct Player
{
    long plyrID;
    char firstName[MAXSTR];
    char lastName[MAXSTR];
    int age;
};

typedef struct PlayerNode
{
    Player PL;
    struct Team *tmptr;
    struct PlayerNode *next;
};

typedef struct Team
{
    char teamName[MAXSTR];
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

headder head;

PlayerNode* findPlayer(long playerID)
{
    PlayerNode *p = head.playerList;

    while (p)
    {
        if (p->PL.plyrID == playerID) return p;
        p = p->next;
    }

    return NULL;
}

Team* findTeam(char name[])
{
    Team *t = head.teamList;

    while (t)
    {
        if (!strcmp(t->teamName, name)) return t;
        t = t->next;
    }

    return NULL;
}

statusType insertPlayer(long playerID, char lastName[], char firstName[], int age)
{
    PlayerNode *p, *q;
    q = findPlayer(playerID);
    if (q) return DUPLICATE_RECORD;
    p = (PlayerNode*) malloc(sizeof(PlayerNode));
    if (!p) return FAILURE;
    p->PL.plyrID = playerID;
    strcpy(p->PL.firstName, firstName);
    strcpy(p->PL.lastName, lastName);
    p->PL.age = age;
    p->tmptr = NULL;
    p -> next = head.playerList;
    head.playerList = p;
    return SUCCESS;
}

statusType insertTeam(char name[])
{
    Team* t = findTeam(name);
    if (t) return DUPLICATE_RECORD;
    t = (Team*) malloc(sizeof(Team));
    if (!t) return FAILURE;
    strcpy(t->teamName, name);
    t->num = 0;
    t->players = NULL;
    t->next = head.teamList;
    head.teamList = t;
    return SUCCESS;
}

statusType deletePlayerFromTeam(long playerID)
{
    PlayerNode* p;
    Team* t;
    int i, k;
    p = findPlayer(playerID);
    if ((p == NULL) || (p->tmptr==NULL)) return MISSING_RECORD;
    else
    {
        t = (Team*) p->tmptr;
        p->tmptr = NULL;
        for (i = 0; i < t -> num; i++)
        {
            if (t->players[i]->plyrID == playerID)
            {
                k = i;
                break;
            }
        }
        for (i = k + 1; i < t -> num; i++)
            t -> players[i-1] = t->players[i];
        t->num = t->num - 1;
        if (t->num)
        {
            t->players = (Player**) realloc(t->players, (t->num) * sizeof(Player*));
            if(!t->players) return FAILURE;
        }
        else
        {
            free(t->players);
            t->players = NULL;
        }
        
    }
    return SUCCESS;
}

statusType deletePlayer(long playerID)
{
    PlayerNode *p, *q;
    statusType status = SUCCESS;
    p = findPlayer(playerID);
    if (p == NULL) status = MISSING_RECORD;
    else
    {
        if (p->tmptr) status = deletePlayerFromTeam(playerID);
        q = head.playerList;
        if (q->PL.plyrID == playerID)
        {
            head.playerList = q->next;
            free(p);
        }
        else
        {
            while (q->next)
            {
                if (q->next->PL.plyrID == p->PL.plyrID)
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
    int i;
    PlayerNode* p;
    Team *t, *s;
    t = findTeam(teamName);
    if (t == NULL) return MISSING_RECORD;
    else
    {
        if (t->players)
            for(i = 0; i < t->num; i++)
                deletePlayerFromTeam(t->players[i]->plyrID);
        if (t == head.teamList)
            head.teamList = t->next;
        else
        {
            s = head.teamList;
            while (s->next != t)
                s = s->next;
            s->next = t->next;
        }
        free(t);
    }
    return SUCCESS;
}

statusType joinPlayerToTeam(long playerID, char team[])
{
    PlayerNode* p;
    Team* t;
    p = findPlayer(playerID);
    t = findTeam(team);
    if (((p == NULL) || (t == NULL)) || (p->tmptr)) return MISSING_RECORD;
    else
    {
        p->tmptr = t;
        if (!t->num)
        {
            t->players = (Player**) malloc(sizeof(Player*));
            if (!t->players) return FAILURE;
            t->players[0] = &p->PL;
            t->num = 1;
        }
        else
        {
            t -> players = (Player**) realloc
                (t->players,(t->num + 1) * sizeof(Player*));
            if (!t->players) return FAILURE;
            t->players[t->num] = &p->PL;
            t -> num = t->num + 1;
        }
    }
    return SUCCESS;
}

statusType printPlayers()
{
    PlayerNode *p = head.playerList;

    if (!p) printf("No Players\n");
    else while (p)
    {
        printf("Name: %s %s\tID: %l\tAge: %d\n",
            p->PL.firstName, p->PL.lastName, p->PL.plyrID, p->PL.age);
        p = p->next;
    }
    
    return SUCCESS;
}

statusType printTeams()
{
    Team *t = head.teamList;

    if (!t) printf("No Teams\n");
    else while (t)
    {
        printf("Name: %s\n", t->teamName);
        t = t->next;
    }

    return SUCCESS;
}

statusType printTeamInfo(char teamName[])
{
    Team *t = findTeam(teamName);

    if (!t) return MISSING_RECORD;
    else
    {
        for (int i = 0; i < t->num; i++)
        {
            if (t->num)
            {
                printf("Name: %s %s\tID: %l\tAge: %d\n",
                    t->players[i]->firstName, t->players[i]->lastName,
                    t->players[i]->plyrID, t->players[i]->age);
            }
            else printf("0\n");
        }
    }
    
    return SUCCESS;
}

statusType freeHead()
{
    Team* t = head.teamList;
    PlayerNode* p = head.playerList;

    while (p)
    {
        if (deletePlayer(p->PL.plyrID) != SUCCESS) return FAILURE;
        p = head.playerList;
    }

    while (t)
    {
        if (deleteTeam(t->teamName) != SUCCESS) return FAILURE;
        t = head.teamList;
    }

    return SUCCESS;
}

statusType writeToFile()
{
    FILE *pFile = fopen(FILE1, "w+b");
    if (!pFile) return FILE_ERROR;
    Team *t = head.teamList;
    PlayerNode *p = head.playerList;
    Player **pptr;
    int size = 0;
    
    fwrite(&size, sizeof(int), 1, pFile);
    
    while (p)
    {
        size++;
        fwrite(p, sizeof(PlayerNode), 1, pFile);
        p = p->next;
    }

    long pos = ftell(pFile);
    rewind(pFile);
    fwrite(&size, sizeof(int), 1, pFile);
    fseek(pFile, pos, SEEK_SET);

    size = 0;

    fwrite(&size, sizeof(int), 1, pFile);

    while (t)
    {
        size++;
        t->players = pptr;
        t->players = NULL;
        fwrite(t, sizeof(Team), 1, pFile);
        fwrite(&t, sizeof(Team*), 1, pFile);
        t->players = pptr;
        t = t->next;
    }

    fseek(pFile, pos, SEEK_SET);
    fwrite(&size, sizeof(int), 1, pFile);

    fclose(pFile);

    return SUCCESS;
}

statusType readFromFile()
{
    FILE* pFile = fopen(FILE1, "rb");

    if (!pFile) return FILE_ERROR;

    int size;
    PlayerNode *p;

    fread(&size, sizeof(int), 1, pFile);
    while (size-- > 0 && !feof(pFile))
    {
        p = (PlayerNode*) malloc(sizeof(PlayerNode));
        if (!p) return FAILURE;
        fread(p, sizeof(PlayerNode), 1, pFile);
        p->next = head.playerList;
        head.playerList = p;
    }
    
    Team *t, *s;
    statusType stat;

    fread(&size, sizeof(int), 1, pFile);
    while(size-- > 0 && !feof(pFile))
    {
        t = (Team*) malloc(sizeof(Team));
        if (!t) return FAILURE;
        fread(t, sizeof(Team), 1, pFile);
        fread(&s, sizeof(Team*), 1, pFile);
        t->next = head.teamList;
        head.teamList = t;
        p = head.playerList;
        while (p)
        {
            if(p->tmptr == s)
            {
                p->tmptr = NULL;
                stat = joinPlayerToTeam(p->PL.plyrID, t->teamName);
                if (stat != SUCCESS) return stat;
            }
            p = p->next;
        }
    }

    fclose(pFile);

    return SUCCESS;
}

int main()
{


    return 0;
}
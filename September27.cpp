#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE1 "PROJECT1.DAT"
#define STRMAX 50

typedef enum {FAILURE, SUCCESS, INVALID_INPUT, FILE_ERROR,
            DUPLICATE_RECORD, MISSING_RECORD, EXIT} statusType;

typedef enum {FALSE, TRUE} boolean;

typedef struct Player
{
    char *plyrID;
    char *firstName;
    char *lastName;
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
    char *teamName;
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

PlayerNode* findPlayer(char *playerID)
{
    PlayerNode *p = head.playerList;

    while (p)
    {
        if (!strcmp(p->PL.plyrID, playerID)) return p;
        p = p->next;
    }

    return NULL;
}

Team* findTeam(char *name)
{
    Team *t = head.teamList;

    while (t)
    {
        if (!strcmp(t->teamName, name)) return t;
        t = t->next;
    }

    return NULL;
}

statusType insertPlayer(char *playerID, char *firstName, char *lastName, int age)
{
    PlayerNode *p, *q;
    q = findPlayer(playerID);
    if (q) return DUPLICATE_RECORD;
    p = (PlayerNode*) malloc(sizeof(PlayerNode));
    if (!p) return FAILURE;
    p->PL.plyrID = playerID;
    p->PL.firstName = firstName;
    p->PL.lastName = lastName;
    p->PL.age = age;
    p->tmptr = NULL;
    p -> next = head.playerList;
    head.playerList = p;
    return SUCCESS;
}

statusType insertTeam(char *name)
{
    Team* t = findTeam(name);
    if (t) return DUPLICATE_RECORD;
    t = (Team*) malloc(sizeof(Team));
    if (!t) return FAILURE;
    t->teamName = name;
    t->num = 0;
    t->players = NULL;
    t->next = head.teamList;
    head.teamList = t;
    return SUCCESS;
}

statusType deletePlayerFromTeam(char *playerID)
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
            if (!strcmp(t->players[i]->plyrID, playerID))
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

statusType deletePlayer(char *playerID)
{
    PlayerNode *p, *q;
    statusType status = SUCCESS;
    p = findPlayer(playerID);
    if (p == NULL) status = MISSING_RECORD;
    else
    {
        if (p->tmptr) status = deletePlayerFromTeam(playerID);
        q = head.playerList;
        if (!strcmp(q->PL.plyrID, playerID))
        {
            head.playerList = q->next;
            free(p->PL.plyrID);
            free(p->PL.firstName);
            free(p->PL.lastName);
            free(p);
        }
        else
        {
            while (q->next)
            {
                if (!strcmp(q->next->PL.plyrID, p->PL.plyrID))
                {
                    q->next = p->next;
                    free(p->PL.plyrID);
                    free(p->PL.firstName);
                    free(p->PL.lastName);
                    free(p);
                    break;
                }
                q = q->next;
            }
        }
    }
    return status;
}

statusType deleteTeam(char *name)
{
    int i;
    PlayerNode* p;
    Team *t, *s;
    t = findTeam(name);
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
        free(t->teamName);
        free(t);
    }
    return SUCCESS;
}

statusType joinPlayerToTeam(char *playerID, char *team)
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
        printf("Name: %s %s\t\tID: %s\tAge: %d\n",
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
        printf("Team: %s\n", t->teamName);
        t = t->next;
    }

    return SUCCESS;
}

statusType printTeamInfo(char *name)
{
    Team *t = findTeam(name);

    if (!t) return MISSING_RECORD;
    else
    {
        if (t->num)
            for (int i = 0; i < t->num; i++)
                printf("Name: %s %s\t\tID: %s\tAge: %d\n",
                    t->players[i]->firstName, t->players[i]->lastName,
                    t->players[i]->plyrID, t->players[i]->age);
        else printf("0\n");
    }
    return SUCCESS;
}

int playerCmp(const void* a, const void* b)
{
    Player *pa = *(Player**)a;
    Player *pb = *(Player**)a;

    return strcmp(pb->lastName, pa->lastName);
}

statusType playerSort(char *name)
{
    Team* t = findTeam(name);
    if (!t || !t->players) return MISSING_RECORD;

    qsort(t->players, t->num, sizeof(Player*), playerCmp);

    return printTeamInfo(name);
}

statusType teamNameSort()
{
    int count = 0;
    for (Team* s = head.teamList; s; s = s->next) count++;
    if (!count) return MISSING_RECORD;
    Team *t, *s;
    
    for (int i = 1; i < count; i++)
    {
        t = head.teamList;
        s = t->next;
        for (int j = 1; j <= count - i && t && s; j++)
        {
            s = t->next;
            if (strcmp(t->teamName, s->teamName) > 0)
            {
                t->next = s->next;
                s->next = head.teamList;
                head.teamList = s;
            }
            else t = t->next;
        }
    }
    return SUCCESS;
}

statusType teamSizeSort()
{
    int count = 0;
    for (Team* s = head.teamList; s; s = s->next) count++;
    if (!count) return MISSING_RECORD;
    Team *t, *s;
    
    for (int i = 1; i < count; i++)
    {
        t = head.teamList;
        for (int j = 1; j < count - i && t; j++)
        {
            s = t->next;
            if (t->num > s->num)
            {
                t->next = s->next;
                s->next = head.teamList;
                head.teamList = s;
            }
            t = t->next;
        }
    }
    return SUCCESS;
}

statusType isPlayerAvail(char *playerID)
{
    PlayerNode *p = findPlayer(playerID);
    if (!p) return MISSING_RECORD;
    else if (!p->tmptr) 
        printf("Player available\n");
    else printTeamInfo(p->tmptr->teamName);
    return SUCCESS;
}

char* getString()
{
    char str[STRMAX];
    scanf("%s", str);
    char* sans = (char*) malloc((strlen(str) + 1) * sizeof(char));
    strcpy(sans, str);
    return sans;
}

char* getTeam(boolean chained)
{
    char str[STRMAX];
    if (chained) getchar();
    gets(str);
    char* sans = (char*) malloc((strlen(str) + 1) * sizeof(char));
    strcpy(sans, str);
    return sans;
}

void writeDynString(FILE* pFile, char* str)
{
    int len = strlen(str);
    fwrite(&len, sizeof(int), 1, pFile);
    fwrite(str, sizeof(char), len, pFile);
}

statusType readDynString(FILE* pFile, char** str)
{
    int size;
    fread(&size, sizeof(int), 1, pFile);
    char *alloc = (char*) malloc((size + 1) * sizeof(char));
    if (!alloc) return FAILURE;
    alloc[size] = '\0';
    fread(alloc, sizeof(char), size, pFile);
    *str = alloc;
    return SUCCESS;
}

statusType writeToFile()
{
    FILE *pFile = fopen(FILE1, "w+b");
    if (!pFile) return FILE_ERROR;
    PlayerNode *p = head.playerList;
    Team *t = head.teamList;
    Player **pptr;
    int size = 0, num;
    
    fwrite(&size, sizeof(int), 1, pFile);
    
    while (p)
    {
        size++;
        fwrite(p, sizeof(PlayerNode), 1, pFile);
        writeDynString(pFile, p->PL.plyrID);
        writeDynString(pFile, p->PL.firstName);
        writeDynString(pFile, p->PL.lastName);
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
        pptr = t->players;
        num = t->num;
        t->num = 0;
        t->players = NULL;
        fwrite(t, sizeof(Team), 1, pFile);
        writeDynString(pFile, t->teamName);
        fwrite(&t, sizeof(Team*), 1, pFile);
        t->players = pptr;
        t->num = num;
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
        if (readDynString(pFile, &p->PL.plyrID) != SUCCESS) return FAILURE;
        if (readDynString(pFile, &p->PL.firstName) != SUCCESS) return FAILURE;
        if (readDynString(pFile, &p->PL.lastName) != SUCCESS) return FAILURE;
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
        if (readDynString(pFile, &t->teamName) != SUCCESS) return FAILURE;
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

boolean handleStatus(statusType s)
{
    switch(s)
    {
        case FAILURE:
            printf("Dynamic memory allocation error\n");
            return TRUE;
        case SUCCESS:
            printf("Success\n");

            break;
        case INVALID_INPUT:
            printf("Invalid input\n");

            break;
        case FILE_ERROR:
            printf("Error opening file\n");

            break;
        case DUPLICATE_RECORD:
            printf("Error\n");

            break;
        case MISSING_RECORD:
            printf("Error\n");

            break;
        case EXIT:
            printf("Bye\n");
            return TRUE;
        default:
            break;
    }

    return FALSE;
}

statusType exitProg()
{
    Team* t = head.teamList;
    PlayerNode* p = head.playerList;
    
    printf("Write changes to file? (1, 0)\n");
    fflush(stdin);
    if (getchar() == '1') 
        if (handleStatus(writeToFile()))
            return EXIT;

    while (p)
    {
        if (deletePlayer(p->PL.plyrID) == FAILURE) return FAILURE;
        p = head.playerList;
    }

    while (t)
    {
        if (deleteTeam(t->teamName) == FAILURE) return FAILURE;
        t = head.teamList;
    }

    return EXIT;
}

statusType select(int selection)
{
    statusType s;
    char* str = NULL;
    
    switch(selection)
    {
        case 1:
        {
            printf("Insert player, enter player info:\n");
            char *id = getString(), *fn = getString(), *ln = getString();
            int age;
            scanf("%d", &age);
            s = insertPlayer(id, fn, ln, age);

            break;
        }
        case 2:
        {
            printf("Find player, enter ID:\n");
            str = getString();
            PlayerNode *p = findPlayer(str);
            if (!p) s = MISSING_RECORD;
            else s = SUCCESS;

            break;
        }
        case 3:
            printf("Delete player, enter ID:\n");
            str = getString();
            s = deletePlayer(str);

            break;
        case 4:
        {
            printf("Insert team, enter name:\n");
            fflush(stdin);
            char *str2 = getTeam(FALSE);
            s = insertTeam(str2);

            break;
        }
        case 5:
        {
            printf("Find team, enter name:\n");
            fflush(stdin);
            str = getTeam(FALSE);
            Team *t = findTeam(str);
            if (!t) s = MISSING_RECORD;
            else s = SUCCESS;

            break;
        }
        case 6:
            printf("Delete team, enter name:\n");
            fflush(stdin);
            str = getTeam(FALSE);
            s = deleteTeam(str);

            break;
        case 7:
        {
            printf("Add player to team, enter ID and name:\n");
            str = getString();
            char *str2 = getTeam(TRUE);
            s = joinPlayerToTeam(str, str2);
            free(str2);

            break;
        }
        case 8:
            printf("Remove player from team, enter ID:\n");
            str = getString();
            s = deletePlayerFromTeam(str);

            break;
        case 9:
            printf("Players in the league:\n");
            s = printPlayers();

            break;
        case 10:
            printf("Teams in the league:\n");
            s = printTeams();

            break;
        case 11:
            printf("Enter team name to print:\n");
            fflush(stdin);
            str = getTeam(FALSE);
            s = printTeamInfo(str);

            break;
        case 12:
            printf("Enter team with players to sort:\n");
            fflush(stdin);
            str = getTeam(FALSE);
            s = playerSort(str);

            break;
        case 13:
            printf("Sorting teams by name...\n");
            s = teamNameSort();

            break;
        case 14:
            printf("Sorting teams by number of players...\n");
            s = teamSizeSort();

            break;
        case 15:
            printf("Check if player is available, insert ID:\n");
            str = getString();
            s = isPlayerAvail(str);

            break;
        case 16:
            s = exitProg();

            break;
        default:
            s = INVALID_INPUT;

            break;
    }
    if (str) free(str);

    return s;
}

// todo: fix team sorts
int main()
{
    head.teamList = NULL;
    head.playerList = NULL;

    boolean exit = FALSE;

    printf("Would you like to read from file? (1, 0)\n");
    fflush(stdin);
    if(getchar() == '1') exit = handleStatus(readFromFile());

    int selection = 0;

    while (!exit)
    {
        printf("Enter selection: (1-16)\n");
        fflush(stdin);
        scanf("%d", &selection);
        exit = handleStatus(select(selection));
    }

    return 0;
}
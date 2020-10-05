#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct PlayerNode* findPlayer(char* playerID)
{
	struct PlayerNode* p = head.playerList;

	while (p)
	{
		if (!strcmp(p->PL.plyrID, playerID)) return p;
		p = p->next;
	}

	return NULL;
}

struct Team* findTeam(char* name)
{
	struct Team* t = head.teamList;

	while (t)
	{
		if (!strcmp(t->teamName, name)) return t;
		t = t->next;
	}

	return NULL;
}

statusType insertPlayer(char* playerID, char* firstName, char* lastName, int age)
{
	struct PlayerNode* p, * q;
	q = findPlayer(playerID);
	if (q) return DUPLICATE_RECORD;
	p = (struct PlayerNode*)malloc(sizeof(struct PlayerNode));
	if (!p) return FAILURE;
	p->PL.plyrID = playerID;
	p->PL.firstName = firstName;
	p->PL.lastName = lastName;
	p->PL.age = age;
	p->tmptr = NULL;
	p->next = head.playerList;
	head.playerList = p;
	return SUCCESS;
}

statusType insertTeam(char* name)
{
	struct Team* t = findTeam(name);
	if (t) return DUPLICATE_RECORD;
	t = (struct Team*)malloc(sizeof(struct Team));
	if (!t) return FAILURE;
	t->teamName = name;
	t->num = 0;
	t->players = NULL;
	t->next = head.teamList;
	head.teamList = t;
	return SUCCESS;
}

statusType deletePlayerFromTeam(char* playerID)
{
	struct PlayerNode* p;
	struct Team* t;
	int i, k;
	p = findPlayer(playerID);
	if ((p == NULL) || (p->tmptr == NULL)) return MISSING_RECORD;
	else
	{
		t = (struct Team*)p->tmptr;
		p->tmptr = NULL;
		for (i = 0; i < t->num; i++)
		{
			if (!strcmp(t->players[i]->plyrID, playerID))
			{
				k = i;
				break;
			}
		}
		for (i = k + 1; i < t->num; i++)
			t->players[i - 1] = t->players[i];
		t->num = t->num - 1;
		if (t->num)
		{
			t->players = (struct Player**)realloc(t->players, (t->num) * sizeof(struct Player*));
			if (!t->players) return FAILURE;
		}
		else
		{
			free(t->players);
			t->players = NULL;
		}
	}
	return SUCCESS;
}

statusType deletePlayer(char* playerID)
{
	struct PlayerNode* p, * q;
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

statusType deleteTeam(char* name)
{
	int i;
	struct PlayerNode* p;
	struct Team* t, * s;
	t = findTeam(name);
	if (t == NULL) return MISSING_RECORD;
	else
	{
		if (t->players)
			for (i = 0; i < t->num; i++)
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

statusType joinPlayerToTeam(char* playerID, char* team)
{
	struct PlayerNode* p;
	struct Team* t;
	p = findPlayer(playerID);
	t = findTeam(team);
	if (((p == NULL) || (t == NULL)) || (p->tmptr)) return MISSING_RECORD;
	else
	{
		p->tmptr = t;
		if (!t->num)
		{
			t->players = (struct Player**)malloc(sizeof(struct Player*));
			if (!t->players) return FAILURE;
			t->players[0] = &p->PL;
			t->num = 1;
		}
		else
		{
			t->players = (struct Player**)realloc
			(t->players, (t->num + 1) * sizeof(struct Player*));
			if (!t->players) return FAILURE;
			t->players[t->num] = &p->PL;
			t->num = t->num + 1;
		}
	}
	return SUCCESS;
}

statusType printPlayers()
{
	struct PlayerNode* p = head.playerList;

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
	struct Team* t = head.teamList;

	if (!t) printf("No Teams\n");
	else while (t)
	{
		printf("Team: %s\n", t->teamName);
		t = t->next;
	}

	return SUCCESS;
}

statusType printTeamInfo(char* name)
{
	struct Team* t = findTeam(name);

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

statusType playerSort(char* name)
{
	struct Player* temp;
	struct Team* t = findTeam(name);
	if (!t || !t->players) return MISSING_RECORD;

	int ar_len = t->num;
	for (int i = 0; i < ar_len - 1; i++)
	{
		for (int k = 0; k < ar_len - i - 1; k++)
		{
			if (strcmp(t->players[k]->lastName, t->players[k + 1]->lastName) > 0)
			{
				temp = t->players[k];
				t->players[k] = t->players[k + 1];
				t->players[k + 1] = temp;
			}
		}
	}
	return printTeamInfo(name);
}

statusType teamNameSort()
{
	int i, j, swa = 1, count = 0;
	for (struct Team* t = head.teamList; t; t = t->next) count++;
	if (!count) return MISSING_RECORD;
	struct Team* temp, * x, * t, * s;

	for (i = 0; i < count && swa; i++)
	{
		t = head.teamList;
		s = t;
		swa = 0;
		for (j = 0; j < count - i - 1; j++)
		{
			x = t->next;
			if (strcmp(t->teamName, x->teamName) > 0)
			{
				if (t == head.teamList)
				{
					temp = x->next;
					head.teamList = x;
					head.teamList->next = t;
					t->next = temp;
				}
				else
				{
					temp = x->next;
					x->next = t;
					t->next = temp;
					s->next = x;
				}
				s = x;
				swa = 1;
			}
			else
			{
				s = t;
				t = t->next;
			}
		}
	}
	return SUCCESS;
}

statusType teamSizeSort()
{
	int i, j, swa = 1, count = 0;
	for (struct Team* t = head.teamList; t; t = t->next) count++;
	if (!count) return MISSING_RECORD;
	struct Team* temp, * x, * t, * s;

	for (i = 0; i < count && swa; i++)
	{
		t = head.teamList;
		s = t;
		swa = 0;
		for (j = 0; j < count - i - 1; j++)
		{
			x = t->next;
			if (t->num > x->num)
			{
				if (t == head.teamList)
				{
					temp = x->next;
					head.teamList = x;
					head.teamList->next = t;
					t->next = temp;
				}
				else
				{
					temp = x->next;
					x->next = t;
					t->next = temp;
					s->next = x;
				}
				s = x;
				swa = 1;
			}
			else
			{
				s = t;
				t = t->next;
			}
		}
	}
	return SUCCESS;
}

statusType isPlayerAvail(char* playerID)
{
	struct PlayerNode* p = findPlayer(playerID);
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
	char* sans = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!sans) return sans;
	strcpy(sans, str);
	return sans;
}

char* getTeam()
{
	char c = getchar();
	char* sans = (char*)malloc(sizeof(char));
	if (!sans) return sans;
	int size = 0;
	while ((c = getchar()) != '\n' && size++ <= STRMAX)
	{
		if (c == ' ' && size == 1)
		{
			size--;
			continue;
		}
		sans = (char*)realloc(sans, (size + 1) * sizeof(char));
		if (!sans) return sans;
		sans[size - 1] = c;
		sans[size] = '\0';
	}
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
	char* alloc = (char*)malloc((size + 1) * sizeof(char));
	if (!alloc) return FAILURE;
	alloc[size] = '\0';
	fread(alloc, sizeof(char), size, pFile);
	*str = alloc;
	return SUCCESS;
}

statusType writeToFile()
{
	FILE* pFile = fopen(FILE1, "w+b");
	if (!pFile) return FILE_ERROR;
	struct PlayerNode* p = head.playerList;
	struct Team* t = head.teamList;
	struct Player** pptr;
	int size = 0, num;

	fwrite(&size, sizeof(int), 1, pFile);

	while (p)
	{
		size++;
		fwrite(p, sizeof(struct PlayerNode), 1, pFile);
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
		writeDynString(pFile, t->teamName);
		fwrite(&t, sizeof(struct Team*), 1, pFile);
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
	struct PlayerNode* p;

	fread(&size, sizeof(int), 1, pFile);
	while (size-- > 0 && !feof(pFile))
	{
		p = (struct PlayerNode*)malloc(sizeof(struct PlayerNode));
		if (!p) return FAILURE;
		fread(p, sizeof(struct PlayerNode), 1, pFile);
		if (readDynString(pFile, &p->PL.plyrID) == FAILURE) return FAILURE;
		if (readDynString(pFile, &p->PL.firstName) == FAILURE) return FAILURE;
		if (readDynString(pFile, &p->PL.lastName) == FAILURE) return FAILURE;
		p->next = head.playerList;
		head.playerList = p;
	}

	struct Team* s;
	char* c;

	fread(&size, sizeof(int), 1, pFile);
	while (size-- > 0 && !feof(pFile))
	{
		if (readDynString(pFile, &c) == FAILURE) return FAILURE;
		if (insertTeam(c) == FAILURE) return FAILURE;
		fread(&s, sizeof(struct Team*), 1, pFile);
		p = head.playerList;
		while (p)
		{
			if (p->tmptr == s)
			{
				p->tmptr = NULL;
				if (joinPlayerToTeam(p->PL.plyrID, c) == FAILURE) return FAILURE;
			}
			p = p->next;
		}
	}

	fclose(pFile);

	return SUCCESS;
}

boolean handleStatus(statusType s)
{
	switch (s)
	{
	case FAILURE:
		printf("Allocation Error\n");
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
	struct Team* t = head.teamList;
	struct PlayerNode* p = head.playerList;

	printf("Write changes to file? (1, 0)\n");
	fflush(stdin);
	getchar();
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

	switch (selection)
	{
	case 1:
	{
		printf("Insert player, enter player info:\n");
		char* id = getString(), * fn = getString(), * ln = getString();
		if (!id || !fn || !ln) return FAILURE;
		int age;
		scanf("%d", &age);
		s = insertPlayer(id, fn, ln, age);

		break;
	}
	case 2:
	{
		printf("Find player, enter ID:\n");
		str = getString();
		if (!str) return FAILURE;
		struct PlayerNode* p = findPlayer(str);
		if (!p) s = MISSING_RECORD;
		else s = SUCCESS;

		break;
	}
	case 3:
		printf("Delete player, enter ID:\n");
		str = getString();
		if (!str) return FAILURE;
		s = deletePlayer(str);

		break;
	case 4:
	{
		printf("Insert team, enter name:\n");
		fflush(stdin);
		char* str2 = getTeam();
		if (!str2) return FAILURE;
		s = insertTeam(str2);

		break;
	}
	case 5:
	{
		printf("Find team, enter name:\n");
		fflush(stdin);
		str = getTeam();
		if (!str) return FAILURE;
		struct Team* t = findTeam(str);
		if (!t) s = MISSING_RECORD;
		else s = SUCCESS;

		break;
	}
	case 6:
		printf("Delete team, enter name:\n");
		fflush(stdin);
		str = getTeam();
		if (!str) return FAILURE;
		s = deleteTeam(str);

		break;
	case 7:
	{
		printf("Add player to team, enter ID and name:\n");
		str = getString();
		char* str2 = getTeam();
		if (!str || !str2) return FAILURE;
		s = joinPlayerToTeam(str, str2);
		free(str2);

		break;
	}
	case 8:
		printf("Remove player from team, enter ID:\n");
		str = getString();
		if (!str) return FAILURE;
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
		str = getTeam();
		if (!str) return FAILURE;
		s = printTeamInfo(str);

		break;
	case 12:
		printf("Enter team with players to sort:\n");
		fflush(stdin);
		str = getTeam();
		if (!str) return FAILURE;
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
		if (!str) return FAILURE;
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
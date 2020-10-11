#include "header.h"

headder head;

int main()
{
	head.teamList = NULL;
	head.playerList = NULL;

	boolean exit = FALSE;

	printf("Would you like to read from file? (1, 0)\n");
	fflush(stdin);
	if (getchar() == '1') exit = handleStatus(readFromFile());

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
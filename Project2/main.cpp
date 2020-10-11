#include "header.h"

int main()
{
	int exit = 0, choice = 0;

	while (!exit)
	{
		printf("1. Polynoms\n2. Bulk\n3. Exit\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			polyMain();
			break;
		case 2:
			bulkMain();
			break;
		case 3:
			exit = 1;
			break;
		default:
			printf("Invalid Choice\n");
			break;
		}
	}


	return 0;
}
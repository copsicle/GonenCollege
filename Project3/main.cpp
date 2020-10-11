#include "header.h"

void main()
{
	// Arrays of names
	const char* names[MAX] = { "Sasson_Sassoni", "Pooh", "James_Bond",
	"Elvis_is_Alive!", "Shilgiya", "Cleopatra", "Sissoo_VeSimmhoo" };
	// Matrix of dates of birth
	const int dates[MAX][COLS] =
	{
		{10, 1, 1988},
		{12, 12, 1948},
		{4, 12, 1970},
		{11, 11, 1890},
		{11, 11, 1948},
		{1, 10, 1213},
		{12, 11, 1948}
	};
	// The file name
	const char* f_name = "Persons.txt";

	char c;
	int counter = 0;
	Person* pArr = NULL;

	while (1)
	{
		printf("Press 1 to add a new person to the list:\n\n");
		printf("Press 2 to print all persons in the list:\n\n");
		printf("Press 3 to sort all persons by ages, ");
		printf("and then print the sorted list:\n\n");
		printf("Press 4 to save current list to file:\n\n");
		printf("Press 5 to read the file into the list:\n\n");
		printf("Press E or e to exit the program:\n\n\n");
		printf("======> ");
		
		scanf(" %c", &c);
		printf("\n");

		switch (c)
		{
		case '1':
			addToList(names, dates, &counter, &pArr);
			break;
		case '2':
			printf("Current list:\n\n");
			printList(pArr, counter);
			break;
		case '3':
			sortList(pArr, counter);
			break;
		case '4':
			writeFile(f_name, pArr, counter);
			break;
		case '5':
			readFile(f_name, &pArr, &counter);
			break;
		case 'E':
		case 'e':
			printf("The program ends now...\n\nGood bye...\n\n");
			freeList(&pArr, &counter);
			exit(0);
			break;
		default:
			printf("Invalid Choice\n\n");
			break;
		}
	}

}
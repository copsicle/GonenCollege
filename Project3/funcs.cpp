#include "header.h"

void printPerson(Person* p)
{
	printf("%2d %-20s\t%2d %2d %4d\n",
		p->serial_num, p->full_name, p->pDate->day, p->pDate->month, p->pDate->year);
}

void printList(Person* arr, int count)
{
	for (int i = 0; i < count; i++)
		printPerson(&arr[i]);

	printf("\n");
}

void freeList(Person** arr, int* count)
{
	for (int i = 0; i < *count; i++)
		free((*arr)[i].pDate);

	free(*arr);
	*arr = NULL;
	*count = 0;
}

void addToList(const char* names[], const int dates[][COLS], int* count, Person** arr)
{
	if (*count == MAX)
	{
		printf("All people loaded\n\n");
		return;
	}

	*arr = (Person*)realloc(*arr, (*count + 1) * sizeof(Person));
	if (!(*arr)) exit(1);
	
	Person* tmp = &(*arr)[*count];

	tmp->pDate = (Date*)malloc(sizeof(Date));
	if (!(tmp->pDate)) exit(1);

	tmp->serial_num = *count + 1;
	strcpy(tmp->full_name, names[*count]);
	
	tmp->pDate->day = dates[*count][0];
	tmp->pDate->month = dates[*count][1];
	tmp->pDate->year = dates[*count][2];

	printPerson(tmp);
	printf("\n");

	(*count)++;
}

int cmpPerson(const void* a, const void* b)
{
	Person* ap = (Person*)a, * bp = (Person*)b;
	
	if (ap->pDate->year != bp->pDate->year)
		return ap->pDate->year - bp->pDate->year;
	
	else if (ap->pDate->month != bp->pDate->month)
		return ap->pDate->month - bp->pDate->month;
	
	else return ap->pDate->day - bp->pDate->day;
}

void sortList(Person* arr, int count)
{
	qsort(arr, count, sizeof(Person), cmpPerson);
	printf("Current list sorted by age:\n\n");
	printList(arr, count);
}

void writeFile(const char* fn, Person* arr, int count)
{
	FILE* pFile;
	if (!(pFile = fopen(fn, "wt"))) exit(1);

	for (int i = 0; i < count; i++)
		fprintf(pFile, "%2d %-20s\t%2d %2d %4d\n",
			arr[i].serial_num, arr[i].full_name,
			arr[i].pDate->day, arr[i].pDate->month, arr[i].pDate->year);

	fclose(pFile);

	printf("File is saved.\n\n");
}

void readFile(const char* fn, Person** arr, int* count)
{
	FILE* pFile;
	if (!(pFile = fopen(fn, "rt"))) exit(1);

	freeList(arr, count);

	while (!feof(pFile))
	{	
		*arr = (Person*)realloc(*arr, (*count + 1) * sizeof(Person));
		if (!(*arr)) exit(1);
		
		Person* tmp = &(*arr)[*count];

		tmp->pDate = (Date*)malloc(sizeof(Date));
		if (!(tmp->pDate)) exit(1);

		fscanf(pFile, "%d %s %d %d %d\n",
			&tmp->serial_num, tmp->full_name,
			&tmp->pDate->day, &tmp->pDate->month, &tmp->pDate->year);

		(*count)++;
	}

	fclose(pFile);

	printf("File is loaded.\n\n");
}
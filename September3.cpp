#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void dateexercise()
{
	int day, month, year, days;

	scanf("%d.%d.%d", &day, &month, &year);

	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: days = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11: days = 30;
		break;
	case 2: days = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) ? 29 : 28);
		break;
	}

	if (day + 1 > days)
	{
		if (month + 1 > 12)
		{
			year++;
			day = 1;
			month = 1;
		}
		else
		{
			month++;
			day = 1;
		}
	}
	else day++;

	printf("tomorrow is %d.%d.%d \n", day, month, year);
}

void angleexercise()
{

}

void main()
{
	dateexercise();
	angleexercise();
}
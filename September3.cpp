#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void dateexercise()
{
	int day, month, year, days = 30;

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

		if ((month > 12 || month < 1) || (day > days || day < 1)) 
		{
			printf("invalid");
			return;
		}

		(day == days) ? ((month == 12) ? year++, month = 1, day = 1 : month++, day = 1) : day++;

		printf("tomorrow is %d.%d.%d \n", day, month, year);
}

void angleexercise()
{
	int angle;
	
	scanf("%d", &angle);

	while (angle < 0) angle += 360;

	switch (angle / 90)
	{
	//case 0: printf(());
	case 1: printf("90 degrees");
		break;
	case 2:
		break;
	}
}

void main()
{
	dateexercise();
	//angleexercise();
}
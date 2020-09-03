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
	angle = (angle > 360) ? angle % 360 : angle;
	
	switch (angle / 90)
	{
	case 0: printf((angle > 0) ? "hada" : "0 degrees");
		break;
	case 1: printf((angle > 90) ? "keha" : "90 degrees");
		break;
	case 2: printf("180 degrees");
		break;
	}
}

void f1()
{
	int a, b, x, y;
	a = 9;
	b = 5;
	printf("a=%d b=%d result=%d\n", a, b, a + ++b);
	printf("a=%d b=%d result=%d\n", a, b, --b - a++);
	printf("a=%d b=%d result=%d\n", a, b, a++ + b);
	printf("a=%d b=%d result=%d\n", a, b, a-- + b);
	printf("a=%d b=%d result=%d\n", a, b, -a + b++);
}

void f2()
{

}

void f3()
{
	printf("\tmuse \tHORS \nnavada\n");
}

void f4()
{
	int x = 12, y = 9;
	printf("%d\n", y += x * y + 5 % 2);
}

void f5()
{
	printf("\123\105\122\123");
}

void main()
{
	
	dateexercise();
	angleexercise();
	f1();
	f2();
	f3();
	f4();
	f5();
}
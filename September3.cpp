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
			printf("invalid \n");
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
	case 0: printf((angle > 0) ? "hada \n" : "0 degrees \n");
		break;
	case 1: printf((angle > 90) ? "keha \n" : "90 degrees \n");
		break;
	case 2: printf("180 degrees \n");
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
	printf("\123\105\122\123 \n");
}

void exercise1()
{
	int num1, num2, pos = 0, neg = 0, possum = 0;

	scanf("%d", &num1);
	
	for (int i = 0; i < num1; i++)
	{
		scanf("%d", &num2);
		if (num2 != 0) (num2 > 0) ? pos++, possum += num2 : neg++;
	}

	printf("positive: %d negative: %d positive sum: %d", pos, neg, possum / pos);
}

void exercise2()
{
	int a, b, c, avg, bigavg = 0, otheravg = 0, count = 0;

	for (int i = 0; i < 100; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		avg = (a + b + c) / 3;
		printf("average %d \n", avg);
		printf((a == avg) ? "YES \n" : "NO \n");
		bigavg += avg;
		if (a == b && b == c)
		{
			count++;
			otheravg += a;
		}
	}

	printf("big average %d, equal average %d \n", bigavg / 100, otheravg / count);
}

void exercise3()
{
	int male, female, fams, count = 0, favg = 0;

	scanf("%d", &fams);

	for (int i = 0; i < fams; i++)
	{
		scanf("%d %d", &male, &female);
		
		if (male == female) count++;

		printf("number of kids %d \n", male + female);

		favg += female;
	}

	printf("num of equals: %d average female count: %d \n", count, favg / fams);
}

void exercise4()
{

}

void main()
{
	/*
	dateexercise();
	angleexercise();
	f1();
	f2();
	f3();
	f4();
	f5();
	exercise1();
	exercise2();
	*/
	exercise3();
}
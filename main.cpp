#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void exercise1()
{
	float a, b, c;
	
	scanf("%d %d %d", &a, &b, &c);
	
	if (a == 0)
	{
		if (b == 0) printf("no answer \n");
		else printf("x is %.2f \n", (c * -1) / b);
	}
	else printf("x1 is %.2f and x2 is %.2f \n",
		((b * -1) + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a),
		((b * -1) - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
}

void exercise2()
{
	float a, b, c;
	
	scanf("%f %f %f", &a, &b, &c);
	
	if (a == b && b == c) printf("Equilateral \n");
	else if (a == b || b == c || c == a) printf("Isosceles \n");
	else if (pow(a, 2) + pow(b, 2) == pow(c, 2) ||
		pow(b, 2) + pow(c, 2) == pow(a, 2) ||
		pow(c, 2) + pow(a, 2) == pow(b, 2))
		printf("Right \n");
	else printf("Scalene \n");
}

void exercise3()
{
	int day, month, year, days;

	scanf("%d %d %d", &day, &month, &year);

	switch (month)
	{
	case 1: 
		days = 31;
		break;
	case 2:
		if (year % 4 == 0) days = 29;
		else days == 28;
		break;
	case 3: 
		days = 31;
		break;
	case 4: 
		days = 30;
		break;
	case 5: 
		days = 31;
		break;
	case 6:
		days = 30;
		break;
	case 7:
		days = 31;
		break;
	case 8:
		days = 31;
		break;
	case 9:
		days = 30;
		break;
	case 10:
		days = 31;
		break;
	case 11:
		days = 30;
		break;
	case 12:
		days = 31;
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

	printf("tomorrow is %d/%d/%d \n", day, month, year);
}

void exercise4()
{
	char a, b;
	int c, d;
	
	for (int i = 0; i < 20; i++)
	{
		scanf(" %c %c", &a, &b);
		printf("%d %d \n", a, b);
		
		c = (int)a; 
		d = (int)b;
		
		if (c > d) printf("%d \n", (122 - c) + (d - 97));
		else if (c < d) printf("%d \n", (122 - d) + (c - 97));
		else printf("0 \n");
	}
}

void exercise6()
{
	char a;
	float b, count = 0.1, sum = 0;

	scanf(" %c", &a);

	while (a != '*')
	{	
		if (a == '.')
		{
			scanf(" %c", &a);
			while (a != '*')
			{
				b = (int)a - 48;
				sum += (b * count);
				count *= count;
				
				scanf(" %c", &a);
			}
			break;
		}
		b = (int)a - 48;
		sum = (sum * 10) + b;
		
		scanf(" %c", &a);
	}
	printf("%f \n", sum);
}

void exercise32()
{
	char a;
	int b, sum = 0, mul = 1, ans = 0;

	scanf(" %c", &a);

	while (a != '*')
	{
		b = (int)a - 48;
		sum = (sum * 10) + b;
		scanf(" %c", &a);
	}
	
	while (sum > 10)
	{
		ans += (sum % 10) * mul;
		sum /= 10;
		mul *= 8;
	}
	ans += sum * mul;

	printf("%d \n", ans);
}

void exercise42()
{
	int a, mul1 = 1, mul2 = 1;

	scanf("%d", &a);

	while (a / mul1 > 10) mul1 *= 10;
	
	int c = a % 10, d = a / mul1;

	// mul1 != mul2 || (mul1 != mul2 * 10)

	while (1)
	{
		if (c != d)
		{
			printf("%d is not palindrome \n", a);
			break;
		}
		else if (mul1 == mul2 || mul1 == mul2 * 10)
		{
			printf("%d is palindrome \n", a);
			break;
		}

		mul1 /= 10;
		mul2 *= 10;

		c = (a / mul2) % 10;
		d = (a / mul1) % 10;
	}
}

void exercise5()
{
	int a, b, mul1 = 1, mul2 = -1, sum = 0;

	scanf("%d", &a);

	while (a > 0)
	{
		mul2 *= -1;
		mul1 += mul2;
		b = (a % 10) * mul1;
		if (b >= 10) sum += (b % 10) + (b / 10);
		else sum += b;
		a /= 10;
	}
	
	printf("the last digit is %d \n", 10 - (sum % 10));
}

void randexercise()
{
	srand((unsigned)time(NULL));
	int r1 = rand() % 11;
	printf("%d \n", r1);
}

void main()
{	
	exercise1();
	exercise2();
	exercise4();
	exercise6();
	exercise32();
	exercise42();
	exercise5();
	randexercise();
	exercise3();
}
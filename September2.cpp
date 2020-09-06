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

void exercise4()
{
	char a, b;
	int c, d;
	
	for (int i = 0; i < 20; i++)
	{
		scanf(" %c %c", &a, &b);
		//printf("%d %d \n", a, b);
		
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
		sum += (b >= 10 ? (b % 10) + (b / 10) : b);
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

int main()
{	
	exercise1();
	exercise2();
	exercise4();
	exercise6();
	exercise32();
	exercise42();
	exercise5();
	randexercise();

	return 0;
}
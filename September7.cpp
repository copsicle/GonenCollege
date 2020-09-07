#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int exercise1(int num, int dig);

int exercise2a(int num1, int num2);
void exercise2b();

int exercise3a(int num);
void exercise3b();

int exercise4a(int num);
void exercise4b();

int main()
{
    srand(time(NULL));
    /*
    printf("%d \n", exercise1(4204204, 4));
    exercise2b();
    exercise3b();
    */
    exercise4b();

    return 0;
}

int exercise1(int num, int dig)
{
    int count = 0;

    while (num != 0)
    {
        if (num % 10 == dig) count++;
        num /= 10;
    }

    return count;
}

int exercise2a(int num1, int num2)
{
    return (rand() % (num2 - --num1)) + num1 + 1; 
}

void exercise2b()
{
    int num1, num2;

    scanf("%d %d", &num1, &num2);

    while (num1 != -999 && num2 != -999) 
    {
        for (int i = 0; i < 5; i++) printf("%d \n", exercise2a(num1, num2));
        scanf("%d %d", &num1, &num2);
    }
}

int exercise3a(int num)
{
    int sum = 0;

	while (num != 0)
	{
		sum += num % 10;
		num /= 10;
	}

    return sum;
}

void exercise3b()
{
    int n, num, permnum, sum = 0, res;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        
        res = exercise3a(num);

        if (res >= sum || i == 0)
        {
            permnum = num;
            sum = res;
        }
    }

    printf("The last number with the biggest sum of digits is %d with a sum of %d \n", permnum, sum);
}


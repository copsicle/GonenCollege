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

int exercise5a(int num);
void exercise5b();

void exercise6a(int num, int digit);
void exercise6b();

void exercise7a(int num);
void exercise7b();

int main()
{
    srand(time(NULL));
    /*
    printf("%d \n", exercise1(4204204, 4));
    exercise2b();
    exercise3b();
    exercise4b();
    exercise5b();
    exercise6b();
    */


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

int exercise4a(int num)
{
    int cur = 1, sum = 0;

    while (cur != num && num > 1) 
    {
        if (num % cur == 0) sum += cur;
        cur++;
    }

    return (num == sum) ? 1 : 0;
}

void exercise4b() { for (int i = 10; i <= 1000; i++) if (exercise4a(i)) printf("%d \n", i); }

int exercise5a(int num)
{
    int digit, temp;

    while (num != 0)
    {
        digit = num % 10;
        num /= 10;
        temp = num;
        while (digit != (temp % 10) && temp > 0) temp /= 10;
        if (temp > 0) return 0;
    }

    return 1;
}

void exercise5b()
{
    int ans = 0, num, count = 0;
    
    while (!ans)
    {
        scanf("%d", &num);
        count++;
        ans = exercise5a(num);
    }

    printf("good number was %d and %d numbers were tested before it \n", num, --count);
}

void exercise6a(int num, int digit)
{
    int count = 0;

    for (int i = 1; num > 0; i++)
    {
        if (num % 10 == digit)
        {
            printf("%d ", i);
            count++;
        } 
        num /= 10;
    }

    printf((count == 0) ? "0 \n \n" : "\n \n");
}

void exercise6b()
{
    int num;

    scanf("%d", &num);

    for (int i = 0; i <= 9; i++)
    {
        printf("%d \n", i);
        exercise6a(num, i);
    }
}

void exercise7a(int num)
{
    
}
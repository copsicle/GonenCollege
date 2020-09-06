#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void algoexercise()
{
    int sum = 0, n, num, last = 0, mid, num1 = 0, num2 = 0;

    scanf("%d", &n);

    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &num);

        sum += num;

        if (i == (n / 2) + 1) mid = num;

        if ((i > 2 && num - last < num2 - num1) || i == 2)
        {
            num1 = last;
            num2 = num;
        }

        last = num;
    }

    printf("average is %d numbers are %d %d and the diff is %d the mid is %d \n", sum / n, num1, num2, num2 - num1, mid);
}

int main()
{
    algoexercise();

    return 0;
}
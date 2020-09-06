#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

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

void calcexercise1()
{
    long a, b, c, count1 = 0, ans = 0, mod = 0, div = 0, count2 = 0;

    scanf("%d %d %d", &a, &b, &c);

    while (a > 0)
    {
        if (b == 10)
        {
            if (b == c)
            {
                ans = a;
                break;
            }
            div = (a/c);
            ans += (a - (div*c)) * pow(10, count1++);
            a = div;
        }
        else
        {
            if (a % 10 >= b)
            {
                ans = 0;
                break;
            }

            ans += (a % 10) * pow(b, count2++);
            a /= 10;

            if (a == 0)
            {
                a = ans;
                ans = 0;
                b = 10;
            }
        }
    }

    if ((a == 0 || ans != 0)) printf("%d \n", ans);
    else printf("ERROR \n");
}

void calcexercise2()
{
    char c;

    while(c = getchar() != '_')
    {
        switch (c)
        {
        }
    }

    printf("bye \n");
}

int main()
{
    /*
    algoexercise();
    */
    calcexercise1();
    return 0;
}
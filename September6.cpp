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
    int a, b, c, count1 = 0, ans = 0, mod = 0, div = 0, count2 = 0;

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
    int num1, num2;
    float num, sum;

    scanf(" %c", &c);

    while(c != '_')
    {
        switch (c)
        {
        case '+':
        case '*':
            scanf("%f", &num);
            sum = (c == '+') ? 0.0f : 1.0f;
            while ((c == '+') ? num != 0 : num != 1)
            {
                sum = (c == '+') ? sum + num : sum * num;
                scanf("%f", &num);
            }
            printf("%f \n", sum);
            break;
        case '-':
        case '/':
        case '^':
            scanf("%d %d", &num1, &num2);
            if (c == '-') printf("%d \n", num1 - num2);
            else if (c == '/')
            {
                if (num1 != 0) printf("%d \n", num2 / num1);
                else
                {
                    printf("ERROR \n");
                    break;
                }
                if (num2 % num1 != 0) printf("%d \n", num2 % num1);
            }
            else printf("%f \n", pow(num1, num2));
            break;
        default:
            printf("??? \n");
        }

        scanf(" %c", &c);
    }

    printf("bye \n");
}

int main()
{
    algoexercise();
    calcexercise1();
    calcexercise2();

    return 0;
}
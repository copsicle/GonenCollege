#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int find5(int num)
{
    if (num % 5 == 0)
        return 1;
    else if (num < 10)
        return 0;
    else return find5(num / 10);
}

int sumDigits(int num)
{
    if (num < 10)
        return num;
    
    return num % 10 + sumDigits(num / 10);
}

int sumPosDigits(int num)
{
    if (num < 10 && num % 2 == 0)
        return num;
    else if (num % 2 == 0)
        return num % 10 + sumPosDigits(num / 10);
    else if (num < 10) return 0;
    else return sumPosDigits(num / 10);
}

int findOdd(int num)
{
    if (num % 2 != 0) return 1;
    else if (num < 10) return 0;
    else return findOdd(num / 10);
}

int isRising(int num)
{
    
}

int main()
{
    int num = 13245;
    printf("%d\n", find5(num));
    printf("%d\n", sumDigits(num));
    printf("%d\n", sumPosDigits(num));
    printf("%d\n", findOdd(num));
    printf("%d\n", isRising(num));


    return 0;
}
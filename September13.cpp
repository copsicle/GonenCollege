#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define STRMAX 255

void exercise1(char str[])
{
    int size;
    char temp;
    for (size = 0; str[size]; size++);

    size--;

    for (int i = 0; size != i && size != i + 1; i++, size--)
    {
        temp = str[i];
        str[i] = str[size];
        str[size] = temp;
    }
}

void itoa(int num, char str[])
{
    int count = 0;
    
    while (num > 0)
    {
        str[count++] = (num % 10) + '0';
        num /= 10;
    }

    exercise1(str);
}

void exercise2(char str[])
{
    printf("%s \n", str);

    int len = strlen(str);
    char temp1[len * 2 + 1];

    strcpy(temp1, str);
    strcat(temp1, temp1);
    printf("%s \n", temp1);

    char temp2[len * 2 + 1];

    strcpy(temp1, str);
    strcpy(temp2, str);
    exercise1(temp2);
    strcat(temp1, temp2);
    printf("%s \n", temp1);

    strcpy(temp1, str);

    char save = temp1[0];

    for (int i = 0, j = 0; i < len * 2 && temp1[i]; i++, j += 2)
    {
        temp2[j] = temp1[i];
        temp2[j + 1] = temp1[i];
        temp2[j + 2] = 0;
    }

    printf("%s \n", temp2);
}

void exercise3(char str1[], char str2[])
{
    int len1 = strlen(str1), len2 = strlen(str2), count = 0, expr = (len1 > len2);
    char str[(len1 > len2) ? len1 + 1 : len2 + 1], temp;

    for (int i = 0; i < (expr ? len1 : len2); i++)
    {
        if (strchr(expr ? str2 : str1, expr ? str1[i] : str2[i])) 
            str[count++] = (expr ? str1[i] : str2[i]);
    }

    strcpy(str1, str);
}

void exercise4(char str[])
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j <= i; j++) printf(" %c", str[j]);
        printf("\n");
    }
}

void exercise6()
{
    const int lim = 100;
    char starr[lim][lim];

    for (int i = 0; i < lim; i++) scanf("%s", starr[i]);

    for (int i = 0; i < lim; i++)
    {
        printf("%s ", starr[i]);
        if ( starr[i][strlen(starr[i]) - 1] == '.') printf("\n");
    }
}

void exercise7(char str1[], char str2[])
{
    int ind = -1, j, len = strlen(str2);

    for (int i = 0; i < strlen(str1); i++)
    {
        for (j = 0; str1[i + j] == str2[j] && j < len && str1[i + j]; j++);
        if (j == len) ind = i;
    }

    printf("%d \n", ind + 1);
}

void exercise11(char str1[], char str2[], char str3[])
{
    int j, len = strlen(str2);

    char temp[STRMAX];

    for (int i = 0; i < strlen(str1); i++)
    {
        for (j = 0; str1[i + j] == str2[j] && j < len && str1[i + j]; j++);
        if (j == len)
        {
            strcpy(temp, str1 + i + j);
            str1[i] = '\0';
            strcat(str1, str3);
            strcat(str1, temp);
            i += strlen(str3) - 1;
        }
    }
}

void exercise12(char str[])
{
    char temp[STRMAX];

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '*')
        {
            strcpy(temp, str + i + 1);
            str[i--] = '\0';
            strcat(str, temp);
        }
    }
}

void exercise14(char str[])
{
    int dig, even = 0, odd = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        dig = str[i] - '0';
        if (dig % 2 == 0)
        {
            even *= 10;
            even += dig;
        }
        else
        {
            odd *= 10;
            odd += dig;
        }
    }

    printf("%d \n", even + odd);
}

void exercise17()
{
    int num1, num2;
    scanf("%d %d", &num1, &num2);
    char a[STRMAX], b[STRMAX];
    itoa(num1, a);
    itoa(num2, b);
    strcat(a, b);
    printf("%s \n", a);
}

void exercise18()
{
    char input[STRMAX], temp[STRMAX], ch;
    scanf("%s", input);
    
    for (int i = 0; 1; i++)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            strcpy(temp, input + i + 1);
            int num = input[i] - '0' - 1; 
            for (int j = 0; j < num; j++)
            {
                input[i + j] = input[i - 1];
                input[i + j + 1] = '\0';
            }
            strcat(input, temp);
            break;
        }
    }

    printf("%s \n", input);
}

void exercise20(char str[], int num1, int num2)
{
    char temp1[100], temp2[100];
    int count = 0;
    strcpy(temp1, str + num1 + num2);
    str[num1 + num2] = '\0';
    strcpy(temp2, str + num1);
    str[num1] = '\0';
    strcat(temp2, str);
    strcat(temp2, temp1);
    strcpy(str, temp2);
}

void exercise21()
{
    char input[70], temp[70];
    scanf("%s", input);

    int len = strlen(input), j = 0;

    for (int i = 0; i < len; i += j + 1)
    {
        for (j = 0; input[i + j] != '*'; j++);
        if (j % 2 == 0) 
            printf("%c%c \n", input[(j / 2 ) + i - 1], input[(j / 2) + i]);
        else
            printf("%c \n", input[(j / 2) + i]);
    }
}

int main()
{
    char str1[] = "125439047", str2[] = "yes", str3[] = "no";

    exercise1(str1);
    exercise2(str1);
    exercise3(str1, str2);
    exercise4(str1);
    exercise6();
    exercise7(str1, str2);
    exercise11(str1, str2, str3);
    exercise12(str1);
    exercise14(str1);
    exercise17();
    exercise18();
    exercise20(str1, 3, 3);
    printf("%s \n", str1);
    exercise21();

    return 0;
}
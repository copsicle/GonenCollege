#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int* bigfunc()
{

}

int main()
{
    int* x = bigfunc();
    printf("%d", x);

    return 0;
}
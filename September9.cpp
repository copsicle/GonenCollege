#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ROW 5
#define COL 5

void printarr(int arr[], int size)
{    
    printf("[");

    for(int i = 0; i < size; i++) printf("%d, ", arr[i]);

    printf("\b\b] \n");
}

void printmat(int mat[][COL]) 
{
    printf("Matrix with %d rows and %d columns \n", ROW, COL);

    for (int i = 0; i < ROW; i++) printarr(mat[i], COL);
}

void exercise6(int mat[][COL])
{
    int arr[ROW] = {0};

    for (int i = 0; i < ROW; i++)
    {
        arr[i] = mat[i][0];
        for (int j = 1; j < COL; j++)
            if (mat[i][j] > arr[i]) arr[i] = mat[i][j];
    }

    printarr(arr, ROW);
}

void exercise7(int mat[][COL])
{
    int cross = 1, neg = 1;
    
    for (int i = 0; i < ROW; i++)
    {
        if (mat[i][i] != 0 || mat[ROW - i - 1][COL - i - 1] != 0) cross = 0;
        for (int j = 0; j < COL; j++) 
            if (j != i && j != ROW - i - 1 && mat[i][j] >= 0) neg = 0;
    }

    if (neg && cross) printf("Negative \n");
    else if (cross) printf("Not negative \n");
    else if (neg) printf("Typical \n");
    else printf("Does not fit requirements \n");
}

void exercise8(int mat[][COL])
{
    int sum = 0;

    for (int i = 0; i < ROW; i++)
    {
        if (i == 0 || i == ROW - 1)
            for (int j = 0; j < COL; j++) 
                sum += mat[i][j];
        else sum += mat[i][0] + mat[i][COL - 1];
    }

    printf("Sum is %d \n", sum);
}

void exercise9(int mat[][COL])
{
    
}

int main()
{
    int mat[ROW][COL] = {
                        {0, -1, -1, -1, 0},
                        {-1, 0, -1, 0, -1},
                        {-1, -1, 0, -1, -1},
                        {-1, 0, -1, 0, -1},
                        {0, -1, -1, -1, 0}
                        };
    /*
    exercise6(mat);
    exercise7(mat);
    */

    exercise8(mat);

    return 0;
}
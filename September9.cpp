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
    for (int i = 0; i < ROW - 1; i++)
        for (int j = 0; j < COL; j++)
            if (j > i) mat[i][j] = mat[j][i];
}

void exercise10(int mat[][COL])
{
    int sum1 = 0, sum2 = 0, sum3, sum4, last1 = 0, last2 = 0;
    
    for (int i = 0; i < ROW; i++)
    {
        sum3 = 0;
        sum4 = 0;

        for (int j = 0; j < COL; j++)
        {
            sum3 += mat[i][j];
            sum4 += mat[j][i];
        }

        if ((last1 != sum3 || last2 != sum4) && i != 0) break;

        last1 = sum3;
        last2 = sum4;

        sum1 += mat[i][i];
        sum2 += mat[i][COL - i - 1];
    }

    printf(
        (sum1 == sum2 && sum2 == sum3 && sum3 == sum4 && sum3 == last1 && sum4 == last2) ?
         "Matrix is a magic square \n" : "Matrix is not a magic square \n");

}

void exercise18(int mat[][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        mat[i][0] = 1;

        for (int j = i; j > 0; j--)
            mat[i][j] = mat[i - 1][j] + mat[i - 1][j - 1];
    }
}

void exercise19(int mat[][COL])
{
    int i, j;

    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            if (mat[i][j] != mat[j][i]) break;
    
    printf((i == ROW && j == COL) ? 
        "Matrix is symmetric \n": "Matrix is not symmetric \n");
}

int main()
{
    int mat[ROW][COL] = {
                        {1, 2, 3, 4, 5},
                        {2, 2, 3, 4, 5},
                        {3, 3, 3, 4, 5},
                        {4, 4, 4, 4, 5},
                        {5, 5, 5, 5, 5}
                        };
    /*
    exercise6(mat);
    exercise7(mat);
    exercise8(mat);
    exercise9(mat);
    exercise10(mat);
    exercise18(mat);
    exercise19(mat);
    printmat(mat);
    */

    return 0;
}
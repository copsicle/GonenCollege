#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 4
#define COL 4

#define N

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

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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

void transferMainToSafe(int arr[][COL], int arrB[][COL + 2])
{
    for (int i = 0; i < COL; i++)
    {
        for (int j = 0; i < COL; j++)
        {
            arrB[i + 1][j + 1] = arr[i][j];
        }
    }
}

void buildWall(int arr[][COL], int arrB[][COL + 2])
{
    for (int i = 0; i < COL + 2; i++)
    {
        arrB[0][i] = -999;
        arrB[COL + 1][i] = -999;
        arrB[i][0] = -999;
        arrB[i][COL + 1] = -999;
    }
}

int IsBig(int arr[][COL + 2], int i, int j)
{
    for (int k = (i - 1); k < i + 2; k++)
        for (int w = (j - 1); w < j + 2; w++)
            if (w != j && k != i && arr[k][w] < arr[i][j])
                return 0;
    return 1;
}

int countIsBig(int mat[][COL + 2])
{
    int count = 0;
    for (int i = 1; i < COL + 1; i++)
        for (int j = 1; i < COL + 1; j++)
            count += IsBig(mat, i, j);
    return count;
}

void safeWall() // main
{
    int mat[COL][COL] = { {1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,12},
                    {10,20,30,40} };

    int matB[COL + 2][COL + 2];
    
    transferMainToSafe(mat, matB);
    buildWall(mat, matB);
    countIsBig(matB);
}

void exercise62(int arr[], int size, int ind1, int ind2)
{
    for (int i = ind2 + 1; i > ind1; i--)
        for (int j = ind1 + 1; j < i; j++)
            if (arr[j - 1] > arr[j])
                swap(&arr[j - 1], &arr[j]);
}

int* exercise72(int num)
{
    static int arr[10] = {0};
    
    while (num != 0)
    {
        arr[num % 10]++;
        num /= 10;
    }

    return arr;
}

int exercise82(int arr[], int size)
{
    int count = 0, last = 0, max = 0;
    for (int i = 0; i < size; i++)
    {
        if (i == 0 || arr[i] == last) count++;
        else count = 1;

        if (count > max) max = count;

        last = arr[i];
    }

    return max;
}

int exercise92(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (arr[i] == arr[j]) return 0;
    return 1;
}

int exercise102a(int arr1[], int size1, int arr2[], int size2)
{
    int j;
    
    if (size2 > size1) return 0;

    for (int i = 0; i < size2; i++)
    {
        for (j = 0; j < size1; j++)
            if (arr2[i] == arr1[j]) break;

        if (j == size1) return 0;
    }

    return 1;
}

int exercise102b(int arr1[], int size1, int arr2[], int size2)
{
    int j;

    for (int i = 0; i < size1; i++)
    {
        for (j = 0; j < size2 && arr1[i + j] == arr2[j]; j++);
        if (j == size2) return 1;
    }

    return 0;
}

int IsRow(int mat[][COL], int row)
{
    int arr[4] = {1, 2, 3, 4};
    return exercise102a(mat[row], COL, arr, 4);
}

int IsCol(int mat[][COL], int col)
{
    int arr1[ROW] = {0}, arr2[4] = {1, 2, 3, 4};

    for (int i = 0; i < ROW; i++) arr1[i] = mat[i][col];

    return exercise102a(arr1, ROW, arr2, 4);
}

int Is2X2(int mat[][COL], int r, int c)
{
    int arr1[4] = {mat[r][c], mat[r+1][c], mat[r][c+1], mat[r+1][c+1]},
    arr2[4] = {1, 2, 3, 4};

    return exercise102a(arr1, 4, arr2, 4);
}

int IsQuarter(int mat[][COL])
{
    int res = 1;
    for (int i = 0; i < ROW; i += 2)
        for (int j = 0; j < COL; j += 2)
            res *= Is2X2(mat, i, j);
    return res;
}

int IsSoduku(int mat[][COL])
{
    int res = 1;
    
    for (int i = 0; i < ROW; i++)
        res *= IsCol(mat, i) * IsRow(mat, i);

    return res * IsQuarter(mat);
}

void exercise2(int mat[][COL])
{
    srand((unsigned)time(NULL));
    
    int p1s = 0, p2s = 0;

    while (p1s < 1000 && p2s < 1000)
    {
        p1s += mat[rand() % ROW][rand() % COL];
        p2s += mat[rand() % ROW][rand() % COL];
    }

    printf((p1s >= 1000) ? "Player 1 won \n": "Player 2 won \n");
}

int main()
{
    int mat[ROW][COL] = {
                        {1, 2, 3, 4},
                        {3, 4, 2, 1},
                        {2, 1, 4, 3},
                        {4, 3, 1, 2}
                        };
    
    exercise6(mat);
    exercise7(mat);
    exercise8(mat);
    exercise9(mat);
    exercise10(mat);
    exercise18(mat);
    exercise19(mat);
    printmat(mat);
    exercise62(mat[0], COL, 1, 3);
    printarr(mat[0], COL);
    printarr(exercise72(69420), 10);
    printf("%d \n", exercise82(mat[0], COL));
    printf("%d \n", exercise92(mat[0], COL));
    printf("%d \n", exercise102a(mat[0], COL, mat[1], COL));
    int arr1[10] = {1,2,3,4,5,6,7,8,9,10}, arr2[5] = {4, 5, 6, 7, 8};
    printf("%d \n", exercise102b(arr1, 10, arr2, 5));
    printf("%d \n", IsSoduku(mat));
    exercise2(mat);

    return 0;
}
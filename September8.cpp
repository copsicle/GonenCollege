#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"

void exercise2()
{
    #define ex2len 20

    int arr[ex2len], smallest = 0;

    for (int i = 0; i < ex2len; i++) 
    {
        scanf("%d", &arr[i]);
        if ( i == 0 || arr[i] < smallest) smallest = arr[i];
    }

    for (int i = 0; i < ex2len; i++) if (arr[i] == smallest) printf("%d ", i);

    printf("\n");
}

void exercise3()
{
    #define ex3len 50
    
    int arr[ex3len] = { 0 }, count = 1, max = 0, ind = 0;

    scanf("%d", &arr[0]);

    for (int i = 0; arr[i] != -1; i++)
    {
        if (i > 0 && arr[i] <= arr[i-1]) count++;
        else 
        {
            if (count > max)
            {
                max = count;
                ind = (i - count) + 1;
            }
            count = 1;
            
        }
        scanf("%d", &arr[i+1]); 
    }
    
    printf("%d \n", ind);
}

int exercise4a(int arr[], int size)
{
    int count = 0;

    for (int i = 0; i < size; i++) if (arr[i] > 0) count++;

    return count;
}

void exercise4b(int arr[], int size, int *out)
{
    *out = 0;

    for (int i = 0; i < size; i++) if (arr[i] > 0) *out++;
}

void copyOdd(int A[], int sizeA, int B[], int& sizeB)
{
    sizeB = 0;

    for (int i = 0; i < sizeA; i++) 
    {
        if (A[i] % 2 != 0) 
        {
            B[sizeB] = A[i];
            sizeB++;
        }
    }
}

void removeOdd(int A[], int& size)
{
    int temp;

    for (int i = 0; i < size; i++)
    {
        if (A[i] % 2 != 0)
        {
            temp = A[i];

            for (int j = size - 1; j > i; j--)
            {
                if (A[j] % 2 == 0)
                {
                    A[i] = A[j];
                    A[j] = temp;
                    break;
                }
            }

            if (temp == A[i])
            {
                size = i;
                break;
            }
        }
    }


}

void splitParity(int A[], int size) 
{ 
    int temp = size;
    removeOdd(A, size);
    size = temp; 
}

void insertionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j >= 1 && arr[j] > arr [j - 1]; j--) 
                swap(&arr[j], &arr[j - 1]);
}

void exercise8()
{
    #define ex8len 20

    int arr[ex8len] = {0};
    
    for (int i = 0; i < ex8len; i++) scanf("%d", &arr[i]);

    insertionSort(arr, ex8len);

    printarr(arr, ex8len);
}

int findChange(int arr[], int n)
{
    int ind = -1;
    for (int i = 1; i < n; i++)
    {
        if (arr[i - 1] % 2 == 0 && arr[i] % 2 == 1)
        {
            ind = i - 1;
            break;
        }
    }

    return ind; 
}

int main()
{
    int arr1[] = {1, 3, 5, 7, 9},
        arr2[] = {0, 2, 4, 6, 8, 10},
        n = 5, m = 6;
    /*
    exercise2();
    exercise3();
    exercise4a(arr1, 3);
    exercise4b(arr1, 3);
    copyOdd(arr1, 3, arr2, n);
    printarr(arr2, n);
    splitParity(arr1, n);
    printarr(arr1, n);
    exercise8();
    printf("%d \n", findChange(arr2, m));
    printarr(exercise1(arr1, n, arr2, m), n+m);
    printarr(exercise22(arr1, n, arr2, m), n);
    */

    printarr(exercise32(arr1, n, arr2, m), n+m);

    exercise42a(arr1, n, 4);
    printarr(arr1, n);

    return 0;
}
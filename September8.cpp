#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void printarr(int arr[], int size)
{
    if (size == 0) size = sizeof(arr) / sizeof(int);
    
    printf("Array with size of %d \n[", size);

    for(int i = 0; i < size; i++) printf("%d, ", arr[i]);

    printf("\b\b] \n");
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

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

int main()
{
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, arr2[] = { 0, 0 }, n = 10;
    /*
    exercise2();
    exercise3();
    exercise4a(arr1, 3);
    exercise4b(arr1, 3);
    copyOdd(arr1, 3, arr2, n);
    printarr(arr2, n);
    */
    removeOdd(arr1, n);
    printarr(arr1, n);

    return 0;
}
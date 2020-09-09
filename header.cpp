#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Header.h"

void printarr(int arr[], int size)
{    
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

int* exercise1(int arr1[], int size1, int arr2[], int size2)
{
    static int arr[50] = {0};

    for (int i = 0; i < size1; i++) arr[i] = arr1[i];

    for (int i = 0; i < size2; i++) arr[size1 + i] = arr2[i];

    return arr;
}

int* exercise22(int arr1[], int size1, int arr2[], int size2)
{
    static int arr[50] = {0};
    int count = 0;

    for (int i = 0; i < size1; i++) 
    {
        for (int j = 0; j < size2; j++) 
        {
            if (arr1[i] == arr2[j]) 
            {
                arr[count++] = arr1[i];
                break;
            }
        }
    }

    return arr;
}

int* exercise32(int arr1[], int size1, int arr2[], int size2)
{
    static int arr[50] = {0};
    int count = 0, inserted = 0;

    for (int i = 0; i < size1; i++)
    {
        for (int j = inserted; j < size2 && arr2[j] < arr1[i]; j++)
        {
            inserted = j + 1;
            arr[count++] = arr2[j];
        }

        arr[count++] = arr1[i];
    }

    for (int i = inserted; i < size2; i++) 
            arr[count++] = arr2[i];

    return arr;
}

void exercise42a(int arr[], int size, int num)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < num)
        {
            for (int j = i; j < size; j++) 
                swap(&arr[j], &num);
            break;
        }
    }
}

int* exercise42b(int arr[], int size)
{
    static int ans[50] = {};

    for (int i = 0; i < size; i++) exercise42a(ans, size, arr[i]);

    return ans;
}

void exercise52(int arr[], int size)
{
    for (int i = size; i > 0; i--)
        for (int j = 1; j < i; j++)
            if (arr[j - 1] > arr[j])
                swap(&arr[j - 1], &arr[j]);
}
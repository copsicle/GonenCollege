#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int what(int n1, int n2)
{
    if (n1<10 && n2<10)
        return (n1==n2);
    if (n1<10)
        return what(n1, n2/10);
    if (n2<10)
        return what(n1/10, n2);
    return what(n1/10, n2/10);
}

float q3(int vec[], int n)
{
    if (n == 1) return vec[0];

    return ((vec[0] + (q3(vec + 1, n - 1) * (n - 1))) / n);
}

int q4(int num)
{
    if (num < 2) return num;

    return (10 * q4(num / 2)) + (num % 2);
}

int q5(int num)
{
    if (num < 16) return num;

    if (num % 16 >= 10)
        return ((100 * q5(num / 16)) + num % 16);
    else return ((10 * q5(num / 16)) + num % 16);
}

int q6(int arr[], int num, int size)
{
    int place = (2 * size) / 3;
    if (num == arr[place]) return place;
    else if (num > arr[place])
        return place + q6(arr + place, num, (size / 3) + 1);
    else
    {
        place = size / 3;
        if (num == arr[place]) return place;
        else if(num > arr[place])
            return place + q6(arr + place, num, place + 1);
        else
            return q6(arr, num, place + 1);
    }
}

int main()
{
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, res = 0;

    res = what(nums[0], nums[1]);
    printf("%d\n", res);
    res = q3(nums, sizeof(nums)/sizeof(int));
    printf("%d\n", res);
    res = q4(nums[0]);
    printf("%d\n", res);
    res = q5(nums[0]);
    printf("%d\n", res);
    res = q6(nums, 2, sizeof(nums)/sizeof(int));
    printf("%d\n", res);


    return 0;
}
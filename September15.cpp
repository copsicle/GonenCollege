#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define BOOKAMT 10
#define AUTHAMT 5

typedef struct author
{
    char name[];
    int books;
    int price;
};

typedef struct book
{
    char name[];
    author author;
    int year;
    int stock;
    int price;
};

int main()
{

    book books[BOOKAMT];
    author authors[AUTHAMT];
    int lifetime[BOOKAMT];

    return 0;
}

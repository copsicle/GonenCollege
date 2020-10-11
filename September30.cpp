#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    int info;
    struct node* next;
    struct node* prev;
} nodeType, *nodePtr;

void insertAfter(nodePtr head, int P, int info)
{
    nodePtr temp = head, newnode;
    while (P-- > 0 && temp) temp = temp->next;
    if (temp)
    {
        newnode = (nodePtr) malloc(sizeof(nodeType));
        newnode->info = info;
        if (temp->next)
        {
            (temp->next)->prev = newnode;
            newnode->next = temp->next;
        }
        else newnode->next = NULL;
        newnode->prev = temp;
        temp->next = newnode;
    }
}

void insertBefore(nodePtr head, int P, int info)
{
    nodePtr temp = head, newnode;
    while (P-- > 0 && temp) temp = temp->next;
    if (temp)
    {
        newnode = (nodePtr) malloc(sizeof(nodeType));
        newnode->info = info;
        if (temp->prev)
        {
            (temp->prev)->next = newnode;
            newnode->prev = temp->prev;
        }
        else newnode->prev = NULL;
        newnode->next = temp;
        temp->prev = newnode;
    }
}

void deleteNode(nodePtr target)
{
    if (target->next && target->prev)
    {
        (target->prev)->next = target->next;
        (target->next)->prev = target->prev;
    }
    else if(target->next)
        (target->next)->prev = NULL;
    else if(target->prev)
        (target->prev)->next = NULL;
    free(target);
}

void deleteAfter(nodePtr head, int P)
{
    nodePtr temp = head;
    while (P-- + 1 > 0) temp = temp->next;
    deleteNode(temp);
}

void deleteBefore(nodePtr head, int P)
{
    nodePtr temp = head;
    while (P-- - 1 > 0) temp = temp->next;
    deleteNode(temp);
}

void deleteInfo(nodePtr head, int info)
{
    if (head->info == info)
        deleteNode(head);
    else
    {
        nodePtr temp = head->next;
        while(temp->info != info && temp != head)
            temp = temp->next;
        if (temp->info == info)
            deleteNode(temp);
    }
}

nodePtr createLinearList(int length, int randrange)
{
    srand((unsigned)time(NULL));
    nodePtr head = (nodePtr) malloc(sizeof(nodeType));
    head->info = rand() % randrange;
    head->next = NULL;
    head->prev = NULL;
    if (length > 1)
    {
        nodePtr temp = head;
        for (int i = 1; i < length; i++)
        {
            insertAfter(temp, 0, rand() % randrange);
            temp = temp->next;
        }
    }
    return head;
}

nodePtr createCircularList(int length, int randrange)
{
    srand((unsigned)time(NULL));
    nodePtr head = (nodePtr) malloc(sizeof(nodeType));
    head->info = rand() % randrange;
    head->next = head;
    head->prev = head;
    if (length > 1)
    {
        nodePtr temp = head;
        for (int i = 1; i < length; i++)
        {
            insertAfter(temp, 0, rand() % randrange);
            temp = temp->next;
        }
        temp->next = head;
        head->prev = temp;
    }
    return head;
}

void printNode(nodePtr head)
{
    nodePtr temp = head;
    while (temp)
    {
        printf("%d <=> ", temp->info);
        temp = temp->next;
        if (temp == head) break;
    }
    printf("\b\b\b\b   \n");
}

int main()
{
    nodePtr n1 = createLinearList(5, 100);
    printNode(n1);
    while (n1->next)
        deleteAfter(n1, 0);
    free(n1);
    n1 = createCircularList(5, 100);
    printNode(n1);

    return 0;
}
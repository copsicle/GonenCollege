#pragma once

#include "header.h"

typedef treePtr queueItem;

typedef struct nodeType
{
    queueItem info;
    struct nodeType* next;
}   node;

typedef struct
{
    node* head;
    node* rear;
}   queue;

void queueInit(queue* q);
void printQueue(queue* q);
void enqueue(queue* q, queueItem x);
void freeQueue(queue* q);

queueItem dequeue(queue* q);
queueItem queueTop(queue q);

int isQueueEmpty(queue q);
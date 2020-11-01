#include "queue.h"

void queueInit(queue* q)
{
    q->head = NULL;
    q->rear = NULL;
}

void enqueue(queue* q, queueItem x)
{
    node* n = (node*)malloc(sizeof(node));
    
    n->info = x;
    n->next = NULL;

    if (isQueueEmpty(*q))
        q->head = q->rear = n;
    else
    {
        q->rear->next = n;
        q->rear = n;
    }
}

queueItem dequeue(queue* q)
{
    queueItem val = q->head->info;
    node* n = q->head;
    
    q->head = q->head->next;
    
    if (!(q->head)) q->rear = NULL;
    
    free(n);
    return val;
}


queueItem queueTop(queue q)
{
    return q.head->info;
}

int isQueueEmpty(queue q)
{
    return q.head == NULL;
}

void freeQueue(queue* q)
{
    while (!isQueueEmpty(*q)) dequeue(q);
}

void queue_print(queue* q)
{
    queue temp;
    queueInit(&temp);

    while (!isQueueEmpty(*q))
    {
        printf("%d ", queueTop(*q));
        enqueue(&temp, dequeue(q));
    }

    printf("\n");

    while (!isQueueEmpty(temp))
        enqueue(q, dequeue(&temp));
}
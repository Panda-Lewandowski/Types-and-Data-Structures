#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

qNode *getNewqNode(float time,enum req_type t) {
    qNode *newqNode = (qNode *)malloc(sizeof(qNode));
    if (NULL == newqNode) {
        return newqNode;
    }
    newqNode->time = time;
    newqNode->next = NULL;
    newqNode->type = t;
    return newqNode;
}

queue *CreateQueue() {
    queue *newQueue = (queue *)malloc(sizeof(queue));
    if(NULL == newQueue) {
        return newQueue;
    }
    newQueue->front = newQueue->rear = NULL;
    newQueue->elts = 0;
    newQueue->ever_elts = 0;
    return newQueue;
}

int Enqueue(queue *queueptr, float time, enum req_type t) {
    if(queueptr == NULL) {
        return QUEUE_FAILURE;
    }

    qNode *newqNode = getNewqNode(time, t);
    if (newqNode == NULL) {
        return QUEUE_FAILURE;
    }
    if (queueptr->front == NULL) {
        queueptr->rear =  newqNode;
        queueptr->front = newqNode;
        queueptr->elts++;
        queueptr->ever_elts++;
        return QUEUE_SUCCESS;
    }
    queueptr->rear->next = newqNode;
    queueptr->rear = newqNode;
    queueptr->elts++;
    queueptr->ever_elts++;

    return QUEUE_SUCCESS;
}

float Dequeue(queue *queueptr) {

    if(queueptr == NULL || queueptr->front == NULL) {
        return QUEUE_FAILURE;
    }
    qNode *temp = queueptr->front;
    float time = temp->time;
    queueptr->front = temp->next;
    free(temp);
    queueptr->elts--;
    return time;
}

void PrintQueue(queue *queueptr) {
    /*if(queueptr == NULL || queueptr->front == NULL) {
        return ;
    }*/
    qNode *temp = queueptr->front;
    while(temp != NULL) {
        printf("%g \t",temp->time);
        temp=temp->next;
    }
}

void DestroyQueue(queue *queueptr) {

    queue *temp;
    for(; queueptr; queueptr = temp) {
        temp = queueptr;
        free(queueptr);
    }
}

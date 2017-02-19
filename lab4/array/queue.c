
#include "queue.h"

queue_t* new_queue(int capacity, enum req_type t)
{
    queue_t* queue = malloc(sizeof(queue_t));
    if(queue) {
        float* data_store = malloc(sizeof(float) * capacity);
        if(data_store) {
            queue->data_store = data_store;
            queue->front = 0;
            queue->capacity = capacity;
            queue->elts = 0;
            queue->ever_elts = 0;
            queue->type = t;
        }
        else
            return NULL;
    }
    else
        return NULL;

    return queue;
}

int Enqueue(queue_t* queue, float item, enum req_type t)
{
    if (queue->elts >= queue->capacity) {
        return QUEUE_FAILURE;
    }

    queue->data_store[queue->front] = item;

    queue->front++;
    queue->elts++;
    queue->ever_elts++;

    return QUEUE_SUCCESS;
}

float Dequeue(queue_t* queue)
{
    if (queue->elts < 1) {
        return QUEUE_FAILURE;
    }

    float result = queue->data_store[0];

    queue->elts--;
    queue->front--;

    float buf;
    for(int i = 0; i < queue->front; i++) {
        buf = queue->data_store[i+1];
        queue->data_store[i] = buf;
        queue->data_store[i+1] = 0;
    }
    return result;
}

void queue_free(queue_t* queue)
{
    free(queue->data_store);
    free(queue);
}


void queue_print(queue_t* q)
{
    for(int i = 0; i < q->front; i++)
        printf("%d   %f  \n",i,  q->data_store[i]);
}

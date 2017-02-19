#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SUCCESS 0
#define QUEUE_FAILURE -1

#define T1_MAX 5
#define T1_MIN 1

#define T2_MAX 3
#define T2_MIN 0

#define T3_MAX 10
#define T3_MIN 0

#define T4_MAX 1
#define T4_MIN 0


enum req_type {NONE, T1, T2};

typedef struct qNode {
    struct qNode *next;
    enum req_type type;
    float time;
} qNode;

typedef struct queue {
    struct qNode *front, *rear;
    int elts;
    int ever_elts;
} queue;


qNode *getNewqNode(float , enum req_type);
queue * CreateQueue();
int Enqueue(queue *, float , enum req_type t);
float Dequeue(queue *);
void PrintQueue(queue *);
void DestroyQueue(queue *queueptr);
#endif // QUEUE_H

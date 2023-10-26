#ifndef QUEUE_H
#define QUEUE_H

#include<stdbool.h>
#define MAX_SZ 50000

typedef struct Pair {
	int first;
	int second;
} Pair;

typedef struct Queue {
	int top, bottom;
	Pair queue[MAX_SZ];
} Queue;

void Queue_push(Queue *q, Pair p);
bool Queue_is_empty(Queue *q);
void Queue_pop(Queue *q);
Pair Queue_top(Queue *q);
void Queue_init(Queue *q);

#endif // QUEUE_H

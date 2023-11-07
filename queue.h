#ifndef QUEUE_H
#define QUEUE_H

#include<stdbool.h>
#define MAX_SZ 50000

#define BLOCK_SWAP 0
#define BLOCK_CHECK 1

typedef struct _BlockCheck {
	int first;
	int second;
    int type;
} BlockCheck;

typedef struct _Queue {
	int top, bottom;
	BlockCheck queue[MAX_SZ];
} Queue;

void Queue_push(Queue *q, BlockCheck p);
bool Queue_is_empty(Queue *q);
void Queue_pop(Queue *q);
BlockCheck Queue_top(Queue *q);
void Queue_init(Queue *q);

#endif // QUEUE_H

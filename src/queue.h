#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "raylib.h"
#define MAX_SZ 50000

typedef enum BLOCK_TYPE {
    BLOCK_TYPE_SWAP,
    BLOCK_TYPE_CHECK,
    BLOCK_TYPE_REMAP,
    BLOCK_TYPE_INPLACE,
    BLOCK_TYPE_NONE
} BLOCK_TYPE;

typedef struct _BlockCheck {
	int first;
	int second;
    BLOCK_TYPE type;
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

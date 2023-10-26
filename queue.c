#include "queue.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct Pair {
	int first;
	int second;
} Pair;

#define MAX_SZ 50000
typedef struct Queue {
	int top, bottom;
	Pair queue[MAX_SZ];
} Queue;

void Queue_push(Queue *q, Pair p) {
	if (q->bottom >= MAX_SZ) {
		return;
	}
	q->queue[++q->bottom] = p;
	printf("New value at pos: %d\n", q->bottom);
}

bool Queue_is_empty(Queue *q) {
	return q->top > q->bottom;
}

void Queue_pop(Queue *q) {
	if (empty(q)) {
		return;
	}
	q->top++;
}

Pair Queue_top(Queue *q) {
	if (empty(q)) {
		Pair p;
		p.first = -1;
		p.second = -1;
		return p;
	}
	return q->queue[q->top];
}

void Queue_init(Queue *q) {
	q->top = 0;
	q->bottom = -1;
}

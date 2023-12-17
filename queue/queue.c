#include "queue.h"
#include <stdbool.h>

void Queue_push(Queue *q, BlockCheck p) {
	if (q->bottom >= MAX_SZ) {
		return;
	}
	q->queue[++q->bottom] = p;
}

bool Queue_is_empty(Queue *q) {
	return q->top > q->bottom;
}

void Queue_pop(Queue *q) {
	if (Queue_is_empty(q)) {
		return;
	}
	q->top++;
}

BlockCheck Queue_top(Queue *q) {
	if (Queue_is_empty(q)) {
		BlockCheck p;
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

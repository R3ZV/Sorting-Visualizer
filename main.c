#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "raylib.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800
#define BLOCK_WIDTH 20

// =============== QUEUE =============
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

Pair Queue_top(Queue *q) {
	if (Queue_is_empty(q)) {
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
// =============== QUEUE =============

void Swap(int *x, int *y) {
	if (*x == *y) {
		return;
	}
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}

// Fisher-Yates shuffle algorithm
void Shuffle(int len, int values[]) {
	for (int i = len - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		Swap(&values[i], &values[j]);
	}
}

void init(int len, int values[]) {
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Sorting Visualizer");
	SetTargetFPS(60);
	for (int i = 0; i < len; ++i) {
		values[i] = i + 1;
	}
	Shuffle(len, values);
}

void DebugArray(int len , int values[]) {
	for (int i = 0; i < len; ++i) {
		printf("%d ", values[i]);
	}
	printf("\n");
}

void InsertionSort(int len, int values[], Queue *q) {
	for (int i = 0; i < len; ++i) {
		int mn = len + 2, idx = -1;
		for (int j = i; j < len; ++j) {
			if (values[j] < mn) {
				mn = values[j];
				idx = j;
			}
		}
		if (idx != -1) {
			Swap(&values[i], &values[idx]);
			Pair p;
			p.first = i;
			p.second = idx;
			Queue_push(q, p);
		}
	}
}

void BubbleSort(int len, int values[], Queue *q) {
	for (int i = 0; i < len; ++i) {
		for (int j = i + 1; j < len; ++j) {
			if (values[j] < values[i]) {
				Swap(&values[j], &values[i]);
				Pair p;
				p.first = i;
				p.second = j;
				Queue_push(q, p);
			}
		}
	}
}

long long elapsed_ms(struct timeval *t1, struct timeval *t2) {
	long long t1_ms = (long long) t1->tv_sec * 1000 + (long long) t1->tv_usec / 1000;
	long long t2_ms = (long long) t2->tv_sec * 1000 + (long long) t2->tv_usec / 1000;
	return t1_ms - t2_ms;
}

int main(void) {
	const int BLOCKS = WIN_WIDTH / BLOCK_WIDTH;
	const float HEIGHT_MULTIPLIER = 12;
	const int BASE_SPEED = 1000;
	const int SORTING_SPEED = 100;

	int values[BLOCKS];
	init(BLOCKS, values);

	int aux[BLOCKS];
	for (int i = 0; i < BLOCKS; ++i) {
		aux[i] = values[i];
	}

	Queue q;
	Queue_init(&q);


	struct timeval starting_time;
	gettimeofday(&starting_time, NULL);

	bool sorting = false;
	int speed_changer = 0;

	while (!WindowShouldClose()) {
		// Sorter Controls
		if (!sorting && IsKeyPressed(KEY_R)) {
			Shuffle(BLOCKS, values);
		}
		if (sorting && IsKeyPressed(KEY_LEFT) && speed_changer > 0) {
			speed_changer--;
		}
		if (sorting && IsKeyPressed(KEY_RIGHT) && speed_changer < BASE_SPEED / SORTING_SPEED) {
			speed_changer++;
		}
		if (!sorting && IsKeyPressed(KEY_SPACE)) {
			sorting = true;
			BubbleSort(BLOCKS, aux, &q);
			/* InsertionSort(BLOCKS, aux, &q); */
		}

		struct timeval current_time;
		gettimeofday(&current_time, NULL);
		long long elapsed = elapsed_ms(&current_time, &starting_time);

		// Update blocks
		if (!Queue_is_empty(&q) && elapsed > BASE_SPEED - speed_changer * SORTING_SPEED) {
			starting_time = current_time;
			Pair tp = Queue_top(&q);
			Queue_pop(&q);
			Swap(&values[tp.first], &values[tp.second]);
		}
		if (Queue_is_empty(&q)) {
			sorting = false;
		}

		// Base canvas
		BeginDrawing();
		for (int i = 0; i < BLOCKS; ++i) {
			int x0 = i * BLOCK_WIDTH;
			int y0 = WIN_HEIGHT - values[i] * HEIGHT_MULTIPLIER;
			DrawRectangle(x0, y0, BLOCK_WIDTH, values[i] * HEIGHT_MULTIPLIER, BLUE);
		}
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

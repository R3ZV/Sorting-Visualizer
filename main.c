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


typedef struct Block {
    int x, y;
    int height;
    int width;
    Color color;
} Block;

void BlockDraw(Block block) {
    DrawRectangle(block.x, block.y, block.width, block.height, block.color);

    // Borders
    const Color BORDER_COLOR = WHITE;
    int x1 = block.x, y1 = block.y + block.height;
    DrawLine(block.x, block.y, x1, y1, BORDER_COLOR);
    int x2 = block.x + block.width, y2 = y1;
    DrawLine(x1, y1, x2, y2, BORDER_COLOR);
    int x3 = x2, y3 = y2 - block.height;
    DrawLine(x2, y2, x3, y3, BORDER_COLOR);
    DrawLine(x3, y3, block.x, block.y, BORDER_COLOR);
}

void DebugBlock(Block b) {
    printf("BLOCK INFO: x=%d, y=%d, width=%d, height=%d\n", b.x, b.y, b.width, b.height);
}

void DebugBlocks(int len , Block blocks[]) {
	for (int i = 0; i < len; ++i) {
        DebugBlock(blocks[i]);
	}
}

void IntSwap(int *a, int *b) {
    if (*a == *b) {
        return;
    }
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void BlockSwap(Block *x, Block *y) {
    IntSwap(&x->y, &y->y);
    IntSwap(&x->height, &y->height);
}

// Fisher-Yates shuffle algorithm
void BlockShuffle(int len, Block blocks[]) {
	for (int i = len - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		BlockSwap(&blocks[i], &blocks[j]);
	}
}

const int HEIGHT_MULTIPLIER = 12;
void init(int len, Block blocks[]) {
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Sorting Visualizer");
	SetTargetFPS(60);
	for (int i = 0; i < len; ++i) {
        int x = i * BLOCK_WIDTH;
        int y = WIN_HEIGHT - (i + 1) * HEIGHT_MULTIPLIER;

        blocks[i].x = x;
        blocks[i].y = y;
        blocks[i].width = BLOCK_WIDTH;
        blocks[i].height = (i + 1) * HEIGHT_MULTIPLIER;
        blocks[i].color = BLUE;
	}
	BlockShuffle(len, blocks);
}

void InsertionSort(int len, Block blocks[], Queue *q) {
	for (int i = 0; i < len; ++i) {
		int mn = (len + 1) * HEIGHT_MULTIPLIER, idx = -1;
		for (int j = i; j < len; ++j) {
			if (blocks[j].height < mn) {
				mn = blocks[j].height;
				idx = j;
			}
		}
		if (idx != -1) {
			BlockSwap(&blocks[i], &blocks[idx]);
			Pair p;
			p.first = i;
			p.second = idx;
			Queue_push(q, p);
		}
	}
}

void BubbleSort(int len, Block blocks[], Queue *q) {
	for (int i = 0; i < len; ++i) {
		for (int j = i + 1; j < len; ++j) {
			if (blocks[j].height < blocks[i].height) {
				BlockSwap(&blocks[j], &blocks[i]);
				Pair p = { .first = i, .second = j};
                printf("Swapping i=%d with j=%d\n", i, j);
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
	const int BLOCK_LEN = WIN_WIDTH / BLOCK_WIDTH;
	const int BASE_SPEED = 1000;
	const int SORTING_SPEED = 100;

    Block blocks[BLOCK_LEN];
	Block aux[BLOCK_LEN];
	init(BLOCK_LEN, blocks);

	struct timeval starting_time;
	gettimeofday(&starting_time, NULL);

	bool sorting = false;
	int speed_changer = 0;

	Queue q;
	Queue_init(&q);
    Pair last = {.first = 0, .second = 0};

	while (!WindowShouldClose()) {
		// Sorter Controls
        if (!sorting && IsKeyPressed(KEY_R)) {
            BlockShuffle(BLOCK_LEN, blocks);
        }
        if (sorting && IsKeyPressed(KEY_LEFT) && speed_changer > 0) {
            speed_changer--;
        }
        if (sorting && IsKeyPressed(KEY_RIGHT) && speed_changer < BASE_SPEED / SORTING_SPEED) {
            speed_changer++;
        }
        if (!sorting && IsKeyPressed(KEY_SPACE)) {
            for (int i = 0; i < BLOCK_LEN; ++i) {
                aux[i] = blocks[i];
            }
            sorting = true;
            BubbleSort(BLOCK_LEN, aux, &q);
            // InsertionSort(BLOCK_LEN, aux, &q);
        }

        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        long long elapsed = elapsed_ms(&current_time, &starting_time);

        // Update blocks
        if (!Queue_is_empty(&q) && elapsed > BASE_SPEED - speed_changer * SORTING_SPEED) {
            blocks[last.first].color = BLUE;
            blocks[last.second].color = BLUE;
            starting_time = current_time;
            Pair tp = Queue_top(&q);
            Queue_pop(&q);

            blocks[tp.first].color = RED;
            blocks[tp.second].color = RED;

            BlockSwap(&blocks[tp.first], &blocks[tp.second]);
            last = tp;
        }
        if (Queue_is_empty(&q)) {
            sorting = false;
        }
		// Base canvas
		BeginDrawing();
		for (int i = 0; i < BLOCK_LEN; ++i) {
            BlockDraw(blocks[i]);
		}
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

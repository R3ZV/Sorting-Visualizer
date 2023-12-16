#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "raylib.h"
#include "queue.h"

#define WIN_WIDTH 1280
// #define WIN_WIDTH 1000
#define WIN_HEIGHT 800
#define BLOCK_WIDTH 20
#define HEIGHT_MULTIPLIER 10

typedef struct Block {
    int x, y;
    int height;
    int width;
    int id;
    Color color;
    Color border_color;
} Block;

void BlockDraw(Block block) {
    DrawRectangle(block.x, block.y, block.width, block.height, block.color);

    // Borders
    int x1 = block.x, y1 = block.y + block.height;
    DrawLine(block.x, block.y, x1, y1, block.border_color);
    int x2 = block.x + block.width, y2 = y1;
    DrawLine(x1, y1, x2, y2, block.border_color);
    int x3 = x2, y3 = y2 - block.height;
    DrawLine(x2, y2, x3, y3, block.border_color);
    DrawLine(x3, y3, block.x, block.y, block.border_color);
}

void DrawSortingSpeed(int x, int y, int speed) {
    char SpeedText[20];
    sprintf(SpeedText, "Sorting speed: %d ms", speed);
    DrawText(SpeedText, x, y, 20, GREEN);
}

void DebugBlock(Block b) {
    printf("BLOCK INFO: x=%d, y=%d, width=%d, height=%d\n", b.x, b.y, b.width, b.height);
}

void DebugBlocks(int len , Block blocks[]) { for (int i = 0; i < len; ++i) {
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
    IntSwap(&x->id, &y->id);
    IntSwap(&x->height, &y->height);
}

// Fisher-Yates shuffle algorithm
void BlockShuffle(int len, Block blocks[]) {
    for (int i = len - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        BlockSwap(&blocks[i], &blocks[j]);
    }
}

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
        blocks[i].border_color = WHITE;
        blocks[i].id = i;
    }
    BlockShuffle(len, blocks);
}

void InsertionSort(int len, Block blocks[], Queue *q) {
    for (int i = 0; i < len; ++i) {
        int mn = (len + 1) * HEIGHT_MULTIPLIER, idx = -1;
        for (int j = i; j < len; ++j) {
            // TODO
            BlockCheck p = { .first = j, .second = idx, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < mn) {
                mn = blocks[j].height;
                idx = j;
            }
        }
        if (idx != -1) {
            BlockSwap(&blocks[i], &blocks[idx]);
            BlockCheck p = { .first = i, .second = idx, .type = BLOCK_SWAP};
            Queue_push(q, p);
        }
    }
}

// TODO figure out the actual name
void ToFigure(int len, Block blocks[], Queue *q) {
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            BlockCheck p = { .first = i, .second = j, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[i].height) {
                BlockSwap(&blocks[j], &blocks[i]);
                BlockCheck p = { .first = i, .second = j, .type = BLOCK_SWAP};
                Queue_push(q, p);
            }
        }
    }
}

void BubbleSort(int len, Block blocks[], Queue *q) {
    while (true) {
        bool swaped = false;
        for (int j = 1; j < len; ++j) {
            BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[j - 1].height) {
                swaped = true;
                BlockSwap(&blocks[j], &blocks[j - 1]);
                BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
            }
        }
        if (!swaped) {
            break;
        }
    }
}

void GnomeSort(int len, Block blocks[], Queue *q) {
    int pos = 0;
    while (pos < len) {
        if (pos != 0) {
            BlockCheck p = { .first = pos, .second = pos - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
        }
        if (pos == 0 || blocks[pos].height > blocks[pos - 1].height) {
            pos++;
        } else {
            BlockSwap(&blocks[pos], &blocks[pos - 1]);
            BlockCheck p = { .first = pos, .second = pos - 1, .type = BLOCK_SWAP};
            Queue_push(q, p);
            pos--;
        }
    }
}

void BubbleSortOpt(int len, Block blocks[], Queue *q) {
    int sorted = 0;
    while (true) {
        bool swaped = false;
        for (int j = 1; j < len - sorted; ++j) {
            BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[j - 1].height) {
                swaped = true;
                BlockSwap(&blocks[j], &blocks[j - 1]);
                BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
            }
        }
        if (!swaped) {
            break;
        }
        sorted++;
    }
}

// TODO
void MergeSort(int left, int right, Block blocks[], Queue *q) {
    if (left >= right) return;

    int middle = (left + right) / 2;
    MergeSort(left, middle, blocks, q);
    MergeSort(middle + 1, right, blocks, q);

    int P1 = left, P2 = middle + 1;
    Block aux[WIN_WIDTH / BLOCK_WIDTH + 10];
    int len = 0;
    while (P1 <= middle && P2 <= right) {
        if (blocks[P1].height < blocks[P2].height) {
            aux[len++] = blocks[P1++];
        } else {
            aux[len++] = blocks[P2++];
        }
    }
    while (P1 <= middle) {
        aux[len++] = blocks[P1++];
    }

    while (P2 <= right) {
        aux[len++] = blocks[P2++];
    }

    for (int i = left, j = 0; i <= right; ++i, ++j) {
        BlockCheck p = { .first = blocks[i].id, .second = j, .type = BLOCK_REMAP };
        Queue_push(q, p);
        blocks[i].height = aux[j].height;
        blocks[i].y = aux[j].y;
    }
}

long long elapsed_ms(struct timeval *t1, struct timeval *t2) {
    long long t1_ms = (long long) t1->tv_sec * 1000 + (long long) t1->tv_usec / 1000;
    long long t2_ms = (long long) t2->tv_sec * 1000 + (long long) t2->tv_usec / 1000;
    return t1_ms - t2_ms;
}

int main(void) {
    const int BLOCK_LEN = WIN_WIDTH / BLOCK_WIDTH;
    const int BASE_SPEED = 100;
    int SORTING_SPEED = 200;

    Block blocks[BLOCK_LEN];
    Block aux[BLOCK_LEN];
    init(BLOCK_LEN, blocks);

    struct timeval starting_time;
    gettimeofday(&starting_time, NULL);

    bool sorting = false;
    Queue q;
    Queue_init(&q);
    BlockCheck last = {.first = 0, .second = 0};

    while (!WindowShouldClose()) {
        // Sorter Controls
        if (!sorting && IsKeyPressed(KEY_R)) {
            BlockShuffle(BLOCK_LEN, blocks);
            for (int i = 0; i < BLOCK_LEN; ++i) {
                blocks[i].color = BLUE;
                blocks[i].border_color = WHITE;
            }
        }
        if (sorting && IsKeyPressed(KEY_RIGHT) && SORTING_SPEED > 0) {
            SORTING_SPEED -= BASE_SPEED;
        }
        if (sorting && IsKeyPressed(KEY_LEFT) && SORTING_SPEED < 10 * BASE_SPEED) {
            SORTING_SPEED += BASE_SPEED;
        }
        if (!sorting && IsKeyPressed(KEY_SPACE)) {
            for (int i = 0; i < BLOCK_LEN; ++i) {
                aux[i] = blocks[i];
            }
            sorting = true;
            // BubbleSort(BLOCK_LEN, aux, &q);
            // BubbleSortOpt(BLOCK_LEN, aux, &q);
            GnomeSort(BLOCK_LEN, aux, &q);
            // InsertionSort(BLOCK_LEN, aux, &q);
            // MergeSort(0, BLOCK_LEN - 1, aux, &q);
        }

        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        long long elapsed = elapsed_ms(&current_time, &starting_time);

        // Update blocks
        if (!Queue_is_empty(&q) && elapsed >= SORTING_SPEED) {
            blocks[last.first].color = BLUE;
            blocks[last.second].color = BLUE;
            starting_time = current_time;
            BlockCheck tp = Queue_top(&q);
            Queue_pop(&q);
            if (tp.type == BLOCK_SWAP) {
                blocks[tp.first].color = RED;
                blocks[tp.second].color = RED;
                BlockSwap(&blocks[tp.first], &blocks[tp.second]);
            } else if (tp.type == BLOCK_CHECK) {
                blocks[tp.first].color = ORANGE;
                blocks[tp.second].color = ORANGE;
            } else if (tp.type == BLOCK_REMAP) {
                blocks[tp.first].height = aux[tp.second].height;
                blocks[tp.first].y = aux[tp.second].y;
                blocks[tp.first].color = PINK;
                blocks[tp.second].color = PINK;
            }

            last = tp;
        }
        if (Queue_is_empty(&q) && sorting) {
            sorting = false;
            for (int i = 0; i < BLOCK_LEN; ++i) {
                blocks[i].color = LIME;
                blocks[i].border_color = WHITE;
            }
        }

        // Base canvas
        BeginDrawing();
        DrawFPS(10, 10);
        DrawSortingSpeed(WIN_WIDTH - 240, 10, SORTING_SPEED);
        for (int i = 0; i < BLOCK_LEN; ++i) {
            BlockDraw(blocks[i]);
        }
        ClearBackground(BLACK);
        EndDrawing();
        DebugBlocks(BLOCK_LEN, aux);
    }

    CloseWindow();

    return 0;
}

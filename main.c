#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "raylib.h"
#include "queue/queue.h"
#include "block/block.h"
#include "sorters/sorters.h"

#define WIN_WIDTH  1280
#define WIN_HEIGHT 800

void DrawSortingSpeed(int x, int y, int speed) {
    char SpeedText[20];
    sprintf(SpeedText, "Sorting speed: %d ns", speed);
    DrawText(SpeedText, x, y, 20, GREEN);
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
    SetTargetFPS(200);
    InitBlocks(len, blocks, WIN_HEIGHT);
    BlockShuffle(len, blocks);
}

long long elapsed_ns(struct timespec *end, struct timespec *start) {
    return (end -> tv_sec - start -> tv_sec) * 1000000000L + (end -> tv_nsec - start -> tv_nsec);
}

int main(void) {
    const int BLOCK_LEN = WIN_WIDTH / BLOCK_WIDTH;

    // Nanoseconds
    const int BASE_SPEED = 55000;
    int SORTING_SPEED = 550000;

    const int BASE_SPEED_MULTIPLIER = 18;
    const int SORTING_SPEED_MULTIPLIER = 13;

    Block blocks[BLOCK_LEN];
    Block aux[BLOCK_LEN];
    init(BLOCK_LEN, blocks);

    struct timespec starting_time;
    clock_gettime(CLOCK_MONOTONIC, &starting_time);

    bool sorting = false;
    Queue q;
    Queue_init(&q);
    BlockCheck last = {.first = 0, .second = 0};

    while (!WindowShouldClose()) {
        // --- Sorter Controls ---

        // Reshuffles the blocks
        if (!sorting && IsKeyPressed(KEY_R)) {
            BlockShuffle(BLOCK_LEN, blocks);
            for (int i = 0; i < BLOCK_LEN; ++i) {
                blocks[i].color = BLUE;
                blocks[i].border_color = WHITE;
            }
        }

        if (sorting && IsKeyPressed(KEY_RIGHT) && SORTING_SPEED - BASE_SPEED >= 0) {
            SORTING_SPEED -= BASE_SPEED;
        }

        if (sorting && IsKeyPressed(KEY_LEFT) && SORTING_SPEED < BASE_SPEED_MULTIPLIER * BASE_SPEED) {
            SORTING_SPEED += BASE_SPEED;
        }

        // Starts the sorting algorithm
        if (!sorting && IsKeyPressed(KEY_SPACE)) {
            for (int i = 0; i < BLOCK_LEN; ++i) {
                aux[i] = blocks[i];
            }
            sorting = true;
            BubbleSortVariation(BLOCK_LEN, aux, &q);
            // BubbleSort(BLOCK_LEN, aux, &q);
            // BubbleSortOpt(BLOCK_LEN, aux, &q);
            // GnomeSort(BLOCK_LEN, aux, &q);
            // OddEvenSort(BLOCK_LEN, aux, &q);
            // CocktailShakerSort(BLOCK_LEN, aux, &q);
            // CocktailShakerSortOpt(BLOCK_LEN, aux, &q);
            // InsertionSort(BLOCK_LEN, aux, &q);
            // SelectionSort(BLOCK_LEN, aux, &q);
            // MergeSort(0, BLOCK_LEN - 1, aux, &q);
        }

        struct timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        long long elapsed = elapsed_ns(&current_time, &starting_time);

        // Update blocks
        if (!Queue_is_empty(&q) && elapsed >= SORTING_SPEED_MULTIPLIER * SORTING_SPEED) {
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

        // Draws the FPS, SortingSpeed and the blocks
        BeginDrawing();

        DrawFPS(10, 10);
        DrawSortingSpeed(WIN_WIDTH - 300, 10, SORTING_SPEED);

        for (int i = 0; i < BLOCK_LEN; ++i) {
            DebugBlock(blocks[i]);
            BlockDraw(blocks[i]);
        }

        ClearBackground(BLACK);

        EndDrawing();
        // DebugBlocks(BLOCK_LEN, aux);
    }

    CloseWindow();

    return 0;
}

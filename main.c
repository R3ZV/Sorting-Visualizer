#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "raylib.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800
#define BLOCK_WIDTH 20

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

int main(void) {
    const int BLOCKS = WIN_WIDTH / BLOCK_WIDTH;
    const float HEIGHT_MULTIPLIER = 12;
    int values[BLOCKS];
    DebugArray(BLOCKS, values);
    init(BLOCKS, values);
    DebugArray(BLOCKS, values);

    while (!WindowShouldClose()) {
        BeginDrawing();
            for (int i = 0; i < BLOCKS; ++i) {
                int x0 = i * BLOCK_WIDTH;
                int y0 = WIN_HEIGHT - values[i] * HEIGHT_MULTIPLIER;
                if (i & 1) {
                    DrawRectangle(x0, y0, BLOCK_WIDTH, values[i] * HEIGHT_MULTIPLIER, BLUE);
                } else {
                    DrawRectangle(x0, y0, BLOCK_WIDTH, values[i] * HEIGHT_MULTIPLIER, RED);
                }
            }
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

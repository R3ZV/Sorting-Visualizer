#include <stdio.h>

#include "block.h"
#include "raylib.h"

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

void DebugBlock(Block b) {
    printf("BLOCK INFO: x=%d, y=%d, width=%d, height=%d\n", b.x, b.y, b.width, b.height);
}

void DebugBlocks(int len , Block blocks[]){
    for (int i = 0; i < len; ++i) {
        DebugBlock(blocks[i]);
    }
}

bool IsSorted(int len, Block blocks[]) {
    for (int i = 0; i < len; ++i) {
        if (blocks[i].id != i) {
            return false;
        }
    }
    return true;
}

void InitBlocks(int len, Block blocks[], const int WIN_HEIGHT) {
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
}

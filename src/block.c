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
    DrawRectangleLines(block.x, block.y, block.width, block.height, block.border_color);
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
        blocks[i].color = BLOCK_INIT_COLOR;
        blocks[i].border_color = BLOCK_INIT_BORDER_COLOR;
        blocks[i].id = i;
    }
}

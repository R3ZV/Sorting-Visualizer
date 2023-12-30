#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"

#define BLOCK_WIDTH 16
#define HEIGHT_MULTIPLIER 9

#define BLOCK_INIT_COLOR BLUE
#define BLOCK_INIT_BORDER_COLOR WHITE

typedef struct _Block {
    int x, y;
    int height;
    int width;
    int id;
    Color color;
    Color border_color;
} Block;


void BlockDraw(Block block);
void DebugBlock(Block b);
void DebugBlocks(int len , Block blocks[]);
void BlockSwap(Block *x, Block *y);
void IntSwap(int *a, int *b);
void InitBlocks(int len, Block blocks[], const int WIN_HEIGHT);

#endif // BLOCK_H

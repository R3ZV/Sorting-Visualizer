#pragma once
#include "raylib.h"
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

class SortMethods {
    private:
        const int length = 1200/5;
        const int blockWidth = 5;
        const int blockHeigt = 50;
        const int blockX = 0;
        const int blockY = 0;
        bool isDrawing = false;
        std::vector<int> blocks_value;
        std::vector<Color> colors;
        Color block_color = GRAY;
        void fill_random_blocks();

    public:
        SortMethods();
        void unloadSounds();
        int getLength();
        bool getIsDrawing();
        void drawBlocks(bool begin);
        std::vector<int> getBlocks();
        void shuffleBlocks();
        void BubleSort();
        void MergeSort(int leftPointer, int rightPointer);
        void debug();
};

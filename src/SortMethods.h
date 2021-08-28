#pragma once
#include "raylib.h"
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

class SortMethods {
    private:
        const int length = 48;
        const int blockWidth = 20;
        const int blockHeigt = 50;
        const int blockX = 50;
        const int blockY = 0;
        const int gap = 3;
        bool isDrawing = false;
        std::vector<int> blocks_value;
        std::vector<int> colors;
        Color block_color = GRAY;
        int random_number();
        void fill_random_blocks();
        Sound sortSound = LoadSound("../sounds/sort.wav");

    public:
        SortMethods();
        void unloadSounds();
        int getLength();
        bool getIsDrawing();
        void drawBlocks();
        std::vector<int> getBlocks();
        void shuffleBlocks();
        void BubleSort();
        void MergeSort(int leftPointer, int rightPointer);
        void debug();
};

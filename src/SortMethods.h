#pragma once
#include "raylib.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

class SortMethods {
private:
  const int screenWidth = 1200;
  const int screenHeight = 1000;
  const int blockWidth = 1;
  const int length = screenWidth / blockWidth;
  const int blockX = 0;
  const int blockY = 0;
  bool isDrawing = false;
  std::vector<int> blocks_value;
  std::vector<Color> colors;
  void fill_random_blocks();

public:
  SortMethods();
  // Getters
  bool getIsDrawing();
  int getScreenWidth();
  int getScreenHeight();

  // Utilities
  void drawBlocks(bool begin);
  void shuffleBlocks();
  void BubleSort();
  void debug();
};

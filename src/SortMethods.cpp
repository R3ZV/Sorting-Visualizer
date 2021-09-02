#include "SortMethods.h"

SortMethods::SortMethods() {
  fill_random_blocks();
  shuffleBlocks();
}

// Getters

bool SortMethods::getIsDrawing() { return isDrawing; }

int SortMethods::getScreenWidth() { return screenWidth; }

int SortMethods::getScreenHeight() { return screenHeight; }

// Utilities

void SortMethods::BubleSort() {
  if (!is_sorted(blocks_value.begin(), blocks_value.end())) {
    for (int i = 0; i < length; ++i) {
      if (blocks_value[i + 1] < blocks_value[i]) {
        colors[i + 1] = colors[i] = RED;
        std::swap(blocks_value[i + 1], blocks_value[i]);
      } else
        colors[i + 1] = colors[i] = WHITE;
    }
  } else
    for (int i = 0; i < length; ++i)
      colors[i] = GREEN, isDrawing = true;
}

void SortMethods::drawBlocks(bool begin) {
  ClearBackground(BLACK);
  DrawText("Press SPACE to start", screenWidth / 2 - 175, 50, 30, GOLD);
  if (begin)
    for (int i = 0; i < length; ++i)
      DrawRectangle(blockX + i * blockWidth, screenHeight - blocks_value[i],
                    blockWidth, blocks_value[i], colors[i]);
}

void SortMethods::shuffleBlocks() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(blocks_value.begin(), blocks_value.end(),
          std::default_random_engine(seed));
}

void SortMethods::fill_random_blocks() {
  for (int i = 0; i < length; ++i) {
    blocks_value.push_back(GetRandomValue(10, screenHeight - 100));
    colors.push_back(WHITE);
  }
}

void SortMethods::debug() {
  for (int i = 0; i < length; ++i)
    std::cout << blocks_value[i] << " ";
  std::cout << std::endl;
}

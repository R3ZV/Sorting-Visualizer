#include "./src/SortMethods.h"

int main(void) {
  SortMethods AlgoSort;
  const int screenWidth = AlgoSort.getScreenWidth();
  const int screenHeight = AlgoSort.getScreenHeight();
  const int FPS = 60;

  InitWindow(screenWidth, screenHeight, "Sorting Algorithms");

  SetTargetFPS(FPS);

  bool begin = false;

  while (!WindowShouldClose()) {
    bool flag = AlgoSort.getIsDrawing();
    if (IsKeyPressed(KEY_SPACE))
      begin = true;
    if (begin && !flag)
      AlgoSort.BubleSort();
    BeginDrawing();
    if (!begin)
      AlgoSort.drawBlocks(true);
    AlgoSort.drawBlocks(begin);
    EndDrawing();
  }

  // De-Initialization
  // -------------------------------------------
  CloseWindow();
  return 0;
}

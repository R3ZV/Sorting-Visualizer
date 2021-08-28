#include "./src/SortMethods.h"
#include <vector>

int main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 800;
    const int FPS = 60;


    SortMethods AlgoSort;
    InitWindow(screenWidth, screenHeight, "Sorting Algorithms");

    SetTargetFPS(FPS);

    std::vector<int> blocks = AlgoSort.getBlocks();
    int length = AlgoSort.getLength();
    bool first = true;


    // Main game loop
    while(!WindowShouldClose()) {
        BeginDrawing();
            DrawText("Press SPACE to sort!", 450, 700, 30, GRAY);
        EndDrawing();
        if(first) {
            AlgoSort.drawBlocks();
            first = false;
        }
        if(IsKeyPressed(KEY_SPACE)) {
            AlgoSort.shuffleBlocks();
            //AlgoSort.MergeSort(0, length);
            AlgoSort.BubleSort();
        }
    }

    // De-Initialization
    // -------------------------------------------
    CloseWindow();
    AlgoSort.unloadSounds();
    return 0;
}

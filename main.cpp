#include "./src/SortMethods.h"
#include <vector>

const int N=200, W=5;
std::vector<int> arr(N);
std::vector<Color> colors(N);
int counter = 0;
bool begin = false, flag=false;

void draw() {
    ClearBackground(BLACK);
    DrawText("Press SPACE to start", 330, 50, 30, WHITE);
    if(begin)
        for(int i=0; i<N; ++i)
            DrawRectangle(W*i, 800-arr[i], W, arr[i], colors[i]);
}

void BubleSort() {
    if(!is_sorted(arr.begin(), arr.end())) {
        for(int i=0; i<N; ++i) {
            if(arr[i+1]<arr[i]) {
                colors[i+1] = colors[i] = RED;
                std::swap(arr[i+1], arr[i]);
            }
            else colors[i+1] = colors[i] = WHITE;
        }
    }
    else for(int i=0; i<N; ++i) colors[i] = GREEN, flag = true;
}


int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 800;
    const int FPS = 60;


    //SortMethods AlgoSort;
    InitWindow(screenWidth, screenHeight, "Sorting Algorithms");

    SetTargetFPS(FPS);

    for(int i=0; i<N; ++i) {
        arr[i]=GetRandomValue(10, 700);
        colors[i] = WHITE;
    }

    while(!WindowShouldClose()) {
        if(IsKeyPressed(KEY_SPACE)) begin = true;
        if(begin && !flag) BubleSort();
        BeginDrawing();
            draw();
        EndDrawing();
    }

    // De-Initialization
    // -------------------------------------------
    CloseWindow();
    return 0;
}

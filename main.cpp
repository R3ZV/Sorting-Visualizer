#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "raylib.h"
#include "queue/queue.h"
#include "block/block.h"
#include "sorters/sorters.h"

#define WIN_WIDTH  1280
#define WIN_HEIGHT 800

void DrawSortingSpeed(int x, int y, int speed) {
    char SpeedText[20];
    sprintf(SpeedText, "Sorting speed: %d ns", speed);
    DrawText(SpeedText, x, y, 20, GREEN);
}

// Fisher-Yates shuffle algorithm
void BlockShuffle(int len, Block blocks[]) {
    for (int i = len - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        BlockSwap(&blocks[i], &blocks[j]);
    }
}

void init(int len, Block blocks[]) {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Sorting Visualizer");
    SetTargetFPS(200);
    InitBlocks(len, blocks, WIN_HEIGHT);
    BlockShuffle(len, blocks);
}

long long elapsed_ns(struct timespec *end, struct timespec *start) {
    return (end -> tv_sec - start -> tv_sec) * 1000000000L + (end -> tv_nsec - start -> tv_nsec);
}

typedef enum GameState {
    GAMESTATE_INFO,
    GAMESTATE_SELECT,
    GAMESTATE_SORTER
} GameState;

void CreateButton(Rectangle bounds, const char *text, const int font_size, Color text_color, Color btn_color) {
    DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, btn_color);
    float text_x = bounds.x + bounds.width / 2.0 - (strlen(text) / 3.7) * font_size;
    float text_y = bounds.y + (bounds.height - font_size) / 2.0;
    DrawText(text, text_x, text_y, font_size, text_color);
}

void DisplayInfo() {
    int x = WIN_WIDTH / 2 - 40, y = 100;
    int font_size = 30;
    const int SPACEING = 70;

    DrawText("INFO:", x, y, 2 * font_size, WHITE);
    x -= 200;
    y += 2 * SPACEING;

    DrawText("Left Arrow - decrease sorting speed", x, y, font_size, WHITE);
    y += SPACEING;

    DrawText("Right Arrow - increase sorting speed", x, y, font_size, WHITE);
    y += SPACEING;

    DrawText("s - reshuffle the array", x, y, font_size, WHITE);
    y += SPACEING;

    DrawText("r - reset back to the sorting algorithms page", x, y, font_size, WHITE);
    y += SPACEING;

    DrawText("Space - start the algorithm", x, y, font_size, WHITE);
}

int main(void) {
    const int BLOCK_LEN = WIN_WIDTH / BLOCK_WIDTH;

    // Nanoseconds
    const int BASE_SPEED = 55000;
    int SORTING_SPEED = 550000;

    const int BASE_SPEED_MULTIPLIER = 18;
    const int SORTING_SPEED_MULTIPLIER = 13;

    InitAudioDevice();
    const Sound SORT_SOUND = LoadSound("./resources/tone.wav");
    SetSoundVolume(SORT_SOUND, 0.5);

    Block blocks[BLOCK_LEN];
    Block aux[BLOCK_LEN];
    init(BLOCK_LEN, blocks);

    struct timespec starting_time;
    clock_gettime(CLOCK_MONOTONIC, &starting_time);

    bool sorting = false;
    Queue q;
    Queue_init(&q);
    BlockCheck last = {.first = 0, .second = 0};

    GameState curr_state = GAMESTATE_INFO;
    SortAlgo selected_algo = SORTALGO_BUBBLE;

    Vector2 mouse_point = { 0.0f, 0.0f };
    Rectangle next_btn = {WIN_WIDTH / 2.0, WIN_HEIGHT - 100, 100, 50};
    while (!WindowShouldClose()) {
        if (curr_state == GAMESTATE_INFO) {
            mouse_point = GetMousePosition();
            if (CheckCollisionPointRec(mouse_point, next_btn)) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    curr_state = GAMESTATE_SELECT;
                }
            }

            BeginDrawing();

            DisplayInfo();
            CreateButton(next_btn, "Next", 20, WHITE, BLUE);
            ClearBackground(BLACK);

            EndDrawing();
        } else if (curr_state == GAMESTATE_SELECT) {

            mouse_point = GetMousePosition();
            for (int i = 0; i < AVAILABLE_ALGORITHMS; ++i) {
                if (CheckCollisionPointRec(mouse_point, ALGORITHMS_BTNS[i].bounds)) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        selected_algo = ALGORITHMS_BTNS[i].type;
                        curr_state = GAMESTATE_SORTER;
                    }
                }
            }

            BeginDrawing();


            DrawText("Select a sorting algorithm:", 100, 100, 40, WHITE);

            for (int i = 0; i < AVAILABLE_ALGORITHMS; ++i) {
                CreateButton(ALGORITHMS_BTNS[i].bounds, ALGORITHMS_BTNS[i].name, 24, WHITE, BLUE);
            }

            ClearBackground(BLACK);

            EndDrawing();

        } else if (curr_state == GAMESTATE_SORTER) {
            // Reshuffles the blocks
            if (!sorting && IsKeyPressed(KEY_S)) {
                BlockShuffle(BLOCK_LEN, blocks);
                for (int i = 0; i < BLOCK_LEN; ++i) {
                    blocks[i].color = BLUE;
                    blocks[i].border_color = WHITE;
                }
            }

            if (sorting && IsKeyPressed(KEY_RIGHT) && SORTING_SPEED - BASE_SPEED >= 0) {
                SORTING_SPEED -= BASE_SPEED;
            }

            if (sorting && IsKeyPressed(KEY_LEFT) && SORTING_SPEED < BASE_SPEED_MULTIPLIER * BASE_SPEED) {
                SORTING_SPEED += BASE_SPEED;
            }

            // Starts the sorting algorithm
            if (!sorting && IsKeyPressed(KEY_SPACE)) {
                for (int i = 0; i < BLOCK_LEN; ++i) {
                    aux[i] = blocks[i];
                }
                sorting = true;
                switch (selected_algo) {
                    case SORTALGO_BUBBLE_VARIATION:
                        BubbleSortVariation(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_BUBBLE:
                        BubbleSort(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_BUBBLE_OPT:
                        BubbleSortOpt(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_GNOME:
                        GnomeSort(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_ODDEVEN:
                        OddEvenSort(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_COCKTAILSHAKER:
                        CocktailShakerSort(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_COCKTAILSHAKER_OPT:
                        CocktailShakerSortOpt(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_INSERTION:
                        InsertionSort(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_SELECTION:
                        SelectionSort(BLOCK_LEN, aux, &q);
                        break;
                    case SORTALGO_MERGE:
                        MergeSort(0, BLOCK_LEN - 1, aux, &q);
                        break;
                    default:
                        break;
                }
            }

            struct timespec current_time;
            clock_gettime(CLOCK_MONOTONIC, &current_time);

            long long elapsed = elapsed_ns(&current_time, &starting_time);

            // Update blocks
            if (!Queue_is_empty(&q) && elapsed >= SORTING_SPEED_MULTIPLIER * SORTING_SPEED) {
                blocks[last.first].color = BLUE;
                blocks[last.second].color = BLUE;
                starting_time = current_time;
                BlockCheck tp = Queue_top(&q);
                Queue_pop(&q);
                if (tp.type == BLOCK_SWAP) {
                    blocks[tp.first].color = RED;
                    blocks[tp.second].color = RED;
                    BlockSwap(&blocks[tp.first], &blocks[tp.second]);
                } else if (tp.type == BLOCK_CHECK) {
                    int mx_height = blocks[tp.first].height;
                    if (blocks[tp.second].height > mx_height) {
                        mx_height = blocks[tp.second].height;
                    }
                    if (IsAudioDeviceReady()) {
                        SetSoundPitch(SORT_SOUND, mx_height / 400.0);
                        PlaySound(SORT_SOUND);
                    }

                    blocks[tp.first].color = ORANGE;
                    blocks[tp.second].color = ORANGE;
                } else if (tp.type == BLOCK_REMAP) {
                    blocks[tp.first].height = aux[tp.second].height;
                    blocks[tp.first].y = aux[tp.second].y;
                    blocks[tp.first].color = PINK;
                    blocks[tp.second].color = PINK;
                }

                last = tp;
            }
            if (Queue_is_empty(&q) && sorting) {
                sorting = false;
                for (int i = 0; i < BLOCK_LEN; ++i) {
                    blocks[i].color = LIME;
                    blocks[i].border_color = WHITE;
                }
            }

            // Draws the FPS, SortingSpeed and the blocks
            BeginDrawing();

            DrawFPS(10, 10);
            DrawSortingSpeed(WIN_WIDTH - 300, 10, SORTING_SPEED);

            for (int i = 0; i < BLOCK_LEN; ++i) {
                BlockDraw(blocks[i]);
            }

            ClearBackground(BLACK);

            EndDrawing();
            // DebugBlocks(BLOCK_LEN, aux);

        }
        // --- Sorter Controls ---

    }

    UnloadSound(SORT_SOUND);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

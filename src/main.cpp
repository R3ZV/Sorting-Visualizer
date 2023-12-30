#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "raylib.h"
#include "queue.h"
#include "block.h"
#include "sorters.h"

#define WIN_WIDTH  1280
#define WIN_HEIGHT 800

void DrawSortingInfo(int x, int y, int speed, char * algorithm) {
    char SpeedText[20];
    sprintf(SpeedText, "Sorting speed: %d ns", speed);
    DrawText(SpeedText, x, y, 20, GREEN);

    char AlgorithmText[40];
    sprintf(AlgorithmText, "Selected: %s", algorithm);
    DrawText(AlgorithmText, x - 500, y, 20, GREEN);
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
    int x = WIN_WIDTH / 2 - 100, y = 100;
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

void RunSortingAlgorithm(SORTALGO selected, int BLOCK_LEN, Block blocks[], Queue *q) {
    switch (selected) {
        case SORTALGO_BUBBLE_VARIATION:
            BubbleSortVariation(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_BUBBLE:
            BubbleSort(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_BUBBLE_OPT:
            BubbleSortOpt(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_GNOME:
            GnomeSort(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_ODDEVEN:
            OddEvenSort(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_COCKTAILSHAKER:
            CocktailShakerSort(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_COCKTAILSHAKER_OPT:
            CocktailShakerSortOpt(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_INSERTION:
            InsertionSort(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_SELECTION:
            SelectionSort(BLOCK_LEN, blocks, q);
            break;
        case SORTALGO_MERGE:
            MergeSort(0, BLOCK_LEN - 1, blocks, q);
            break;
        default:
            break;
    }
}

int main(void) {
    const int BLOCK_LEN = WIN_WIDTH / BLOCK_WIDTH;

    // Nanoseconds
    const int BASE_SORTING_SPEED = 55'000;
    const int BASE_SORTING_SPEED_MULTIPLIER = 18;

    int SORTING_SPEED = 550'000;
    const int SORTING_SPEED_MULTIPLIER = 13;

    InitAudioDevice();
    const Sound SORT_SOUND = LoadSound("./resources/sound.wav");
    SetSoundVolume(SORT_SOUND, 0.8);

    Block blocks[BLOCK_LEN];
    Block aux[BLOCK_LEN];
    init(BLOCK_LEN, blocks);

    struct timespec starting_time;
    clock_gettime(CLOCK_MONOTONIC, &starting_time);

    bool sorting = false;
    bool finishing = false;
    Queue q;
    Queue_init(&q);
    BlockCheck last = {.first = 0, .second = 0, .type = BLOCK_TYPE_NONE};

    GameState curr_state = GAMESTATE_INFO;
    SORTALGO selected_algo = SORTALGO_BUBBLE;

    Vector2 mouse_point = { 0.0f, 0.0f };
    Rectangle next_btn = {WIN_WIDTH / 2.0 - 50, WIN_HEIGHT - 100, 100, 50};
    char curr_selected_algo[20];
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
                        strcpy(curr_selected_algo, ALGORITHMS_BTNS[i].name);
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
                    // reset to normal if reshuffle is done after a sorting run
                    blocks[i].color = BLOCK_INIT_COLOR;
                    blocks[i].border_color = BLOCK_INIT_BORDER_COLOR;
                }
            }

            if ((sorting || finishing) && IsKeyPressed(KEY_RIGHT) && SORTING_SPEED - BASE_SORTING_SPEED >= 0) {
                SORTING_SPEED -= BASE_SORTING_SPEED;
            }

            if ((sorting || finishing) && IsKeyPressed(KEY_LEFT) && SORTING_SPEED < BASE_SORTING_SPEED_MULTIPLIER * BASE_SORTING_SPEED) {
                SORTING_SPEED += BASE_SORTING_SPEED;
            }

            // go back to algorithm selection screen
            if (!sorting && !finishing && IsKeyPressed(KEY_R)) {
                curr_state = GAMESTATE_SELECT;
                BlockShuffle(BLOCK_LEN, blocks);
                for (int i = 0; i < BLOCK_LEN; ++i) {
                    // reset to normal if reshuffle is done after a sorting run
                    blocks[i].color = BLOCK_INIT_COLOR;
                    blocks[i].border_color = BLOCK_INIT_BORDER_COLOR;
                }
            }

            // fill the queue with the sorting events
            if (!sorting && IsKeyPressed(KEY_SPACE)) {
                sorting = true;
                for (int i = 0; i < BLOCK_LEN; ++i) {
                    aux[i] = blocks[i];
                }
                RunSortingAlgorithm(selected_algo, BLOCK_LEN, aux, &q);
            }

            // Reset the blocks after a performed action
            // if that action wasn't INPLACE
            if (last.type != BLOCK_TYPE_INPLACE) {
                blocks[last.first].color = BLOCK_INIT_COLOR;
                blocks[last.second].color = BLOCK_INIT_COLOR;
            }

            if (sorting || finishing) {
                struct timespec current_time;
                clock_gettime(CLOCK_MONOTONIC, &current_time);

                long long elapsed = elapsed_ns(&current_time, &starting_time);

                if (Queue_is_empty(&q) || elapsed >= SORTING_SPEED * SORTING_SPEED_MULTIPLIER) {
                    // Update blocks
                    starting_time = current_time;
                    BlockCheck tp = Queue_top(&q);
                    Queue_pop(&q);
                    if (tp.type == BLOCK_TYPE_SWAP) {
                        blocks[tp.first].color = RED;
                        blocks[tp.second].color = RED;
                        BlockSwap(&blocks[tp.first], &blocks[tp.second]);
                    } else if (tp.type == BLOCK_TYPE_CHECK) {
                        int height = (blocks[tp.first].height + blocks[tp.second].height) / 2;
                        if (IsAudioDeviceReady()) {
                            SetSoundPitch(SORT_SOUND, height / 400.0);
                            PlaySound(SORT_SOUND);
                        }

                        blocks[tp.first].color = ORANGE;
                        blocks[tp.second].color = ORANGE;
                    } else if (tp.type == BLOCK_TYPE_REMAP) {
                        blocks[tp.first].height = aux[tp.second].height;
                        blocks[tp.first].y = aux[tp.second].y;

                        blocks[tp.first].color = PINK;
                        blocks[tp.second].color = PINK;
                    } else if (tp.type == BLOCK_TYPE_INPLACE) {
                        blocks[tp.first].color = LIME;
                        if (IsAudioDeviceReady()) {
                            SetSoundPitch(SORT_SOUND, blocks[tp.first].height / 400.0);
                            PlaySound(SORT_SOUND);
                        }
                        if (tp.first == BLOCK_LEN - 1) {
                            finishing = false;
                        }
                    }

                    last = tp;
                    if (Queue_is_empty(&q) && sorting) {
                        sorting = false;
                        finishing = true;
                        for (int i = 0; i < BLOCK_LEN; ++i) {
                            BlockCheck p = {
                                .first = i,
                                .second = i,
                                .type = BLOCK_TYPE_INPLACE
                            };
                            Queue_push(&q, p);
                        }
                    }

                }
            }

            // Draws the FPS, SortingSpeed and the blocks
            BeginDrawing();

            DrawFPS(10, 10);
            DrawSortingInfo(WIN_WIDTH - 300, 10, SORTING_SPEED, curr_selected_algo);

            for (int i = 0; i < BLOCK_LEN; ++i) {
                BlockDraw(blocks[i]);
            }

            ClearBackground(BLACK);

            EndDrawing();
        }
    }

    UnloadSound(SORT_SOUND);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

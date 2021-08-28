#include "SortMethods.h"

SortMethods::SortMethods() {
    fill_random_blocks();
}
void SortMethods::BubleSort() {
    for(int i = 0; i < length; ++i) {
        for(int j = i+1; j < length; ++j) {
            if(blocks_value[i] > blocks_value[j]) {
                std::swap(blocks_value[i], blocks_value[j]);
                isDrawing = true;
            }
        }
        if(isDrawing) {
            PlaySound(sortSound);
            drawBlocks();
            isDrawing = false;
        }
    }
}

void SortMethods::shuffleBlocks() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(blocks_value.begin(), blocks_value.end(), std::default_random_engine(seed));
}

void SortMethods::MergeSort(int leftPointer, int rightPointer) {
    if(leftPointer + 1 < rightPointer) {
        int midPointer = (leftPointer + rightPointer) / 2;
        MergeSort(leftPointer, midPointer);
        MergeSort(midPointer, rightPointer);

        //// Merge the two arrays
        int left_index = leftPointer, right_index = midPointer;
        std::vector<int> changedBlocks;
        while(left_index < midPointer || right_index < rightPointer) {
            isDrawing = true;
            if(right_index == rightPointer || (left_index < midPointer && blocks_value[left_index] < blocks_value[right_index]))
                changedBlocks.push_back(blocks_value[left_index++]);
            else
                changedBlocks.push_back(blocks_value[right_index++]);
        }
        for(left_index = leftPointer, right_index=0; left_index<rightPointer; ++left_index, ++right_index)
            blocks_value[left_index] = changedBlocks[right_index];
    }
    if(isDrawing) {
        drawBlocks();
        isDrawing = false;
    }
}

void SortMethods::drawBlocks() {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            //DrawText("Sorting...", 450, 700, 30, GREEN);
        EndDrawing();
    for(int i = 0; i < length; ++i) {
        BeginDrawing();
            DrawRectangle(blockX + i*(blockWidth+gap), blockY, blockWidth, blockHeigt + blocks_value[i], RED);
        EndDrawing();
    }
}

// Generate a number between 1 and 100
int SortMethods::random_number() {
    return rand() % 300 + 1;
}

int SortMethods::getLength() {
    return length;
}

std::vector<int> SortMethods::getBlocks() {
    return blocks_value;
}

bool SortMethods::getIsDrawing() {
    return isDrawing;
}


void SortMethods::fill_random_blocks() {
    for(int i = 0; i < length; ++i)
        blocks_value.push_back(random_number());
}

void SortMethods::debug() {
    for(int i = 0; i < length; ++i)
        std::cout << blocks_value[i] << " ";
    std::cout << std::endl;
}

void SortMethods::unloadSounds() {
    UnloadSound(sortSound);
}

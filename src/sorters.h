#ifndef SORTERS_H
#define SORTERS_H

#include <stdbool.h>

#include "queue.h"
#include "block.h"

typedef enum SORTALGO {
    SORTALGO_BUBBLE_VARIATION,
    SORTALGO_BUBBLE,
    SORTALGO_BUBBLE_OPT,
    SORTALGO_GNOME,
    SORTALGO_ODDEVEN,
    SORTALGO_COCKTAILSHAKER,
    SORTALGO_COCKTAILSHAKER_OPT,
    SORTALGO_INSERTION,
    SORTALGO_SELECTION,
    SORTALGO_MERGE,
    SORTALGO_QUICK,
    SORTALGO_NONE,
} SORTALGO;

typedef struct AlgorithmBtn {
    Rectangle bounds;
    const char *name;
    SORTALGO type;
} AlgorithmBtn;


#define AVAILABLE_ALGORITHMS SORTALGO_NONE
extern AlgorithmBtn ALGORITHMS_BTNS[AVAILABLE_ALGORITHMS];

void BubbleSortVariation(int len, Block blocks[], Queue *q);
void BubbleSort(int len, Block blocks[], Queue *q);
void BubbleSortOpt(int len, Block blocks[], Queue *q);
void GnomeSort(int len, Block blocks[], Queue *q);
void OddEvenSort(int len, Block blocks[], Queue *q);
void CocktailShakerSort(int len, Block blocks[], Queue *q);
void CocktailShakerSortOpt(int len, Block blocks[], Queue *q);
void InsertionSort(int len, Block blocks[], Queue *q);
void SelectionSort(int len, Block blocks[], Queue *q);
void MergeSort(int left, int right, Block blocks[], Queue *q);
void QuickSort(int left, int right, Block blocks[], Queue *q);
bool IsSorted(int len, Block blocks[]);

#endif // SORTERS_H

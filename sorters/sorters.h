#ifndef SORTERS_H
#define SORTERS_H

#include "../queue/queue.h"
#include "../block/block.h"

typedef enum SortAlgo {
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
    SORTALGO_NONE,
} SortAlgo;

typedef struct AlgorithmBtn {
    Rectangle bounds;
    const char *name;
} AlgorithmBtn;


const int AVAILABE_ALGORITHMS = SORTALGO_NONE;
extern AlgorithmBtn ALGORITHMS_BTNS[AVAILABE_ALGORITHMS];

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

#endif // SORTERS_H

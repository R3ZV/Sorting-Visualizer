#ifndef SORTERS_H
#define SORTERS_H

#include "../queue/queue.h"
#include "../block/block.h"

void InsertionSort(int len, Block blocks[], Queue *q);
void SelectionSort(int len, Block blocks[], Queue *q);
void BubbleSortVariation(int len, Block blocks[], Queue *q);
void BubbleSort(int len, Block blocks[], Queue *q);
void GnomeSort(int len, Block blocks[], Queue *q);
void OddEvenSort(int len, Block blocks[], Queue *q);
void CocktailShakerSort(int len, Block blocks[], Queue *q);
void CocktailShakerSortOpt(int len, Block blocks[], Queue *q);
void BubbleSortOpt(int len, Block blocks[], Queue *q);
void MergeSort(int left, int right, Block blocks[], Queue *q);

#endif // SORTERS_H

#include "sorters.h"

void InsertionSort(int len, Block blocks[], Queue *q) {
    for (int i = 1; i < len; ++i) {
        Block a = blocks[i];
        int j = i - 1;
        for (; j >= 0 && a.height < blocks[j].height ; --j) {
            BlockCheck p = { .first = j, .second = j + 1, .type = BLOCK_REMAP};
            Queue_push(q, p);
            blocks[j + 1] = blocks[j];
        }
        BlockCheck p = { .first = j + 1, .second = i, .type = BLOCK_REMAP};
        Queue_push(q, p);
        blocks[j + 1] = a;
    }
}

void SelectionSort(int len, Block blocks[], Queue *q) {
    for (int i = 0; i < len; ++i) {
        int minBlock = i;
        for (int j = i; j < len; ++j) {
            BlockCheck p = { .first = j, .second = minBlock, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[minBlock].height) {
                minBlock = j; 
            }
        }
        if (minBlock != i) {
            BlockSwap(&blocks[i], &blocks[minBlock]);
            BlockCheck p = { .first = i, .second = minBlock, .type = BLOCK_SWAP};
            Queue_push(q, p);
        }
    }
}

void BubbleSortVariation(int len, Block blocks[], Queue *q) {
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            BlockCheck p = { .first = i, .second = j, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[i].height) {
                BlockSwap(&blocks[j], &blocks[i]);
                BlockCheck p = { .first = i, .second = j, .type = BLOCK_SWAP};
                Queue_push(q, p);
            }
        }
    }
}

void BubbleSort(int len, Block blocks[], Queue *q) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int j = 1; j < len; ++j) {
            BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[j - 1].height) {
                sorted = false;
                BlockSwap(&blocks[j], &blocks[j - 1]);
                BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
            }
        }
    }
}

void GnomeSort(int len, Block blocks[], Queue *q) {
    int pos = 0;
    while (pos < len) {
        if (pos != 0) {
            BlockCheck p = { .first = pos, .second = pos - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
        }
        if (pos == 0 || blocks[pos].height > blocks[pos - 1].height) {
            pos++;
        } else {
            BlockSwap(&blocks[pos], &blocks[pos - 1]);
            BlockCheck p = { .first = pos, .second = pos - 1, .type = BLOCK_SWAP};
            Queue_push(q, p);
            pos--;
        }
    }
}

void OddEvenSort(int len, Block blocks[], Queue *q) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 1; i < len; i += 2) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }

        for (int i = 2; i < len; i += 2) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }
    }
}

void CocktailShakerSort(int len, Block blocks[], Queue *q) {
    bool sorted = false;
    while (!sorted) { 
        sorted = true;
        for (int i = 1; i < len; ++i) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }
        if (sorted) {
            break;
        }

        for (int i = len - 1; i > 0; --i) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }
    }
}

void CocktailShakerSortOpt(int len, Block blocks[], Queue *q) {
    bool sorted = false;
    int swaps = 0;
    while (!sorted) {
        sorted = true;
        for (int i = 1 + swaps; i < len - swaps; ++i) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }
        if (sorted) {
            break;
        }

        for (int i = len - 1 - swaps; i > 0 + swaps; --i) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }
        swaps++;
    }
}

void BubbleSortOpt(int len, Block blocks[], Queue *q) {
    int sorted = 0;
    while (true) {
        bool swaped = false;
        for (int j = 1; j < len - sorted; ++j) {
            BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[j - 1].height) {
                swaped = true;
                BlockSwap(&blocks[j], &blocks[j - 1]);
                BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_SWAP};
                Queue_push(q, p);
            }
        }
        if (!swaped) {
            break;
        }
        sorted++;
    }
}

void MergeSort(int left, int right, Block blocks[], Queue *q) {
    // TODO
}

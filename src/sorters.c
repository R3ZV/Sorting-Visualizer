#include "sorters.h"

#define ALGORITHM_BTN_WIDTH 270
#define ALGORITHM_BTN_HEIGHT 50

#define ALGORITHM_BTN_X 70
#define ALGORITHM_BTN_Y 200
#define ALGORITHM_BTN_XGAP 30
#define ALGORITHM_BTN_YGAP 30

AlgorithmBtn ALGORITHMS_BTNS[AVAILABLE_ALGORITHMS] = {
    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 1 COL 1
            .x = ALGORITHM_BTN_X + 0 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 0 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "Bubble Var",
        .type = SORTALGO_BUBBLE_VARIATION
    },

    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 1 COL 2
            .x = ALGORITHM_BTN_X + 1 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 0 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "Bubble",
        .type = SORTALGO_BUBBLE
    },


    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 1 COL 3
            .x = ALGORITHM_BTN_X + 2 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 0 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "Bubble Opt",
        .type = SORTALGO_BUBBLE_OPT
    },

    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 1 COL 4
            .x = ALGORITHM_BTN_X + 3 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 0 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "Gnome",
        .type = SORTALGO_GNOME
    },

    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 2 COL 1
            .x = ALGORITHM_BTN_X + 0 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 1 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "OddEven",
        .type = SORTALGO_ODDEVEN
    },

    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 2 COL 2
            .x = ALGORITHM_BTN_X + 1 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 1 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "CocktailShaker",
        .type = SORTALGO_COCKTAILSHAKER
    },

    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 2 COL 3
            .x = ALGORITHM_BTN_X + 2 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 1 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "CocktailShaker Opt",
        .type = SORTALGO_COCKTAILSHAKER_OPT
    },

    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 2 COL 4
            .x = ALGORITHM_BTN_X + 3 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 1 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "Insertion",
        .type = SORTALGO_INSERTION
    },

    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 3 COL 1
            .x = ALGORITHM_BTN_X + 0 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 2 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "Selection",
        .type = SORTALGO_SELECTION
    },

    (AlgorithmBtn) {
        .bounds = (Rectangle) {
            // ROW 3 COL 2
            .x = ALGORITHM_BTN_X + 1 * (ALGORITHM_BTN_WIDTH + ALGORITHM_BTN_XGAP),
            .y = ALGORITHM_BTN_Y + 2 * (ALGORITHM_BTN_HEIGHT + ALGORITHM_BTN_YGAP),
            .width = ALGORITHM_BTN_WIDTH,
            .height = ALGORITHM_BTN_HEIGHT
        },
        .name = "Merge",
        .type = SORTALGO_MERGE
    }
};

void InsertionSort(int len, Block blocks[], Queue *q) {
    for (int i = 1; i < len; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            BlockCheck p = { .first = j + 1, .second = j, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[j + 1].height < blocks[j].height) {
                BlockCheck p = { .first = j + 1, .second = j, .type = BLOCK_TYPE_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[j + 1], &blocks[j]);
            }
        }
    }
}

void SelectionSort(int len, Block blocks[], Queue *q) {
    for (int i = 0; i < len; ++i) {
        int minBlock = i;
        for (int j = i; j < len; ++j) {
            BlockCheck p = { .first = j, .second = minBlock, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[minBlock].height) {
                minBlock = j; 
            }
        }
        if (minBlock != i) {
            BlockSwap(&blocks[i], &blocks[minBlock]);
            BlockCheck p = { .first = i, .second = minBlock, .type = BLOCK_TYPE_SWAP};
            Queue_push(q, p);
        }
    }
}

void BubbleSortVariation(int len, Block blocks[], Queue *q) {
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            BlockCheck p = { .first = i, .second = j, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[i].height) {
                BlockSwap(&blocks[j], &blocks[i]);
                BlockCheck p = { .first = i, .second = j, .type = BLOCK_TYPE_SWAP};
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
            BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[j - 1].height) {
                sorted = false;
                BlockSwap(&blocks[j], &blocks[j - 1]);
                BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_TYPE_SWAP};
                Queue_push(q, p);
            }
        }
    }
}

void GnomeSort(int len, Block blocks[], Queue *q) {
    int pos = 0;
    while (pos < len) {
        if (pos != 0) {
            BlockCheck p = { .first = pos, .second = pos - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
        }
        if (pos == 0 || blocks[pos].height > blocks[pos - 1].height) {
            pos++;
        } else {
            BlockSwap(&blocks[pos], &blocks[pos - 1]);
            BlockCheck p = { .first = pos, .second = pos - 1, .type = BLOCK_TYPE_SWAP};
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
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }

        for (int i = 2; i < len; i += 2) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_SWAP};
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
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }
        if (sorted) {
            break;
        }

        for (int i = len - 1; i > 0; --i) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_SWAP};
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
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_SWAP};
                Queue_push(q, p);
                BlockSwap(&blocks[i], &blocks[i - 1]);
                sorted = false;
            }
        }
        if (sorted) {
            break;
        }

        for (int i = len - 1 - swaps; i > 0 + swaps; --i) {
            BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[i].height < blocks[i - 1].height) {
                BlockCheck p = { .first = i, .second = i - 1, .type = BLOCK_TYPE_SWAP};
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
            BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_TYPE_CHECK};
            Queue_push(q, p);
            if (blocks[j].height < blocks[j - 1].height) {
                swaped = true;
                BlockSwap(&blocks[j], &blocks[j - 1]);
                BlockCheck p = { .first = j, .second = j - 1, .type = BLOCK_TYPE_SWAP};
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


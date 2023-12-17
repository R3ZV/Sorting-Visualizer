set -e
gcc main.c ./queue/queue.c ./block/block.c ./sorters/sorters.c -I/usr/local/include -L/usr/local/lib -lraylib -o main
./main

set -e
gcc main.c queue.c -I/usr/local/include -L/usr/local/lib -lraylib -o main
./main

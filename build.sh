set -e
cd src
g++ SortMethods.cpp -c
cd ..
g++ src/SortMethods.o main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main
./main

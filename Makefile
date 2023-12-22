run:
	@g++ main.cpp ./queue/queue.cpp ./block/block.cpp ./sorters/sorters.cpp -I/usr/local/include -L/usr/local/lib -lraylib -o main
	./main

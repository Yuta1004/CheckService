G++ = g++
OPTS = -Wall -std=c++17 --pedantic-errors

make:
	make build
	make run

build: main.cpp
	$(G++) $(OPTS) -o main $^

run: main
	./main


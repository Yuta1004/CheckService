G++ = g++
BOOST_OPT = -I /usr/local/Cellar/boost/1.71.0/include
OPTS = -Wall -std=c++17 --pedantic-errors $(BOOST_OPT)


make:
	make build
	make run

build: main.cpp
	$(G++) $(OPTS) -o main $^

run: main
	./main


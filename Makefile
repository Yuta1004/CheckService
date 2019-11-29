G++ = g++
BOOST_OPT = -I /usr/local/Cellar/boost/1.71.0/include
OPTS = -Wall -std=c++17 --pedantic-errors $(BOOST_OPT)
SRCS = $(wildcard *.cpp)


make:
	make build
	make run

test:
	make build_test
	make run_test

build_test: test_service_knocker.cpp
	$(G++) $(OPTS) -o test_service_knocker $< $(filter-out main.cpp test_service_knocker.cpp, $(SRCS))

run_test: test_service_knocker
	./test_service_knocker


build: main.cpp
	$(G++) $(OPTS) -o main $^

run: main
	./main

clean:
	rm -rf main test_service_knocker

G++ = g++
BOOST_OPT = -I /usr/local/Cellar/boost/1.71.0/include
OPTS = -Wall -std=c++17 --pedantic-errors $(BOOST_OPT)
SRCS = $(wildcard *.cpp)


make:
	make build
	make run

build: main.cpp
	$(G++) $(OPTS) -o main $^

run: main
	./main

test:
	$(call do_test, test_service_knocker)

clean:
	rm -rf main test_service_knocker

define do_test
	$(eval TARGET := $(subst $() ,,$1))
	$(G++) $(OPTS) -o $(TARGET) $(TARGET).cpp $(filter-out main.cpp test_%.cpp, $(SRCS))
	./$(TARGET)
endef


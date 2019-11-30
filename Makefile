G++ = g++
OPTS = -Wall -std=c++17 --pedantic-errors
SRCS = $(wildcard *.cpp */*.cpp)


make:
	make build
	make run

build: main.cpp
	$(G++) $(OPTS) -o main $^

run: main
	./main

test:
	$(call do_test, test_service_knocker)
	$(call do_test, test_url_parser)

clean:
	rm -rf main test_url_parser test_service_knocker

define do_test
	$(eval TARGET := $(subst $() ,,$1))
	$(G++) $(OPTS) -o $(TARGET) test/$(TARGET).cpp $(filter-out main.cpp test/%.cpp, $(SRCS))
	./$(TARGET)
	@rm -rf $(TARGET)
	@echo ""
endef

.PHONY: test

G++ = g++
OPTS = -Wall -std=c++17 --pedantic-errors
SRCS = $(wildcard *.cpp */*.cpp)
TEST_TARGET = tcp_connector


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
	$(call do_test, test_dns_resolver)
	$(call do_test, test_tcp_connector)

test-once:
	$(call do_test, test_$(TEST_TARGET))

clean:
	rm -rf main test_url_parser test_service_knocker test_dns_resolver

define do_test
	$(eval TARGET := $(subst $() ,,$1))
	$(G++) $(OPTS) -o $(TARGET) test/$(TARGET).cpp $(filter-out main.cpp test/%.cpp, $(SRCS))
	./$(TARGET)
	@rm -rf $(TARGET)
	@echo ""
endef

.PHONY: test

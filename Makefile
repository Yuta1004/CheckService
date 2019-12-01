G++ = g++
OPTS = -Wall -std=c++17 --pedantic-errors
SRCS = $(wildcard *.cpp */*.cpp)
TARGET = empty


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
	$(call do_test, test_$(TARGET))

clean:
	rm -rf main test_url_parser test_service_knocker test_dns_resolver

define do_test
	echo $1
	$(eval TARGET_FORM := $(subst $() ,,$1))
	$(G++) $(OPTS) -o $(TARGET_FORM) test/$(TARGET_FORM).cpp $(filter-out main.cpp test/%.cpp, $(SRCS))
	./$(TARGET_FORM)
	@rm -rf $(TARGET_FORM)
	@echo ""
endef

.PHONY: test

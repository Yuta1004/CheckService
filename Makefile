G++ = g++
OPTS = -Wall -std=c++17 --pedantic-errors -I/usr/local/opt/openssl/include -lssl -lcrypto
SRCS = $(wildcard *.cpp */*.cpp)
TARGET = empty
PRODNAME = check_server


make:
	make build
	make run

build: main.cpp
	$(G++) $(OPTS) -o $(PRODNAME) $^ $(filter-out main.cpp test/%.cpp, $(SRCS))

run: $(PRODNAME)
	./$(PRODNAME)

test:
	$(call do_test, test_service_knocker)
	$(call do_test, test_url_parser)
	$(call do_test, test_dns_resolver)
	$(call do_test, test_tcp_connector)

test-once:
	$(call do_test, test_$(TARGET))

clean:
	rm -rf check_server test_*

define do_test
	$(eval TARGET_FORM := $(subst $() ,,$1))
	$(G++) $(OPTS) -o $(TARGET_FORM) test/$(TARGET_FORM).cpp $(filter-out main.cpp test/%.cpp, $(SRCS))
	./$(TARGET_FORM)
	@rm -rf $(TARGET_FORM)
	@echo ""
endef

.PHONY: test

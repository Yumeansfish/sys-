CXXFLAGS=-Wall -g -std=c++11
CFLAGS=-Wall -g

.SILENT:

SHELL=/bin/bash

PROGRAM=messaging

TIMEOUT=8

TESTS_DIR=tests

TESTS_CXX:=$(wildcard $(TESTS_DIR)/*.cc)
TESTS_BIN:=$(patsubst $(TESTS_DIR)/%.cc, $(TESTS_DIR)/%, $(TESTS_CXX))
TESTS:=$(patsubst $(TESTS_DIR)/%.cc, %, $(TESTS_CXX))

.PHONY: all
all: check

$(PROGRAM).o: $(PROGRAM).c
	@$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/%: $(TESTS_DIR)/%.o $(PROGRAM).o
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TESTS_DIR)/$*.o $(PROGRAM).o -o $@

.PHONY: check
check: $(TESTS_BIN)
	@for t in $(TESTS); do \
		echo -n "Running test $$t..." ; \
		output=$$($(TESTS_DIR)/$$t 2>&1) & \
		prog_pid=$$!; \
		( sleep $(TIMEOUT); kill $$prog_pid > /dev/null 2>&1 ) & \
		killer_pid=$$!; \
		wait $$prog_pid; \
		res=$$?; \
		if test $$res -gt 128; \
		then \
			sig=`kill -l $$(($$res - 128))`; \
			case $$sig in \
				ABRT ) echo "FAIL (SIG$$sig - assertion failed)"; ;; \
				TERM ) echo "FAIL (TIMEOUT after $(TIMEOUT)s)"; ;; \
				SEGV ) echo "FAIL (SIG$$sig - segmentation fault)"; ;; \
				BUS ) echo "FAIL (SIG$$sig - bus error)"; ;; \
				FPE ) echo "FAIL (SIG$$sig - floating point exception)"; ;; \
				* ) echo "FAIL (SIG$$sig)"; ;; \
			esac ; \
			if [ -n "$$output" ]; then echo "  Output: $$output"; fi; \
			echo "  Run: $(TESTS_DIR)/$$t"; \
		elif test $$res -ne 0; \
		then \
			echo "FAIL (exit code $$res)"; \
			if [ -n "$$output" ]; then echo "  Output: $$output"; fi; \
			echo "  Run: $(TESTS_DIR)/$$t"; \
		else \
			kill $$killer_pid > /dev/null 2>&1; wait $$killer_pid 2>/dev/null;\
			echo "PASS" ;\
		fi; \
	done


.PHONY: clean
clean:
	rm -f $(PROGRAM) tests/*.o $(TESTS_BIN)



CFLAGS=-Wall -g
.PHONY: all
SHELL=/bin/bash

PROGRAM=fwd

TIMEOUT=8

TESTS_DIR=tests

TESTS_C:=$(wildcard $(TESTS_DIR)/*.c)
TESTS_BIN:=$(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/%, $(TESTS_C))
TESTS:=$(patsubst $(TESTS_DIR)/%.c, %, $(TESTS_C))

.PHONY: all
all: check

$(TESTS_DIR)/%: $(TESTS_DIR)/%.o $(PROGRAM).o
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_DIR)/$*.o $(PROGRAM).o -o $@

.PHONY: check
check: $(TESTS_BIN)
	@exec 2> /dev/null; \
	for t in $(TESTS); do \
		echo -n "Running test $$t..." ; \
		"$(TESTS_DIR)/$$t" &\
		prog_pid=$$!; \
		( sleep $(TIMEOUT); kill $$prog_pid > /dev/null 2>&1 ) & \
		killer_pid=$$!; \
		wait $$prog_pid; \
		res=$$?; \
		if test $$res -gt 128; \
		then \
			echo KILLED; \
			echo "you may run $(TESTS_DIR)/$$t to see what went wrong" ;\
		else \
			kill $$killer_pid > /dev/null 2>&1 ;\
			wait $$killer_pid; \
			echo "PASSED" ;\
		fi; \
	done

.PHONY: clean
clean:
	rm -f $(PROGRAM) tests/*.o $(TESTS_BIN)



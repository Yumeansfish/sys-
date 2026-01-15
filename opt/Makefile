CC = gcc
CFLAGS = -Wall -g

# Main program
OTP = otp

# Test files
TESTS = tests/test1 tests/test2 tests/test3 tests/test4 tests/test5 tests/test6

.PHONY: all clean test

all: $(OTP) $(TESTS)

$(OTP): opt.c
	$(CC) $(CFLAGS) -o $@ $<

tests/test1: tests/test1.c
	$(CC) $(CFLAGS) -o $@ $<

tests/test2: tests/test2.c
	$(CC) $(CFLAGS) -o $@ $<

tests/test3: tests/test3.c
	$(CC) $(CFLAGS) -o $@ $<

tests/test4: tests/test4.c
	$(CC) $(CFLAGS) -o $@ $<

tests/test5: tests/test5.c
	$(CC) $(CFLAGS) -o $@ $<

tests/test6: tests/test6.c
	$(CC) $(CFLAGS) -o $@ $<

test: all
	@echo "========================================"
	@echo "Running all tests..."
	@echo "========================================"
	@echo ""
	@cd tests && ./test1 && echo ""
	@cd tests && ./test2 && echo ""
	@cd tests && ./test3 && echo ""
	@cd tests && ./test4 && echo ""
	@cd tests && ./test5 && echo ""
	@cd tests && ./test6 && echo ""
	@echo "========================================"
	@echo "All tests completed!"
	@echo "========================================"

clean:
	rm -f $(OTP) $(TESTS)
	rm -f tests/*.txt tests/test*_* tests/key tests/key.counter

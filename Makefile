CC ?= gcc
TEST_CC = gdb
CFLAGS = -Wall -Iinc
LDFLAGS ?=
SRC = $(shell find src -name '*.c')
TEST_SRC = $(shell find tests -name '*.c')
OBJ = $(SRC:.c=.o)
OUT = dist/sms

all: $(OUT)

$(OUT): $(OBJ)
	@mkdir -p dist
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

release: clean
	@make LDFLAGS="-s" OUT=$(OUT)

neat:
	@make
	@find src -name '*.o' -delete

clear:
	@echo "Cleaning output files..."
	rm -f $(OUT)
	find src -name '*.o' -delete
	@echo "Cleaned!"


# tests

test:
	@echo "Compiling tests..."
	$(CC) $(CFLAGS) -DTEST -o dist/test_runner $(SRC) $(TEST_SRC)

test-neat:
	@make test
	@echo "\n\n"
	@make test-run
	@echo "\n\n"
	@make test-clear

test-dbg:
	@$(TEST_CC) ./dist/test_runner

test-run:
	@./dist/test_runner

test-clear:
	@echo "Cleaning test runner..."
	rm -f dist/test_runner
	find src -name '*.o' -delete
	@echo "Cleaned!"
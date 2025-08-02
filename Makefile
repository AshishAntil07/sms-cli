CC = gcc
CFLAGS = -Wall -Iinc
SRC = $(shell find src -name '*.c')
OBJ = $(SRC:.c=.o)
OUT = dist/app

all: $(OUT)

$(OUT): $(OBJ)
	@mkdir -p dist
	$(CC) $(OBJ) -o $(OUT)

clean:
	find src -name '*.o' -delete
	rm -f $(OUT)
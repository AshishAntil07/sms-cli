CC = gcc
CFLAGS = -Wall -Iinc
SRC = $(shell find src -name '*.c')
OBJ = $(SRC:.c=.o)
OUT = dist/sms

all: $(OUT)

$(OUT): $(OBJ)
	@mkdir -p dist
	$(CC) $(OBJ) -o $(OUT)

neat:
	make
	find src -name '*.o' -delete

clear:
	find src -name '*.o' -delete
	rm -f $(OUT)
CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/image_processor.c
OBJ = $(SRC:.c=.o)
TARGET = ppm_processor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) $(TARGET).exe

.PHONY: all clean

CC = gcc
CFLAGS = -c -std=gnu99 -m32 -Wall -g -O2
LD = $(CC) -m32
LDFLAGS = -lpthread

TARGET = main

OBJECTS = $(patsubst %.c, %.o, $(shell find . -name '*.c'))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

# You don't even need to be explicit here,
# compiling C files is handled automagically by Make.
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(TARGET) $(OBJECTS)

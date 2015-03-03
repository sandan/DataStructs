CC = gcc
CFLAGS = -c -m64 -Wall -g -O2
LD = $(CC)
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

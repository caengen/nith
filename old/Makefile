CC=gcc
CFLAGS=-std=c99 -Wall -Werror -g
LDFLAGS_START=
LDFLAGS_END=
SOURCES=main.c BinaryFunctions.c FileScanner.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=innt

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS_START) $(OBJECTS) -o $@ $(LDFLAGS_END)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
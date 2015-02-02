CC=gcc
CFLAGS=-std=c99 -Wall -Werror -g
SOURCES=main.c filehandler.c tgamanipulator.c utils.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=innf

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

remake: clean all

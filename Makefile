CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
SOURCES=
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=innf

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

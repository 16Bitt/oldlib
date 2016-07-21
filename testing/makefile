SOURCES	= $(patsubst %.c,%.o,$(wildcard *.c))
TARGET	= test
CFLAGS	= -Wall -Werror -g -I../ -l oldlib

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	-rm $(SOURCES)
	-rm $(TARGET)

run: all
	./$(TARGET)

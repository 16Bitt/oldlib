SOURCES	= $(patsubst %.c,%.o,$(wildcard *.c))
TARGET	= test
OLDLIB	= ../oldlib.a
CFLAGS	= -Wall -Werror -g -I../

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(OLDLIB) -o $(TARGET)

clean:
	-rm $(SOURCES)
	-rm $(TARGET)

run: all
	./$(TARGET)

SOURCES	= $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS	= -Werror -Wall -std=c99 -g -shared -fPIC
TARGET	= liboldlib.so

all: $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: all
	cd testing && make run

clean:
	-cd testing && make clean
	-rm $(SOURCES)
	-rm $(TARGET)

install: all
	cp $(TARGET) /usr/local/lib/
	cp oldlib.h /usr/local/include/
	ldconfig

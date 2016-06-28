SOURCES	= $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS	= -Werror -Wall -std=c99 -g
TARGET	= oldlib.a

all: $(SOURCES)
	$(AR) -rcs $(TARGET) $(SOURCES)

test: all
	cd testing && make run

clean:
	-cd testing && make clean
	-rm $(SOURCES)
	-rm $(TARGET)

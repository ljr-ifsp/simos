CC := gcc
CFLAGS := -c -Wall -Werror
INCLUDES := -I../include 
SOURCES := list.c process.c scheduler.c memory.c simos.c
OBJECTS := $(SOURCES:.c=.o)
OUT := ../lib/libsimos.a


.SUFFICES: .c

all: $(OUT)

$(OUT): $(OBJECTS) simos

simos:
	@echo "Generating ../lib/libsimos.a"
	ar rcs $(OUT) $(OBJECTS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(OUT)  


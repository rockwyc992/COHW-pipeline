#
# Makefile
#
PROG=pipeline

CC=g++
CFLAGS=-Os -O2 -Wall $(SOURCE_FLAGS) -g -Iinclude

TARGET=$(PROG)
OBJS=pipeline.o \
	lib/fetch.o \
	lib/decode.o \
	lib/execute.o \
	lib/memory.o \
	lib/write.o \
	lib/global.o

.SUFFIXS:
.SUFFIXS: .cpp
.PHONY: clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(TARGET)


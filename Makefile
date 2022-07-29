CC = g++
CFLAGS = 

TARGET = main
SOURCES := $(shell find . -name '*.cpp')
all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
clean:
	rm $(TARGET)

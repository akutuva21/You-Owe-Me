CC = g++
CFLAGS = -lsfml-graphics -lsfml-window

TARGET = main
SOURCES := $(wildcard *.cpp)
all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
clean:
	rm $(TARGET)

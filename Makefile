CC = g++
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = main
SOURCES := $(wildcard src/*.cpp)
all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
clean:
	rm $(TARGET)

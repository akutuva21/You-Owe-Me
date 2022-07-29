CC = g++
CFLAGS = 

TARGET = main
#SOURCES := main.cpp List.cpp Matrix.cpp
SOURCES := $(wildcard *.cpp)
all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
clean:
	rm $(TARGET)

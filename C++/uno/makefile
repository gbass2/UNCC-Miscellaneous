CC = g++
CFLAGS = -I. --std=c++17
OBJS = main.o card.o
HEADERS = card.h
TARGET = uno

.PHONY : clean run all

all: clean $(TARGET) run

%.o: %.cpp $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(TARGET)
	rm -rf *.o

run:
	./$(TARGET)

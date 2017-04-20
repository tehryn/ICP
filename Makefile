CC=g++
OFLAGS=-c -Wall -Wextra -pedantic -g -std=c++11
CFLAGS=-std=c++11
all: icp.out

Card.o: Card.cpp Card.hpp
	$(CC) $(OFLAGS) $^
Card_stack.o: Card_stack.cpp Card_stack.hpp
	$(CC) $(OFLAGS) $^
Single_color_stack.o: Single_color_stack.cpp Single_color_stack.hpp
	$(CC) $(OFLAGS) $^
Working_stack.o: Working_stack.cpp Working_stack.hpp
	$(CC) $(OFLAGS) $^
Board.o: Board.cpp Board.hpp
	$(CC) $(OFLAGS) $^
Console.o: Console.cpp Console.hpp
	$(CC) $(OFLAGS) $^
main.o: main.cpp
	$(CC) $(OFLAGS) $^


icp.out: main.o Single_color_stack.o Card_stack.o Working_stack.o Board.o Console.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm *.o
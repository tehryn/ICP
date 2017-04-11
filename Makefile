CC=g++
OFLAGS=-c -Wall -Wextra -pedantic -g -std=c++11
CFLAGS=-std=c++11
all: icp.out

Card_stack.o: Card_stack.cpp Card_stack.hpp Card.hpp
	$(CC) $(OFLAGS) $^
Single_color_stack.o: Single_color_stack.cpp Card_stack.hpp  Single_color_stack.hpp Card.hpp
	$(CC) $(OFLAGS) $^
Working_stack.o: Working_stack.cpp Working_stack.hpp Card_stack.hpp Card.hpp
	$(CC) $(OFLAGS) $^
Board.o: Board.cpp Single_color_stack.hpp Card.hpp Card_stack.hpp Working_stack.hpp Card_deck_visible.hpp Card_deck_hidden.hpp
	$(CC) $(OFLAGS) $^
main.o: main.cpp Single_color_stack.hpp Card.hpp Card_stack.hpp Working_stack.hpp
	$(CC) $(OFLAGS) $^

icp.out: main.o Single_color_stack.o Card_stack.o Working_stack.o Board.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm *.o
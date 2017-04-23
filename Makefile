CC=g++
OFLAGS=-c -Wall -Wextra -pedantic -g -std=c++11
CFLAGS=-std=c++11
OBJDIR=build
SRCDIR=src/game/
MAIN=src/main/main.cpp
OBJECT_GAME=$(addprefix $(OBJDIR)/, Card_stack.o Single_color_stack.o \
         	Working_stack.o Board.o Console.o hra2017-cli.o)
all: bin/hra2017-cli

bin/hra2017-cli: $(OBJECT_GAME)
	$(CC) $(CFLAGS) -o $@ $^

build/Card_stack.o : $(SRCDIR)Card_stack.cpp $(SRCDIR)Card_stack.hpp \
					 $(SRCDIR)Card.hpp
	$(CC) $(OFLAGS) $< -o $@

build/Single_color_stack.o : $(SRCDIR)Single_color_stack.cpp \
							 $(SRCDIR)Single_color_stack.hpp $(SRCDIR)Card.hpp \
							 $(SRCDIR)Card_stack.hpp
	$(CC) $(OFLAGS) -o $@ $<

build/Working_stack.o : $(SRCDIR)Working_stack.cpp $(SRCDIR)Working_stack.hpp \
						$(SRCDIR)Card.hpp $(SRCDIR)Card_stack.hpp
	$(CC) $(OFLAGS) -o $@ $<

build/Board.o : $(SRCDIR)Board.cpp $(SRCDIR)Card_stack.hpp $(SRCDIR)Card.hpp \
				$(SRCDIR)Working_stack.hpp $(SRCDIR)Card_deck_visible.hpp \
				$(SRCDIR)Single_color_stack.hpp $(SRCDIR)History.hpp \
				$(SRCDIR)Card_deck_hidden.hpp $(SRCDIR)Move.hpp
	$(CC) $(OFLAGS) -o $@ $<

build/Console.o : $(SRCDIR)Console.cpp $(SRCDIR)Console.hpp $(SRCDIR)Card.hpp \
				  $(SRCDIR)Board.hpp $(SRCDIR)Move.hpp
	$(CC) $(OFLAGS) -o $@ $<

build/hra2017-cli.o : $(MAIN)
	$(CC) $(OFLAGS) -o $@ $< -DBUILDCLI

.PHONY: clean doxygen pack
clean:
	rm $(OBJECT_GAME) bin/hra2017-cli
doxygen:
	doxygen doc/Doxyfile
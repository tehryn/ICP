#ifndef BOARD
#define BOARD
#include "Card.hpp"
#include "Card_stack.hpp"
#include "Single_color_stack.hpp"
#include "Working_stack.hpp"
#include "Card_deck_hidden.hpp"
#include "Card_deck_visible.hpp"
#include <string>
#include <iostream>

class  Board {
private:
    Working_stack      working_stacks[7];
    Single_color_stack color_stacks[4];
    Card_deck_visible  visible_deck;
    Card_deck_hidden   hidden_deck;
public:
    Board() {}
    void new_game();
    Board load_game(std::string filename);
    bool save_game(Board game);
};
#endif
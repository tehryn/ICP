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

    size_t score = 0;
public:
    Board() {}
    void new_game();
    Board load_game(std::string filename);
    bool save_game(Board game);
    Working_stack *get_stack(unsigned id) {
        return (id<7)?(&(working_stacks[id])):NULL;
    }
    bool move_Wstack(unsigned from, unsigned to, Card card);
    bool move_Cstack(unsigned from, unsigned to) {
        if (color_stacks[to].size() != 0 || color_stacks[from].size() != 1 || to > 3 || from > 3) {
            return false;
        }
        else {
            return color_stacks[to].push(color_stacks[from].pop());
        }
    }
    bool fromW_toC(unsigned from, unsigned to);

};
#endif
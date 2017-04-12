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
    /* Removes all cards from board and creates new game. */
    void new_game();
    Board load_game(std::string filename);
    bool save_game(Board game);
    Working_stack *get_stack(unsigned id) {
        return (id<7)?(&(working_stacks[id])):NULL;
    }
    /**
     * Moves card(s) between two working packs. Moves all cards until specific
     * card is reached. When false is returned, no changes was made.
     * @param  from From wich pack cards will be taken.
     * @param  to   To which pack cards will be added.
     * @param  card Specific card used as a guard.
     * @return      True on succes, False on invalid operation.
     */
    bool fromW_toW(unsigned from, unsigned to, Card card);
    /**
     * Moves card between two color packs. Only ace can be moved. When false is
     * returned, no changes was made.
     * @param  from From which pack card will be taken.
     * @param  to   To which pack card will be added.
     * @return      True on succes, False on invalid operation.
     */
    bool fromC_toC(unsigned from, unsigned to);
    /**
     * Moves card from Working pack to Color pack. When false is returned, no
     * changes are made.
     * @param  from From which pack card will be taken.
     * @param  to   To which pack card will be added.
     * @return      True on succes, false on invalid operation.
     */
    bool fromW_toC(unsigned from, unsigned to);
    /**
     * Moves card from color pack to working pack. When false is returned, no
     * changes are made.
     * @param  from From which pack card will be taken.
     * @param  to   To which pack card will be added.
     * @return      True on succes, false on invalid operation.
     */
    bool fromC_toW(unsigned from, unsigned to);
    /**
     * Takes next card from hidden pack to visible pack or move all cards from
     * Visible pack into hidden, if hidden pack is empty.
     */
    void fromH_toV();
};
#endif
#ifndef BOARD
#define BOARD
#include "Card.hpp"
#include "Card_stack.hpp"
#include "Single_color_stack.hpp"
#include "Working_stack.hpp"
#include "Card_deck_hidden.hpp"
#include "Card_deck_visible.hpp"
#include "Move.hpp"
#include "History.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <exception>



class  Board {
private:
    Working_stack      working_stacks[7];
    Single_color_stack color_stacks[4];
    Card_deck_visible  visible_deck;
    Card_deck_hidden   hidden_deck;

    History history;
    size_t score = 0;
public:
    Board() {}
    /**
     * Removes all cards from board and creates new game.
     */
    void new_game();
    bool load_game(std::string filename);

    bool save_game(std::string filename);

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
     * Moves card from visible deck to specific color stack.
     * @param  to ID of color stack.
     * @return    True on succes, false on invalid operation.
     */
    bool fromV_toC(unsigned to);

    /**
     * Moves card from Visible deck to specific color stack.
     * @param  to ID of color stack.
     * @return    True on succes, false on invalid operation.
     */
    bool fromV_toW(unsigned to);

    /**
     * Takes next card from hidden pack to visible pack or move all cards from
     * Visible pack into hidden, if hidden pack is empty.
     */
    void fromH_toV();

    /**
     * Undo operation. Can be used multipe times. If game is loaded, undo cannot
     * be done to states of game that was before saving.
     */
    Move undo();

    std::vector<Move> help();

    friend std::ostream& operator << (std::ostream& stream, Board board) {
        for (unsigned i = 0; i < 7 ; i++) {
            stream << "Working " << i << ": ";
            stream << board.working_stacks[i] << "\n";
        }
        for (unsigned i = 0; i < 4 ; i++) {
            stream << "  Color " << i << ": ";
            stream << board.color_stacks[i].top() << "\n";
        }
        stream << " Hidden 0: " << board.hidden_deck.top()  << "\n";
        stream << "Visible 0: " << board.visible_deck.top() << "\n";
        stream << "    Score: " << board.score              << "\n";
        return stream;
    }
};
#endif
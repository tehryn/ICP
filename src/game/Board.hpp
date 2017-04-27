/** @file
 *  Header file for class Board.
 *  @author Matejka Jiri (xmatej52)
 */
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
#include <stdexcept>


/**
 * Class representing table with cards. Methods represents all possible moves,
 * player can do. <font color="red" ><b>DO NOT</b></font> use object of this class until you call method
 * new_game() or load_game(String filename).<br>
 * There are seven working stacks, IDs from 0 to 6,<br>
 * four color stacks, IDs from 0 to 3,<br>
 * one visible deck and one hidden deck. <br>
 * Object of Board also holds history of moves and current score.
 * @author Matejka Jiri (xmatej52)
 */
class  Board {
private:
    /// @var Array of working stacks.
    Working_stack      working_stacks[7];

    /// @var Array of color stacks.
    Single_color_stack color_stacks[4];

    /// @var Deck of visible cards.
    Card_deck_visible  visible_deck;

    /// @var Deck of hidden cards.
    Card_deck_hidden   hidden_deck;

    /// @var History of moves
    History history;

    /// @var If user asks for possible move, this variable tells if we shoud generate new vector.
    bool generate = true;

    /// @var Vector of possible moves.
    History possible_moves;

    /// @var Score of game.
    size_t score = 0;

    /**
     * Generates all possible moves and adds it into vector.
     */
    void generate_moves();

    /**
     * Removes all cards from table and set score to 0.
     */
    void clear() {
        for (int i = 0; i < 7; i++) {
            working_stacks[i].clear();
        }
        for (int i = 0; i < 4; i++) {
            color_stacks[i].clear();
        }
        hidden_deck.clear();
        visible_deck.clear();
        history.clear();
        possible_moves.clear();
        score = 0;
        generate = true;
    }

public:
    /**
     * Constructs new game with no cards on table.
     */
    Board() {}

    /**
    * Creates new game. If there was previous game, all cards will be removed,
    * and new cards will be dealt.
    */
    void new_game();

    /**
     * Loads previous saved game from file.
     * @param  filename File where game is stored.
     * @return True of game was loaded, false on error.
     */
    bool load_game(std::string filename);

    /**
     * Save current progress of game into file.
     * @param  filename Name of file, where game will be stored
     * @return          True if game was saved, false on error.
     */
    bool save_game(std::string filename);

    /**
     * Checks player won the game.
     * @return true when player won.
     */
    bool is_victory();

    /**
     * Moves card(s) between two working packs. Moves all cards until specific
     * card is reached. When false was returned, no changes were made.
     * @param  from From wich pack cards will be taken.
     * @param  to   To which pack cards will be added.
     * @param  card Specific card used as a guard.
     * @return      True on succes, False on invalid operation.
     */
    bool fromW_toW(unsigned from, unsigned to, Card card);

    /**
     * Moves card between two color packs. Only ace can be moved. When false is
     * returned, no changes were made.
     * @param  from From which pack card will be taken.
     * @param  to   To which pack card will be added.
     * @return      True on succes, False on invalid operation.
     */
    bool fromC_toC(unsigned from, unsigned to);

    /**
     * Moves card from Working pack to Color pack. When false is returned, no
     * changes were made.
     * @param  from From which pack card will be taken.
     * @param  to   To which pack card will be added.
     * @return      True on succes, false on invalid operation.
     */
    bool fromW_toC(unsigned from, unsigned to);

    /**
     * Moves card from color pack to working pack. When false is returned, no
     * changes were made.
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
     * Represents click on hidden deck. Removes one card from it and adds it to
     * visible deck. If hidden deck is empty, takes all cards from visible deck
     * and moves them to hidden deck.
     */
    void fromH_toV();

    /**
     * Undo operation. Can be used multipe times. If game is loaded, undo cannot
     * be done to states of game that was before saving.
     */
    Move undo();

    /**
     * Returns one of possible moves. If no move is possible, invalid move is
     * returned (type fo move is INV). Only moves between 2 working stacks,
     * working stack and color stack, visible deck and color stack can be returned.
     * @return One of possible moves.
     */
    Move help();

    /**
     * Overload output stream operator.
     */
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

    /**
     * Retrieve card from hidden deck.
     * @param  idx Index of card in deck.
     * @return     Card from index on succes, otherwise returns invalid card
     *             (Color is set to ERR).
     */
     Card get_hidden_deck(int idx) {
        return hidden_deck.get(idx);
    }

    /**
     * Retrieve card from visible deck.
     * @param  idx Index of card in deck.
     * @return     Card from index on succes, otherwise returns invalid card
     *             (Color is set to ERR).
     */
    Card get_visible_deck(int idx) {
        return visible_deck.get(idx);
    }

    /**
     * Retrieve score of game.
     * @return value of scor.
     */
    int get_score() {
        return score;
    }
};
#endif
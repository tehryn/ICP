#ifndef BOARD
#define BOARD
#include "Card.hpp"
#include "Card_stack.hpp"
#include "Single_color_stack.hpp"
#include "Working_stack.hpp"
#include "Card_deck_hidden.hpp"
#include "Card_deck_visible.hpp"
#include <string>
#include <fstream>
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
    /**
     * Removes all cards from board and creates new game.
     */
    void new_game();
    bool load_game(std::string filename) {
        std::fstream in(filename, std::fstream::in);
        if (in.is_open()) {
            in >> this;
            if (!in.fail()) {
                in.close();
                return true;
            }
            else {
                in.close();
                return false;
            }
        }
        else {
            return false;
        }
    }

    bool save_game(std::string filename) {
        std::ofstream out(filename, std::ofstream::out);
        if (out.is_open()) {
            out << (*this);
            out.close();
            return true;
        }
        else {
            return false;
        }
    }

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

    friend std::ostream& operator << (std::ostream& stream, Board board) {
        for (unsigned i = 0; i < 7 ; i++) {
            stream << board.working_stacks[i] << "\n";
        }
        for (unsigned i = 0; i < 4 ; i++) {
            stream << board.color_stacks[i] << "\n";
        }
        stream << board.hidden_deck   << "\n";
        stream << board.visible_deck << "\n";
        stream << board.score        << "\n";
        return stream;
    }

private:
    friend std::istream& operator >> (std::istream& stream, Board *board) {
        std::string line;
        int lines = 0;
        size_t size;
        while (!stream.eof()) {
            getline(stream, line);
            if (lines < 13) {
                size = line.size();
                std::string tmp = "";
                int value = 0;
                Card card;
                char c = 'E';
                for(unsigned i = 0; i < size; i++) {
                    if (line[i] == '\n') {
                        break;
                    }
                    else if (line[i] == '(') {
                        value = stoi(tmp);
                    }
                    else if (line[i] == ')') {
                        tmp = "";
                        if (c == 'C') {
                            card = Card(value, CLUBS);
                        }
                        else if (c == 'D') {
                            card = Card(value, DIAMONDS);
                        } else if (c == 'H') {
                            card = Card(value, HEARTS);
                        } else if (c == 'S') {
                            card = Card(value, SPADES);
                        }
                        else {
                             stream.setstate(std::ios::failbit);
                             return stream;
                        }
                        i++;
                        if (line[i] == 'T') {
                            card.make_visible();
                        }
                        switch(lines) {
                            /*from 0 to 6 - reading working_stacks*/
                            case 0:
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                            case 5:
                            case 6:
                                board->working_stacks[lines].force_push(card);
                                break;
                            /* from 7 to 10 - reading color_stacks*/
                            case 7:
                            case 8:
                            case 9:
                            case 10:
                                board->color_stacks[lines-7].force_push(card);
                                break;
                            /* reading hidden_deck */
                            case 11:
                                board->hidden_deck.force_push(card);
                                break;
                            /* reading visible_deck */
                            case 12:
                                board->visible_deck.force_push(card);
                        }
                    }
                    else {
                        tmp += line[i];
                        c    = line[i];
                    }
                }
            }
            else {
                board->score = stoi(line);
                return stream;
            }
            lines++;
        }
        stream.setstate(std::ios::failbit);
        return stream;
    }
};
#endif
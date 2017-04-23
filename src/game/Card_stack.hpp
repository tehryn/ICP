/** @file
 *  Header file for class Card_stack.
 *  @author Matejka Jiri (xmatej52)
 */
#ifndef CARD_STACK
#define CARD_STACK
#include <iostream>
#include <vector>
#include <string>
#include "Card.hpp"
#include <ctime>

/**
 * Base class of Card_deck_visible, Card_deck_hidden, Working_stack and
 * Single_color_stack. Used as very advanced stack of cards.
 * @author Matejka Jiri (xmatej52)
 */
class Card_stack {
protected:
    /// @var Vector of cards in class.
    std::vector<Card> stack;
public:
    /**
     * Constructor of class
     * @return New Card stack with no cards.
     */
    Card_stack() {}

    /**
     * Retrieve size of card stack. (Number of cards in stack)
     * @return Size of card stack.
     */
    size_t size() {
        return this->stack.size();
    }

    /**
     * Pushes card on top of stack, regardless of the cards in stack.
     * @param card Card that will be pushed.
     */
    void force_push(Card card) {
        this->stack.push_back(card);
    }

    /**
     * Inserts card on bottom of stack, regardless of the cards in stack.
     * @param card Card that will be inserted.
     */
    void insert_bottom(Card card) {
        if (this->stack.size() > 0) {
            this->stack.insert(this->stack.begin(), card);
        }
        else {
            this->stack.push_back(card);
        }
    }

    /**
     * Pops card on top of stack.
     * @return Popped card.
     */
    Card pop() {
        Card card = top();
        if (!card.is_error_card()) {
            this->stack.pop_back();
        }
        return card;
    }

    /**
     * Pops card from top of stack.
     * @return Popped card
     */
    Card pop_bottom() {
        Card card = bottom();
        if (!card.is_error_card()) {
            this->stack.erase(this->stack.begin());
        }
        return card;
    }

    /**
     * Retrieve card from top of stack.
     * @return Card from top, if stack is empty, invalid card is returned
     *         (Card of color ERR).
     */
    Card top() {
        if (this->stack.size()) {
            return this->stack.back();
        }
        else {
            return Card(0, ERR);
        }
    }

    /**
     * Retrieve card from bottom of stack.
     * @return Card from bottom, if stack is empty, invalid card is returned
     *         (Card of color ERR).
     */
    Card bottom() {
        if (this->stack.size()) {
            return this->stack.front();
        }
        else {
            return Card(0, ERR);
        }
    }

    /**
     * Makes card on top of the stack visible.
     */
    void set_top_visible() {
        if (this->stack.size() > 0) {
            this->stack.back().make_visible();
        }
    }

    /**
     * Makes card on top of the stack hidden.
     */
    void set_top_hidden() {
        if (this->stack.size() > 0) {
            this->stack.back().make_hidden();
        }
    }

    /**
     * Retrieve card from specific index,
     * @param  idx Index of card.
     * @return     In case on succes, card is returned, otherwise card with color
     *             of ERR is returned.
     */
    Card get(unsigned idx) {
        if (idx < this->size()) {
            return this->stack[idx];
        }
        else {
            return Card(0, ERR);
        }
    }

    /**
     * Converts Stack into string.
     * @return String representing stack.
     */
    std::string to_string() {
        std::string str = "";
        for (unsigned i = 0; i < size(); i++) {
            str += get(i).to_string();
        }
        return str;
    }

    /**
     * Overloads operator for output streams.
     */
    friend std::ostream& operator << (std::ostream& stream, Card_stack stack) {
        for (unsigned i = 0; i < stack.size(); i++) {
            stream << stack.get(i);
        }
        return stream;
    }

    /**
     * Removes all cards from stack.
     */
    void clear() {
        this->stack.clear();
    }

    /**
     * Pops random card from stack.
     * @return Random card.
     */
    Card pop_random();

    /**
     * Creates new stack of 52 cards.
     * @return New stack of cards.
     */
    static Card_stack new_deck();
};
#endif
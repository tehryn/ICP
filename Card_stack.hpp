#ifndef CARD_STACK
#define CARD_STACK
#include <iostream>
#include <vector>
#include "Card.hpp"
#include <ctime>

class Card_stack {
protected:
    std::vector<Card> stack;
public:
    Card_stack() {}
    size_t size() {return this->stack.size();}
    void force_push(Card card) {this->stack.push_back(card);}
    virtual Card pop() {
        Card card = this->stack.back();
        this->stack.pop_back();
        return card;
    }
    Card last() {
        if (this->stack.size()) return this->stack.back();
        else return Card(0, ERR);
    }
    Card pop_random();
    static Card_stack new_deck();
};
#endif
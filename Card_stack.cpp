#ifndef CARD_STACK
#define CARD_STACK
#include <iostream>
#include <vector>
#include "Card.cpp"

using namespace std;

class Card_stack {
protected:
    vector<Card> stack;
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
        else return Card(-1, ERR);
    }
    Card pop_random();
    static Card_stack new_deck();
};

Card_stack Card_stack::new_deck() {
    Card_stack deck;
    for (int i = 1; i <= 13; i++) {
        deck.force_push(Card(i, DIAMONDS));
        deck.force_push(Card(i, SPADES));
        deck.force_push(Card(i, HEARTS));
        deck.force_push(Card(i, CLUBS));
    }
    return deck;
}

Card Card_stack::pop_random() {
    if (this->stack.size() > 0) {
        int idx;
        if (this->stack.size() == 1) idx = 0;
        else idx = rand()%(this->stack.size() - 1);
        Card out = this->stack[idx];
        this->stack.erase(this->stack.begin() + idx);
        return out;
    }
    else {
        return Card(-1, ERR);
    }
}
#endif
#include <iostream>
#include <vector>
#include "Card.cpp"

using namespace std;

class Card_stack {
protected:
    vector<Card> stack;
public:
    Card_stack() {}
    Card pop() {
        Card card = this->stack.back();
        this->stack.pop_back();
        return card;
    }
    void push(Card card) {this->stack.push_back(card);}
    static Card_stack new_deck();
};

Card_stack Card_stack::new_deck() {
    Card_stack deck;
    for (int i = 1; i <= 13; i++) {
        deck.push(Card(i, DIAMONDS));
        deck.push(Card(i, SPADES));
        deck.push(Card(i, HEARTS));
        deck.push(Card(i, CLUBS));
    }
    return deck;
}
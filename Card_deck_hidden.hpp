#ifndef CARD_DECK_HIDDEN
#define CARD_DECK_HIDDEN
#include "Card.hpp"
#include "Card_stack.hpp"
#include "Card_deck_visible.hpp"

class Card_deck_hidden: public Card_stack {
public:
    void push(Card_deck_visible deck) {
        force_push(deck.pop());
    }
};
#endif
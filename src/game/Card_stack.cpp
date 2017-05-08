/*
 * Author: Matejka Jiri
 * login:  xmatej52
 * school: VUT FIT
 * date:   22. 4. 2017
 */
#include "Card_stack.hpp"

Card_stack Card_stack::new_deck() {
    Card_stack deck;
    // creates all cards...
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
        srand(time(NULL));
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
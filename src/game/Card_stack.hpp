#ifndef CARD_STACK
#define CARD_STACK
#include <iostream>
#include <vector>
#include <string>
#include "Card.hpp"
#include <ctime>

class Card_stack {
protected:
    std::vector<Card> stack;
public:
    Card_stack() {}

    size_t size() {
        return this->stack.size();
    }

    void force_push(Card card) {
        this->stack.push_back(card);
    }

    void insert_bottom(Card card) {
        if (this->stack.size() > 0) {
            this->stack.insert(this->stack.begin(), card);
        }
        else {
            this->stack.push_back(card);
        }
    }

    Card pop() {
        Card card = top();
        if (!card.is_error_card()) {
            this->stack.pop_back();
        }
        return card;
    }

    Card pop_bottom() {
        Card card = bottom();
        if (!card.is_error_card()) {
            this->stack.erase(this->stack.begin());
        }
        return card;
    }

    Card top() {
        if (this->stack.size()) {
            return this->stack.back();
        }
        else {
            return Card(0, ERR);
        }
    }

    Card bottom() {
        if (this->stack.size()) {
            return this->stack.front();
        }
        else {
            return Card(0, ERR);
        }
    }

    void set_top_visible() {
        if (this->stack.size() > 0) {
            this->stack.back().make_visible();
        }
    }
    
    void set_top_hidden() {
        if (this->stack.size() > 0) {
            this->stack.back().make_hidden();
        }
    }

    Card get(unsigned idx) {
        if (idx < this->size()) {
            return this->stack[idx];
        }
        else {
            return Card(0, ERR);
        }
    }

    std::string to_string() {
        std::string str = "";
        for (unsigned i = 0; i < size(); i++) {
            str += get(i).to_string();
        }
        return str;
    }

    friend std::ostream& operator << (std::ostream& stream, Card_stack stack) {
        for (unsigned i = 0; i < stack.size(); i++) {
            stream << stack.get(i);
        }
        return stream;
    }

    void clear() {
        this->stack.clear();
    }

    Card pop_random();
    static Card_stack new_deck();
};
#endif
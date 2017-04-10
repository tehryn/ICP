#ifndef SINGLE_COLOR_STACK
#define SINGLE_COLOR_STACK
#include "Card.hpp"
#include "Card_stack.hpp"
class Single_color_stack: public Card_stack {
protected:
    int color = ERR;
public:
    Single_color_stack(int color) {this->color = color;}
    int get_color() {return this->color;}
    bool push(Card card);
};
#endif
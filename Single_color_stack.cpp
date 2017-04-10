#ifndef SINGLE_COLOR_STACK
#define SINGLE_COLOR_STACK
#include "Card.cpp"
#include "Card_stack.cpp"
using namespace std;
class Single_color_stack: Card_stack {
protected:
    int color = ERR;
public:
    Single_color_stack(int color) {this->color = color;}
    int get_color() {return this->color;}
    bool push(Card card);
};

bool Single_color_stack::push(Card card) {
    if (card.get_color() == this->color && card.get_value() == (1 + this->last().get_value())) {
        this->force_push(card);
        return false;
    }
    else {
        return false;
    }
}
#endif
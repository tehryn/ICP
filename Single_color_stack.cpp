#include "Single_color_stack.hpp"

bool Single_color_stack::push(Card card) {
    if (card.get_color() == this->color && card.get_value() == (1 + this->top().get_value())) {
        this->force_push(card);
        return true;
    }
    else {
        return false;
    }
}
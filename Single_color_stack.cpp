#include "Single_color_stack.hpp"

bool Single_color_stack::push(Card card) {
    if (this->size() == 0) {
        if (card.get_value() != 1) {
            return false;
        }
        else {
            this->color = card.get_color();
            this->force_push(card);
            return true;
        }
    }
    if (card.get_color() == this->color && card.get_value() == (1 + this->top().get_value())) {
        this->force_push(card);
        return true;
    }
    else {
        return false;
    }
}
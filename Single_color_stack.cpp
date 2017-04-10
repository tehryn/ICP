#include "Single_color_stack.hpp"

bool Single_color_stack::push(Card card) {
    std::cout << card << "==" << (1 + this->last().get_value()) << "(" << this->color << ")" << std::endl;
    if (card.get_color() == this->color && card.get_value() == (1 + this->last().get_value())) {
        this->force_push(card);
        return true;
    }
    else {
        return false;
    }
}
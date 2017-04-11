#include "Working_stack.hpp"

bool Working_stack::push(Card card) {
    if (this->size() == 0 && card.get_value() == 13) {
        force_push(card);
        return true;
    }

    if ((this->top().get_value() - 1) == card.get_value() && !card.is_similar(this->top())) {
        force_push(card);
        return true;
    }
    else {
        return false;
    }
}

bool Working_stack::push(Working_stack stack) {
    Card card = stack.bottom();
    if ((((this->top().get_value() - 1) == card.get_value()) && !card.is_similar(this->top()))
         || (this->size() == 0 && (card.get_value() == 13))) {
        int size = stack.size();
        for (int i = 0; i < size; i++) {
            force_push(stack.pop_bottom());
        }
        return true;
    }
    else {
        return false;
    }
}

Working_stack Working_stack::pop_until(Card card) {
    int i = -1;
    for(i = this->size() - 1; i >= 0; i--) {
            if (card == this->stack[i] && this->stack[i].is_visible()) {
                break;
            }
    }
    if (i < 0 || !this->stack[i].is_visible()) {
        Working_stack empty;
        return empty;
    }
    Card compare_to = this->top();
    Working_stack new_stack;
    while (!(card == compare_to)) {
        compare_to = pop();
        new_stack.insert_bottom(compare_to);
    }
    return new_stack;
}
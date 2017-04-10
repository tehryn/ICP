#include "Working_stack.hpp"

bool Working_stack::push(Card card) {
    if ((this->top().get_value() - 1) == card.get_value() and card.is_similar(this->top())) {
        force_push(card);
        return true;
    }
    else {
        return false;
    }
}

bool Working_stack::push(Working_stack stack) {
    Card card = stack.bottom();
    if ((this->top().get_value() - 1) == card.get_value() and card.is_similar(this->top())) {
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
    Card compare_to = this->top();
    Working_stack new_stack;
    while (~(card == compare_to)) {
        compare_to = pop();
        new_stack.insert_bottom(compare_to);
    }
    return new_stack;
}
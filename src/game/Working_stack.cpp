/*
 * Author: Matejka Jiri
 * login:  xmatej52
 * school: VUT FIT
 * date:   23. 4. 2017
 */
#include "Working_stack.hpp"

bool Working_stack::push(Card card) {
    if (card.is_error_card() || !card.is_visible()) { // only visible cards can be pushed
        return false;
    }
    if (this->size() == 0 && card.get_value() == 13) { // only king can be pushed on empty stack
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
    Working_stack err_stack = Working_stack();
    if (!card.is_visible()) { // only visible cards are allowed
        return err_stack;
    }
    Card popped = this->pop();
    Card on_top = this->top();
    Working_stack new_stack = Working_stack();
    new_stack.force_push(popped);
    while (!popped.is_similar(on_top) && !(popped == card) && popped.is_visible() && !on_top.is_error_card()) {
        popped = this->pop();
        on_top = this->top();
        new_stack.insert_bottom(popped);
    }
    if (popped == card) { // succes
        return new_stack;
    }
    else {
        // push cards back
        for (unsigned i = 0; i < new_stack.size(); i++) {
            force_push(new_stack.pop_bottom());
        }
        return err_stack;
    }
}
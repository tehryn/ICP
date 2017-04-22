#ifndef WORKING_STACK
#define WORKING_STACK
#include "Card.hpp"
#include "Card_stack.hpp"

class Working_stack: public Card_stack {
public:
    bool push(Card card);
    bool push(Working_stack stack);
    Working_stack pop_until(Card card);
};
#endif
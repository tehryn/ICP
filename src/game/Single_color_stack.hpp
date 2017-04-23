/*
 * Author: Matejka Jiri
 * login:  xmatej52
 * school: VUT FIT
 * date:   23. 4. 2017
 */
#ifndef SINGLE_COLOR_STACK
#define SINGLE_COLOR_STACK
#include "Card.hpp"
#include "Card_stack.hpp"

/**
 * Class representing stack of color cards with same color.
 * @author Matejka Jiri (xmatej52)
 */
class Single_color_stack: public Card_stack {
protected:
    /// @var color of this stack. Color will be changed by pushing Ace into stack.
    int color = ERR;
public:

    /**
     * Retrieve color of this stack.
     * @return Color of stack.
     */
    int get_color() {return this->color;}

    /**
     * Pushes card into stack.
     * @return True on succes, false on invalid operation.
     */
    bool push(Card card);
};
#endif
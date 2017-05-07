/** @file
 *  Header file for class Working_stack.
 *  @author Matejka Jiri (xmatej52)
 */
#ifndef WORKING_STACK
#define WORKING_STACK
#include "Card.hpp"
#include "Card_stack.hpp"

/**
 * @brief Class representing stack of card with multiple colors.
 * Class representing stack of card with multiple colors.
 * @author Matejka Jiri (xmatej52)
 */
class Working_stack: public Card_stack {
public:

    /**
     * Pushes card into stack.
     * @param  card Card that will be pushed.
     * @return      True on succes, false on invalid operation.
     */
    bool push(Card card);

    /**
     * Pushes stack of cards into stack.
     * @param  stack Stack of cards tha will be pushed.
     * @return       True on succes, false on invalid operation.
     */
    bool push(Working_stack stack);

    /**
     * Pops all card until given card is reached.
     * @param  card Card that will be used as guard
     * @return      All cards including given card as stack, when given card
     *              is not in stack or is not visible, empty stack is returned.
     */
    Working_stack pop_until(Card card);
};
#endif
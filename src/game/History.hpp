#ifndef HISTORY
#define HISTORY
#include <vector>
#include "Move.hpp"

/**
 * Class that holds history of moves.
 */
class History {
protected:
    std::vector<Move> stack;
public:
    History() {}

    /**
     * Adds new move into history.
     * @param m Move that will be added.
     */
    void push(Move m) {
        this->stack.push_back(m);
    }

    /**
     * Retrieve move on tom of stack.
     * @return Invalid move when stack is empty, otherwise move on top of stack.
     */
    Move top() {
        if (this->stack.size()) {
            return this->stack.back();
        }
        else {
            return Move::err();
        }
    }

    /**
     * Removes one move from history.
     * @return Removed move on succes, otherwise return move representing
     *         error.
     */
    Move pop() {
        Move move = top();
        if (!move.is_move_invalid()) {
            this->stack.pop_back();
        }
        return move;
    }
};
#endif
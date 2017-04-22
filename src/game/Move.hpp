#ifndef MOVE
#define MOVE

/**
 * Enum that holds movement identifiers.
 */
enum {
    INV = 0, WW, CC, WC, CW, VW, VC, H
};

/**
 * Class representing moves. There are 8 possible moves:
 * WW  - Move between two working stacks.<br>
 * CC  - Move between two color stacks.<br>
 * WC  - Move between working stack(from) and color stack(to).<br>
 * CW  - Move between color stack(from) amd working stack(to).<br>
 * VW  - Move between visible deck and working stack.<br>
 * VC  - Move between visible deck and color stack.<br>
 * H   - Move representing click on hidden deck. <br>
 * INV - Invalid move.
 */
class Move {
protected:
    int from;
    int to;
    int card_count;
    int type;
    bool card_turned;
public:
    /**
     * Creates new move.
     * @param  type        Type of move.
     * @param  from        From which stack/deck card(s) was taken.
     * @param  to          To which stack/deck card(s) was added.
     * @param  card_count  Number of cards that was moved.
     * @param  card_turned Tells if card was turned on top of stack after move.
     */
    Move(int type, int from, int to, int card_count, bool card_turned) {
        this->type        = type;
        this->to          = to;
        this->from        = from;
        this->card_count  = card_count;
        this->card_turned = card_turned;
    }

    /**
     * Creates invalid move.
     * @return Invalid move.
     */
    static Move err() {
        return Move(INV, 0,0,0, false);
    }

    /**
     * Retrieve type of movement.
     * @return Type of movement.
     */
    int get_type() {
        return this->type;
    }

    /**
     * Retrieve ID of stack where cards was added.
     * @return ID of stack.
     */
    int get_to() {
        return this->to;
    }

    /**
     * Retrieve ID of stack from where cards was taken.
     * @return ID of stack
     */
    int get_from() {
        return this->from;
    }

    /**
     * Retrieve count of cards that were moved.
     * @return Number of cards that were moved.
     */
    int get_count() {
        return this->card_count;
    }

    /**
     * Tells if card was turned after this move.
     * @return True if card was turned, otherwise false.
     */
    bool was_turned() {
        return this->card_turned;
    }
    
    /**
     * Checks if move is invalid (type of move is INV)
     * @return true if move is invalid.
     */
    bool is_move_invalid() {
        return type == INV;
    }
};
#endif
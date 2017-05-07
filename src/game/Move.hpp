/** @file
 *  Header file for class Move.
 *  @author Matejka Jiri (xmatej52)
 */
#ifndef MOVE
#define MOVE
#include <iostream>
#include "Card.hpp"
/**
 * Enum that holds movement identifiers.
 */
enum {
    INV = 0, WW, CC, WC, CW, VW, VC, H
};

/**
 * @brief Class representing moves.
 * 
 * Class representing moves. There are 8 possible moves:
 * WW  - Move between two working stacks.<br>
 * CC  - Move between two color stacks.<br>
 * WC  - Move between working stack(from) and color stack(to).<br>
 * CW  - Move between color stack(from) amd working stack(to).<br>
 * VW  - Move between visible deck and working stack.<br>
 * VC  - Move between visible deck and color stack.<br>
 * H   - Move representing click on hidden deck. <br>
 * INV - Invalid move.
 * @author Matejka Jiri (xmatej52)
 */
class Move {
protected:
    /// @var Id of stack from where card was taken.
    int from;

    /// @var Id of stack where card was added.
    int to;

    /// @var Card that was moved.
    Card card;

    /// @var Type of move.
    int type;

    /// @var Holds information if card on top of stack was turned after move.
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
    Move(int type, int from, int to, Card card, bool card_turned) {
        this->type        = type;
        this->to          = to;
        this->from        = from;
        this->card        = card;
        this->card_turned = card_turned;
    }

    /**
     * Creates invalid move.
     * @return Invalid move.
     */
    static Move err() {
        return Move(INV, 0,0,Card(0, ERR), false);
    }

    /**
     * Retrieve type of movement.
     * @return Type of movement.
     */
    int get_type() const {
        return this->type;
    }

    /**
     * Retrieve ID of stack where cards was added.
     * @return ID of stack.
     */
    int get_to() const {
        return this->to;
    }

    /**
     * Retrieve ID of stack from where cards was taken.
     * @return ID of stack
     */
    int get_from() const {
        return this->from;
    }

    /**
     * Retrieve card that was moved.
     * @return Number of cards that were moved.
     */
    Card get_card() const {
        return this->card;
    }

    /**
     * Tells if card was turned after this move.
     * @return True if card was turned, otherwise false.
     */
    bool was_turned() const {
        return this->card_turned;
    }

    /**
     * Checks if move is invalid (type of move is INV)
     * @return true if move is invalid.
     */
    bool is_move_invalid() const {
        return type == INV;
    }

    friend std::ostream& operator << (std::ostream& stream, const Move move) {
        switch(move.get_type()) {
            case WW:
                stream << "working " << move.from << " working " << move.to << ' ' << Card::to_string(move.card);
                break;
            case WC:
                stream << "working " << move.from << " color " << move.to;
                break;
            case CW:
                stream << "color " << move.from << " working " << move.to;
                break;
            case CC:
                stream << "color " << move.from << " color " << move.to;
                break;
            case VW:
                stream << "visible working " << move.to;
                break;
            case VC:
                stream << "visible color " << move.to;
                break;
            case  H:
                stream << "hidden";
                break;
            default: return stream;
        }
        stream << std::endl;
        return stream;
    }
};
#endif
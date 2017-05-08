/** @file
 *  Header file for class G_Stack.
 *  @author Misova Miroslava (xmisov00), Matejka Jiri (xmatej52)
 */
#ifndef G_STACK_H
#define G_STACK_H

#include <QWidget>
#include <QMouseEvent>
#include <vector>

#include "../gui/globals.hpp"

class G_Board;

/**
 * @brief Class representing graphical view of stack of cards.
 *
 * @author Misova Miroslava (xmisov00)
 */
class G_Stack : public QWidget
{
    Q_OBJECT

private:
    /// Vector of graphical cards
    std::vector<G_Card*> stack;
    /// Y axis shift down
    uint positionY = 0;
    /// Pointer to Board, because of calling Board functions
    G_Board * board = nullptr;
    /// Type of this stack
    Stacks type = ErrStack;
    /// Index of this stack in array of stacks
    int id = 0;

    /**
     * Finds card in vector by Y position in stack.
     * @param  y Y position
     * @return   Graphical card
     */
    G_Card* find_card(uint y);

    /**
     * Calls Border's funkction 'process_command'
     */
    void process_command();

public:
    /**
     * Constructor.
     */
    explicit G_Stack(QWidget *parent = 0);

    /**
     * Sets Y axis shift down
     * @param positionY Axis shift
     */
    void set_positionY(uint positionY);

    /**
     * Sets Board pointer.
     * @param board Pointer to Board
     */
    void set_board(G_Board* board);

    /**
     * Sets index of stack in stacks.
     * @param id Index
     */
    void set_id(int id);

    /**
     * Sets type of this stack.
     * @param type Type
     */
    void set_type(Stacks type);

    /**
     * Sets border around card.
     * @param style Style
     * @param gcard Graphical card
     */
    void set_border(const char * style, G_Card * gcard);

    /**
     * Sets border around card.
     * @param style Style
     * @param card  Logic card
     */
    void set_border(const char * style, Card card);

    /**
     * Makes string from type and index of this stack.
     * @param  type Type
     * @param  id   Index
     * @return      string indentifier
     */
    std::string stack_identifier_to_str(Stacks type, int id) const;

    /**
     * Returns how many cards are in stack. Be prepaired, that empty stack contains one error-card.
     * @return Size
     */
    int size();

    /**
     * Returns card on the top of the stack and doesn't remove it.
     * @return Graphical card.
     */
    G_Card* top();

    /**
     * Push one card on top of this stack.
     * @param card Card to push
     */
    void push(Card card);

    /**
     * Remove top card of this stack and return.
     * @return Removed card
     */
    G_Card* pop();

    /**
     * Finds and returns a card on index.
     * @param  index Index in the stack
     * @return       Graphical card
     */
    G_Card* get(int index);

    /**
     * Clear the stack.
     */
    void clean();

protected:
    /**
     * Player clicked on stack.
     */
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // G_STACK_H

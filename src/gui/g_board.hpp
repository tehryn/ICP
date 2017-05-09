/** @file
 *  Header file for class G_Board.
 *  @author Misova Miroslava (xmisov00), Matejka Jiri (xmatej52)
 */
#ifndef G_BOARD_HPP
#define G_BOARD_HPP

#include <QWidget>
#include <QLayout>
#include <QLabel>

#include "../game/Board.hpp"
#include "../gui/globals.hpp"
#include "../gui/g_card.hpp"
#include "../gui/g_stack.hpp"
#include "../game/Move.hpp"
#include "../game/Card.hpp"


constexpr int GAME_WIDTH = 9 * CARD_WIDTH; ///< Variable representing width of one game board

constexpr int GAME_HEIGHT = 6 * CARD_HEIGHT; ///< Variable representing height of one game board

/**
 * @brief Class representing graphical view of table with cards.
 *
 * @author Misova Miroslava (xmisov00)
 */
class G_Board : public QWidget
{
    Q_OBJECT
private:
    
    Board game; ///< Game logic
    
    QVBoxLayout * card_board_layout; ///< Layout for whole game

    QWidget top_panel; ///< Top part of game
    QWidget bottom_panel; ///< Botton part of game

    QHBoxLayout * top_panel_layout; ///< Layout for top part of game
    QHBoxLayout * bottom_panel_layout; ///< Layout for bottom part of game

    QWidget left_panel; ///< Left part of top panel
    QWidget right_panel; ///< Right part of top panel

    
    QHBoxLayout * left_panel_layout; ///< Layout for left part of top panel
    QHBoxLayout * right_panel_layout; ///< Layout for right part of top panel

   
    QLabel score; ///< Graphical representation player's score
    
    std::string str_score; ///< Player's score

   
    G_Stack Card_deck_hidden; ///< Deck of hidden cards
    G_Stack Card_deck_visible; ///< Deck of visible cards
    G_Stack Single_color_stack[4]; ///< Array of color stacks
    G_Stack Working_stack[7]; ///< Array of working stacks

   
    bool proc_move = false; ///< Variable which says if next click will call processing command
    Stacks from_type; ///< Type of the first clicked stack
    Stacks to_type; ///< Type of the second clicked stack
    int from_id; ///< Index of the first clicked stack in array of stacks
    int to_id; ///< Index of the second clicked stack in array of stacks
    G_Card * clicked; ///< Pointer to graphical representation of clicked card

   
    Move hint_move = Move(ERR, 0, 0, Card(0, ERR), false); ///< One hint move
    bool was_hint = false; ///< If player wanted help

    /**
     * Reads all cards' location
     */
    void readCards();

    /**
     * Rebuilds one stack
     * @param type Type of stack
     * @param id   Index of stack in array of stacks
     */
    void rebuild_stack(Stacks type, int id);

public:
    /**
     * Constructs one game. Calls function 'readCards' in it.
     */
    G_Board(QWidget *parent = 0);

    /**
     * Builds a new game.
     */
    void new_game();

    /**
     * Loads a new game.
     * @param  filename File where game is stored
     * @return          True if success, false if not
     */
    bool load_game(std::string filename);

    /**
     * Saves a this game.
     * @param  filename File where game will be stored
     * @return          True if success, false if not
     */
    bool save_game(std::string filename);

    /**
     * Returns a game before the last move.
     */
    void undo();

    /**
     * Show one hint to player.
     */
    void hint();

    /**
     * Hide last hint.
     */
    void unset_hint();

    /// Style for hint move - starting position
    const char * hint_from_border = "border: 2px solid #0000FF";
    /// Style for hint move - final position
    const char * hint_to_border = "border: 2px solid #00FFFF";

    /**
     * Sets variables after situation, that hidden deck was clicked.
     */
    void clicked_hidden();

    /**
     * Sets variables after situation, that visible deck was clicked.
     */
    void clicked_visible();

    /**
     * Sets variables after situation, that colored stack was clicked.
     * @param id Index of clicked stack
     */
    void clicked_color(int id);

    /**
     * Sets variables after situation, that working stack was clicked.
     * @param id    Index of clicked stack
     * @param gcard Card that was clicked
     */
    void clicked_working(int id, G_Card * gcard);

    /**
     * Process one command.
     */
    void process_command();

    /**
     * Destructor.
     */
    ~G_Board();

protected:
    /**
     * Player clicked on board.
     */
    void mousePressEvent(QMouseEvent *event);
};

#endif // G_BOARD_HPP

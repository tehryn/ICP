#ifndef G_BOARD_HPP
#define G_BOARD_HPP

#include <QWidget>
#include <QLayout>
#include <QLabel>

#include "Board.hpp"
#include "globals.hpp"
#include "g_card.hpp"
#include "g_stack.hpp"
#include "Move.hpp"
#include "Card.hpp"
constexpr int GAME_WIDTH = 9 * CARD_WIDTH;
constexpr int GAME_HEIGHT = 6 * CARD_HEIGHT;

class G_Board : public QWidget
{
    Q_OBJECT
private:
    Board game;
    QVBoxLayout * card_board_layout;
    QHBoxLayout * top_panel_layout;
    QHBoxLayout * bottom_panel_layout;

    QWidget top_panel;
    QWidget bottom_panel;

    QHBoxLayout * left_panel_layout;
    QHBoxLayout * right_panel_layout;

    QWidget left_panel;
    QWidget right_panel;

    QLabel score;
    std::string str_score;

    G_Stack Card_deck_hidden;
    G_Stack Card_deck_visible;
    G_Stack Single_color_stack[4];
    G_Stack Working_stack[7];

    bool proc_move = false;
    Stacks to_type;
    Stacks from_type;
    int to_id;
    int from_id;
    G_Card * clicked;
    Move hint_move = Move(ERR, 0, 0, Card(0, ERR), false);
    bool was_hint = false;

    void readCards();
    void rebuild_stack(Stacks type, int id);

public:
    G_Board(QWidget *parent = 0);

    void new_game();
    bool load_game(std::string filename);
    bool save_game(std::string filename);
    void undo();
    void hint();
    void unset_hint();
    const char * hint_from_border = "border: 2px solid #0000FF";
    const char * hint_to_border = "border: 2px solid #00FFFF";

    void clicked_working(int id, G_Card * gcard);

    void clicked_color(int id);

    void clicked_hidden();

    void clicked_visible();

    void process_command();

    ~G_Board();
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // G_BOARD_HPP

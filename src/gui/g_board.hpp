#ifndef G_BOARD_HPP
#define G_BOARD_HPP

#include <QWidget>
#include <QLayout>

#include "Board.hpp"
#include "globals.hpp"
#include "g_card.hpp"
#include "g_stack.hpp"

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

    G_Stack Card_deck_hidden;
    G_Stack Card_deck_visible;
    G_Stack Single_color_stack[4];
    G_Stack Working_stack[7];

    void readCards();
    void rebuild_stack(Stacks type, int id);

public:
    G_Board(QWidget *parent = 0);
    void process_command();
    ~G_Board();
};

#endif // G_BOARD_HPP

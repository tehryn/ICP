/*
 * Author: Misova Miroslava, Matejka Jiri
 * login:  xmisov00, xmatej52
 * school: VUT FIT
 * date:   22. 4. 2017
 */

#include "g_board.hpp"

G_Board::G_Board(QWidget *parent) : QWidget(parent)
{
    // setting styles and layouts
    setWindowTitle(tr("Solitaire"));
    setStyleSheet("background-color: green;");
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);

    card_board_layout = new QVBoxLayout(this);
    setLayout(card_board_layout);

    str_score  = "Score:\n";
    str_score += std::to_string(game.get_score());
    score.setText(str_score.c_str());
    score.setParent(this);
    score.setWordWrap(true);
    score.setFixedHeight(CARD_HEIGHT);

    left_panel_layout = new QHBoxLayout;
    left_panel.setLayout(left_panel_layout);
    left_panel.setFixedWidth(2*CARD_WIDTH + 30);
    left_panel.setFixedHeight(CARD_HEIGHT + 30);

    right_panel_layout = new QHBoxLayout;
    right_panel.setLayout(right_panel_layout);
    right_panel.setFixedWidth(4*CARD_WIDTH + 3*15);
    right_panel.setFixedHeight(CARD_HEIGHT + 30);

    top_panel_layout = new QHBoxLayout;
    top_panel.setLayout(this->top_panel_layout);
    top_panel.setFixedHeight(CARD_HEIGHT + 30);
    card_board_layout->addWidget(&top_panel);

    bottom_panel_layout = new QHBoxLayout;
    bottom_panel.setLayout(this->bottom_panel_layout);
    card_board_layout->addWidget(&bottom_panel);

    // -------------------------------------------------------
    // setting card stacks
    Card_deck_hidden.setParent(this);
    Card_deck_hidden.set_id(0);
    Card_deck_hidden.set_type(Hidden);
    Card_deck_hidden.set_board(this);
    Card_deck_visible.setParent(this);
    Card_deck_visible.set_id(0);
    Card_deck_visible.set_type(Visible);
    Card_deck_visible.set_board(this);

    for (int i = 0; i<4; i++){
        Single_color_stack[i].setParent(this);
        Single_color_stack[i].set_id(i);
        Single_color_stack[i].set_type(Single_Color);
        Single_color_stack[i].set_board(this);
    }

    for (int i = 0; i<7; i++) {
        Working_stack[i].setParent(this);
        Working_stack[i].set_positionY(CARD_HEIGHT*0.25);
        Working_stack[i].set_id(i);
        Working_stack[i].set_type(Working);
        Working_stack[i].set_board(this);
    }

    // ------------------------------------------
    // adding card stacks to the game
    left_panel_layout->addWidget(&Card_deck_hidden);
    left_panel_layout->addWidget(&Card_deck_visible);

    top_panel_layout->addWidget(&left_panel);

    top_panel_layout->addWidget(&score);

    for (int i = 0; i<4; i++)
        right_panel_layout->addWidget(&(Single_color_stack[i]));
    top_panel_layout->addWidget(&right_panel);

    for (int i = 0; i<7; i++)
        bottom_panel_layout->addWidget(&(Working_stack[i]));
    game.new_game();

    // -----------------------------------------
    // loading cards
    readCards();
}

void G_Board::readCards()
{
    Card card;
    unsigned index = 0;
    str_score  = "Score:\n";
    str_score += std::to_string(game.get_score());
    score.setText(str_score.c_str());
    // Card_deck_hidden
    Card_deck_hidden.clean();
    card = game.get_hidden_deck(index);
    do {        // while loaded card is valid, if stack is empty, it would contain one error card
        Card_deck_hidden.push(card);
        index++;
    } while (!(card = game.get_hidden_deck(index)).is_error_card());

    // Card_deck_visible
    Card_deck_visible.clean();
    index = 0;
    card = game.get_visible_deck(index);
    do {
        Card_deck_visible.push(card);
        index++;
    } while (!(card = game.get_visible_deck(index)).is_error_card());

    // Single_color_stack
    for (int i = 0; i<4; i++)
    {
        Single_color_stack[i].clean();
        index = 0;
        card = game.get_color_stack(i, index);
        do {
            Single_color_stack[i].push(card);
            index++;
        } while (!(card = game.get_color_stack(i, index)).is_error_card());
    }

    // Working_stack
    for (int i = 0; i<7; i++)
    {
        index = 0;
        card = game.get_working_stack(i, index);
        Working_stack[i].clean();
        do {
            Working_stack[i].push(card);
            index++;
        } while (!(card = game.get_working_stack(i, index)).is_error_card());
    }
}

void G_Board::process_command()
{
    if (was_hint)
        unset_hint();

    switch (from_type) {
        case Hidden:
            game.fromH_toV();
            rebuild_stack(from_type,0);
            rebuild_stack(Visible, 0);
            break;

        case Visible:
            Card_deck_visible.set_border("border: 0px;", Card_deck_visible.top());
            if (to_type == Single_Color)
            {
                if (!game.fromV_toC(to_id))
                   {}//std::cerr << "Unsuccessful command." << std::endl;
                else
                {
                    rebuild_stack(Visible, 0);
                    rebuild_stack(Single_Color, to_id);
                }
            }
            else if (to_type == Working)
            {
                if (!game.fromV_toW(to_id))
                    {}//std::cerr << "Unsuccessful command." << std::endl;
                else
                {
                    rebuild_stack(Visible, 0);
                    rebuild_stack(Working, to_id);
                }
            }
            else
                {}//std::cerr << "Unknown command." << std::endl;
            break;

        case Single_Color:
            Single_color_stack[from_id].set_border("border: 0px;", Single_color_stack[from_id].top());
            if (to_type == Single_Color)
            {
                if (!game.fromC_toC(from_id, to_id))
                    {}//std::cerr << "Unsuccessful command." << std::endl;
                else
                {
                    rebuild_stack(Single_Color, from_id);
                    rebuild_stack(Single_Color, to_id);
                }
            }
            else if (to_type == Working)
            {
                if (!game.fromC_toW(from_id, to_id))
                    {}//std::cerr << "Unsuccessful command." << std::endl;
                else
                {
                    rebuild_stack(Single_Color, from_id);
                    rebuild_stack(Working, to_id);
                }
            }
            else
                {}//std::cerr << "Unknown command." << std::endl;
            break;

        case Working:
            Working_stack[from_id].set_border("border: 0px;", clicked);
            if (to_type == Single_Color)
            {
                if (!game.fromW_toC(from_id, to_id))
                    {}//std::cerr << "Unsuccessful command." << std::endl;
                else
                {
                    rebuild_stack(Working, from_id);
                    rebuild_stack(Single_Color, to_id);
                }
            }
            else if (to_type == Working)
            {
                if (!game.fromW_toW(from_id, to_id, clicked->card))
                    {}//std::cerr << "Unsuccessful command." << std::endl;
                else
                {
                    rebuild_stack(Working, from_id);
                    rebuild_stack(Working, to_id);
                }
            }
            else
                {}//std::cerr << "Unknown command." << std::endl;
            break;

        default:
            break;
    }
    // writing score to board
    str_score  = "Score:\n";
    str_score += std::to_string(game.get_score());
    if (game.is_victory())
        str_score += "\nVictory";
    score.setText(str_score.c_str());

    proc_move = false;
}

void G_Board::rebuild_stack(Stacks type, int id)
{
    Card card;
    unsigned index = 0;

    switch (type) {
        case Hidden:
            Card_deck_hidden.clean();
            card = game.get_hidden_deck(index);
            do {        // while loaded card is valid, if stack is empty, it would contain one error card
                Card_deck_hidden.push(card);
                index++;
            } while (!(card = game.get_hidden_deck(index)).is_error_card());
            break;

        case Visible:
            Card_deck_visible.clean();
            card = game.get_visible_deck(index);
            do {
                Card_deck_visible.push(card);
                index++;
            } while (!(card = game.get_visible_deck(index)).is_error_card());
            break;

        case Single_Color:
            Single_color_stack[id].clean();
            index = 0;
            card = game.get_color_stack(id, index);
            do {

                Single_color_stack[id].push(card);
                index++;
            } while (!(card = game.get_color_stack(id, index)).is_error_card());
            break;

        case Working:
            Working_stack[id].clean();
            card = game.get_working_stack(id, index);
            do {
                Working_stack[id].push(card);
                index++;
            } while (!(card = game.get_working_stack(id, index)).is_error_card());
            break;

        default:
            break;
    }
}

void G_Board::clicked_hidden()
{
    if (proc_move)
    {
        to_type   = ErrStack;
        process_command();
    }
    else
    {
        from_type = Hidden;
        process_command();
    }
}

void G_Board::clicked_visible()
{
    if (proc_move)
    {
        to_type   = ErrStack;
        process_command();
    }
    else
    {
        if (Card_deck_visible.top()->card.is_error_card())
            return;

        from_type = Visible;
        Card_deck_visible.set_border("Border: 2px solid red;", Card_deck_visible.top());
        proc_move = true;
    }
}


void G_Board::clicked_color(int id)
{
    if (proc_move)
    {
        to_type = Single_Color;
        to_id = id;
        process_command();
    }
    else
    {
        if (Single_color_stack[id].top()->card.is_error_card())
            return;

        from_id = id;
        from_type = Single_Color;
        Single_color_stack[id].set_border("Border: 2px solid red;", Single_color_stack[id].top());
        proc_move = true;
    }
}

void G_Board::clicked_working(int id, G_Card *gcard)
{
    if (proc_move)
    {
        to_id = id;
        to_type = Working;
        process_command();
    }
    else
    {
        if (gcard != nullptr && gcard->card.is_visible())
        {
            from_id = id;
            from_type = Working;
            Working_stack[id].set_border("Border: 2px solid red;", gcard);
            clicked = gcard;
            proc_move = true;
        }
    }
}

void G_Board::new_game()
{
    game.new_game();
    readCards();
}

bool G_Board::save_game(std::string filename)
{
    return game.save_game(filename);
}

bool G_Board::load_game(std::string filename)
{
    bool ret = game.load_game(filename);
    readCards();
    return ret;
}

void G_Board::undo()
{
    game.undo();
    str_score  = "Score:\n";
    str_score += std::to_string(game.get_score());
    readCards();
}

void G_Board::hint()
{
    proc_move = false;
    if (was_hint)
        unset_hint();

    hint_move = game.help();
    switch(hint_move.get_type()) {
        case WW:
            Working_stack[hint_move.get_from()].set_border(hint_from_border, hint_move.get_card());
            Working_stack[hint_move.get_to()].set_border(hint_to_border, Working_stack[hint_move.get_to()].top());
            break;

        case WC:
            Working_stack[hint_move.get_from()].set_border(hint_from_border, hint_move.get_card());
            Single_color_stack[hint_move.get_to()].set_border(hint_to_border, Single_color_stack[hint_move.get_to()].top());
            break;

        case VC:
            Card_deck_visible.set_border(hint_from_border, Card_deck_visible.top());
            Single_color_stack[hint_move.get_to()].set_border(hint_to_border, Single_color_stack[hint_move.get_to()].top());
            break;

        case VW:
            Card_deck_visible.set_border(hint_from_border, Card_deck_visible.top());
            Working_stack[hint_move.get_to()].set_border(hint_to_border, Working_stack[hint_move.get_to()].top());
            break;

        default: break;
    }
    was_hint  = true;
}

void G_Board::unset_hint()
{
    switch(hint_move.get_type()) {
        case WW:
            Working_stack[hint_move.get_from()].set_border("border: none;", hint_move.get_card());
            Working_stack[hint_move.get_to()].set_border("border: none;", Working_stack[hint_move.get_to()].top());
            break;
        case WC:
            Working_stack[hint_move.get_from()].set_border("border: none;", hint_move.get_card());
            Single_color_stack[hint_move.get_to()].set_border("border: none;", Single_color_stack[hint_move.get_to()].top());
            break;
        case VC:
            Card_deck_visible.set_border("border: none;", Card_deck_visible.top());
            Single_color_stack[hint_move.get_to()].set_border("border: none;", Single_color_stack[hint_move.get_to()].top());
            break;
        case VW:
            Card_deck_visible.set_border("border: none;", Card_deck_visible.top());
            Working_stack[hint_move.get_to()].set_border("border: none;", Working_stack[hint_move.get_to()].top());
            break;
        default: break;
    }
    was_hint = false;
}

void G_Board::mousePressEvent(QMouseEvent *event)
{
    if (proc_move)
    {
        to_type = ErrStack;
        process_command();
    }
    else {
        event = (QMouseEvent*) event; // gcc throws warnign.. so lets do nothing
    }
}

G_Board::~G_Board() {}

#include "g_board.hpp"


G_Board::G_Board(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("Solitaire"));
    setStyleSheet("background-color: green");
    setFixedSize((9 * CARD_WIDTH), (6 * CARD_HEIGHT));

    card_board_layout = new QVBoxLayout(this);
    setLayout(card_board_layout);

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
    game.load_game("./saved.txt");
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
        //Single_color_stack[i].show();
    }

    for (int i = 0; i<7; i++) {
        Working_stack[i].setParent(this);
        Working_stack[i].set_positionY(CARD_HEIGHT*0.25);
        Working_stack[i].set_id(i);
        Working_stack[i].set_type(Working);
        Working_stack[i].set_board(this);
        //Working_stack[i].show();
    }

    // ------------------------------------------
    readCards();

    left_panel_layout->addWidget(&Card_deck_hidden);
    left_panel_layout->addWidget(&Card_deck_visible);
    top_panel_layout->addWidget(&left_panel);

    for (int i = 0; i<4; i++)
        right_panel_layout->addWidget(&(Single_color_stack[i]));
    top_panel_layout->addWidget(&right_panel);
    for (int i = 0; i<7; i++)
        bottom_panel_layout->addWidget(&(Working_stack[i]));

}

void G_Board::readCards() {
    Card card;
    unsigned index = 0;

    // Card_deck_hidden
    card = game.get_hidden_deck(index);
    do {        // while loaded card is valid, if stack is empty, it would contain one error card
        Card_deck_hidden.push(card);
        index++;
    } while (!(card = game.get_hidden_deck(index)).is_error_card());

    // Card_deck_visible
    index = 0;
    card = game.get_visible_deck(index);
    do {
        Card_deck_visible.push(card);
        index++;
    } while (!(card = game.get_visible_deck(index)).is_error_card());

    // Single_color_stack
    for (int i = 0; i<4; i++)
    {
        index = 0;
        card = game.get_color_stack(i, index);
        do {
            Single_color_stack[i].push(card);
            index++;
        } while (!(card = game.get_color_stack(i, index)).is_error_card());
    }

    // Working_stack
    for (int i = 0; i<7; i++){
        index = 0;
        card = game.get_working_stack(i, index);
        do {
            Working_stack[i].push(card);
            index++;
        } while (!(card = game.get_working_stack(i, index)).is_error_card());
    }
}

void G_Board::process_command() {
    std::cout << game << "AAAAAA" << std::endl;
    bool paintable = false;
    switch (clicked_stack_01) {
        case Hidden:
            Card_deck_hidden.set_border("border: 0px;", clicked_card);
            if (clicked_stack_02 == Visible) {
                game.fromH_toV();
                std::cout << game << std::endl;
                paintable = true;
            }
            else
                std::cerr << "Unknown command." << std::endl;
            break;

        case Visible:
            Card_deck_visible.set_border("border: 0px;", clicked_card);
            if (clicked_stack_02 == Single_Color) {
                if (!game.fromV_toC(clicked_stack_02_index))
                    std::cerr << "Unsuccessful command." << std::endl;
                else
                    paintable = true;
            }
            else if (clicked_stack_02 == Working) {
                if (!game.fromV_toW(clicked_stack_02_index))
                    std::cerr << "Unsuccessful command." << std::endl;
                else
                    paintable = true;
            }
            else
                std::cerr << "Unknown command." << std::endl;
            break;

        case Single_Color:
            Single_color_stack[clicked_stack_01_index].set_border("border: 0px;", clicked_card);
            std::cout << "BBBBB" << std::endl;
            if (clicked_stack_02 == Single_Color) {
                if (!game.fromC_toC(clicked_stack_01_index,clicked_stack_02_index))
                    std::cerr << "Unsuccessful command." << std::endl;
                else
                    paintable = true;
            }
            else if (clicked_stack_02 == Working) {
                if (!game.fromC_toW(clicked_stack_01_index, clicked_stack_02_index))
                    std::cerr << "Unsuccessful command." << std::endl;
                else
                    paintable = true;
                std::cout << "CCCCCCCCCCCCCC";
            }
            else
                std::cerr << "Unknown command." << std::endl;
            break;

        case Working:
            Working_stack[clicked_stack_01_index].set_border("border: 0px;", clicked_card);
            if (clicked_stack_02 == Single_Color) {
                if (!game.fromW_toC(clicked_stack_01_index,clicked_stack_02_index))
                    std::cerr << "Unsuccessful command." << std::endl;
                else
                    paintable = true;
            }
            else if (clicked_stack_02 == Working) {
                std::cout << this << std::endl;
                if (!game.fromW_toW(clicked_stack_01_index, clicked_stack_02_index, clicked_card->card))
                    std::cerr << "Unsuccessful command." << std::endl;
                else
                    paintable = true;
            }
            else
                std::cerr << "Unknown command." << std::endl;
            break;

        default:
            std::cerr << "Invalid command." << std::endl;
    }

    if (paintable)
    {
        std::cout << "Prekresluji." << std::endl;
        std::cout << game << std::endl;
        this->rebuild_stack(clicked_stack_01, clicked_stack_01_index); //TODO
        this->rebuild_stack(clicked_stack_02, clicked_stack_02_index);

        //this->repaint();
        //this->update();
    }
    else
    {
        std::cout << "Nebudu prekreslovat." << std::endl;
    }
}
void G_Board::rebuild_stack(Stacks type, int id) {
    Card card;
    unsigned index = 0;
    std::cout << "rebuild\n"<<std::endl;
    switch (type) {
        case Hidden:
            Card_deck_hidden.clean();
            card = game.get_hidden_deck(index);
            do {        // while loaded card is valid, if stack is empty, it would contain one error card
                Card_deck_hidden.push(card);
                index++;
            } while (!(card = game.get_hidden_deck(index)).is_error_card());

            //Card_deck_hidden.repaint();
            //Card_deck_hidden.update();
            break;

        case Visible:
            Card_deck_visible.clean();
            card = game.get_visible_deck(index);
            do {
                Card_deck_visible.push(card);
                index++;
            } while (!(card = game.get_visible_deck(index)).is_error_card());

            //Card_deck_visible.repaint();
            //Card_deck_visible.update();
            break;

        case Single_Color:
            Single_color_stack[id].clean();
            index = 0;
            card = game.get_color_stack(id, index);
            do {

                Single_color_stack[id].push(card);
                index++;
            } while (!(card = game.get_color_stack(id, index)).is_error_card());

            //Single_color_stack[id].repaint();
            //Single_color_stack[id].update();
            break;

        case Working:
            std::cout << "repainting: " << id << " as " << clicked_stack_02_index << std::endl;
            Working_stack[id].clean();
            card = game.get_working_stack(id, index);
            do {
                Working_stack[id].push(card);
                index++;
            } while (!(card = game.get_working_stack(id, index)).is_error_card());

            //Working_stack[id].repaint();
            //Working_stack[id].update();
            break;

        default:
            break;
    }
}


G_Board::~G_Board() {}

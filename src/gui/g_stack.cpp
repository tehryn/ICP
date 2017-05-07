#include "g_stack.hpp"
#include "g_board.hpp"

G_Card * clicked_card = nullptr;
Stacks clicked_stack_01 = ErrStack;
int clicked_stack_01_index = -1;

Stacks clicked_stack_02 = ErrStack;
int clicked_stack_02_index = -1;


G_Stack::G_Stack(QWidget *parent) : QWidget(parent) {}

void G_Stack::set_positionY(int positionY) {
    this->positionY = positionY;
}

void G_Stack::set_board(G_Board *board) {
    this->board = board;
}

void G_Stack::set_id(int id) {
    this->id = id;
}

void G_Stack::set_type(Stacks type) {
    this->type = type;
}


int G_Stack::size() {
    return this->stack.size();
}

void G_Stack::push(Card c) {
    if (!c.is_error_card() || stack.size() == 0) {
        G_Card *card = new G_Card(c, this);
        card->setParent(this);
        card->move(0, (this->positionY) * (this->size()));
        card->show();
        this->stack.push_back(card);
        //this->updateGeometry();
        //TODO
    }
}

G_Card* G_Stack::pop() {
    G_Card* card = top();
    if (card != nullptr) {
        this->stack.pop_back();
    }
    return card;
}

G_Card* G_Stack::top() {
    if (this->stack.size())
        return this->stack.back();
    else
        return nullptr;
}

G_Card* G_Stack::get(int index) {
    if (index < this->size())
        return this->stack[index];
    else
        return nullptr;
}

void G_Stack::clean() {
    for(uint i = 0; i < stack.size(); i++) {
        stack[i]->hide();
        delete stack[i];
    }
    this->stack.clear();
    //TODO
}

G_Card* G_Stack::find_card(int y) {
    if (top()->card.is_error_card())
        return nullptr;
    if (positionY == 0)
        return top();
    if ((CARD_HEIGHT + positionY*(stack.size()-1)) < y)
        return nullptr;
    int n = y/positionY;
    if (n > (this->size() - 1))
        n = size() - 1;
    return get(n);
}

std::string G_Stack::stack_identifier_to_str(Stacks type, int id) const {
    std::string str = "";
    switch (type) {
        case Hidden:        str += "H";             break;
        case Visible:       str += "V";             break;
        case Single_Color:  str += "C" + std::to_string(id);  break;
        case Working:       str += "W" + std::to_string(id);  break;
        default:            str += "E";
    }
    return str;
}

void G_Stack::set_border(const char *style, G_Card *gcard) {
    if (gcard == nullptr) return;
    if (this->type == Working)
    {
        bool found = false;
        for (int i = 0; i < stack.size(); i++) {
            if (stack[i]->card.is_visible() && gcard->card == stack[i]->card) {
                found = true;
            }
            if (found) {
                stack[i]->setStyleSheet(style);
            }
        }
    }
    else {
         gcard->setStyleSheet(style);
    }
}

void G_Stack::mousePressEvent(QMouseEvent *event) {
    set_border("border: 0px;", clicked_card);
    G_Card* gcard = find_card(event->pos().y());
    if (clicked_card == nullptr) {
        if (gcard == nullptr)
            return;
        if (this->type == Working && !gcard->card.is_visible())
            return;
        set_border("border: 2px solid red;", gcard);
        clicked_card = gcard;
        clicked_stack_01 = this->type;
        clicked_stack_01_index = this->id;
        std::cout << "Clicked: " << Card::to_string(clicked_card->card)
                  << " Stack: " << this->stack_identifier_to_str(clicked_stack_01, clicked_stack_01_index) << std::endl;
    }
    else
    { 
        clicked_stack_02 = this->type;
        clicked_stack_02_index = this->id;

        std::cout << "Clicked: " << Card::to_string(clicked_card->card)
                  << " Stack: " << this->stack_identifier_to_str(clicked_stack_01, clicked_stack_01_index)
                  << " Stack: " << this->stack_identifier_to_str(this->type, this->id) << std::endl;

        if (!clicked_card->card.is_error_card()) {

            std::cout << "Process command." << std::endl;
            process_command();
        }

        clicked_card = nullptr;
        clicked_stack_01 = ErrStack;
        clicked_stack_01_index = -1;
        clicked_stack_02 = ErrStack;
        clicked_stack_02_index = -1;
    }
}
void G_Stack::process_command() {
    this->board->process_command();
}

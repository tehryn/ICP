#include "g_stack.hpp"
#include "g_board.hpp"

G_Card * clicked_card = nullptr;
Stacks clicked_stack_01 = ErrStack;
int clicked_stack_01_index = -1;

Stacks clicked_stack_02 = ErrStack;
int clicked_stack_02_index = -1;


G_Stack::G_Stack(QWidget *parent) : QWidget(parent) {}

void G_Stack::set_positionY(uint positionY) {
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

G_Card* G_Stack::find_card(uint y) {
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
    std::string str;
    if (static_cast<std::string>(style) == "Border: 2px solid red;" && gcard->card.is_error_card())
        return;
    if (gcard == nullptr) return;
    if (this->type == Working)
    {
        bool found = false;
        if (stack.size() == 1) {
            stack[0]->setStyleSheet(style);
        }
        for (uint i = 0; i < stack.size(); i++) {
            if (stack[i]->card.is_visible() && gcard->card == stack[i]->card) {
                found = true;
            }
            if (found) {
                stack[i]->setStyleSheet(style);
            }
        }
    }
    else {
       if (!(this->type == Visible) || gcard->card.is_visible())
         gcard->setStyleSheet(style);
    }
}

void G_Stack::set_border(const char *style, Card card) {
    G_Card * gcard = new G_Card(card, 0);
    if (gcard == nullptr) return;
    if (this->type == Working)
    {
        if (stack.size() == 1) {
            stack[0]->setStyleSheet(style);
        }
        bool found = false;
        for (uint i = 0; i < stack.size(); i++) {
            if (stack[i]->card.is_visible() && gcard->card == stack[i]->card) {
                found = true;
            }
            if (found) {
                stack[i]->setStyleSheet(style);
            }
        }
    }
    else {
       if (!(this->type == Visible) || gcard->card.is_visible())
         gcard->setStyleSheet(style);
    }
    delete gcard;
}

void G_Stack::mousePressEvent(QMouseEvent *event) {
    G_Card *gcard = find_card(event->pos().y());
    switch(this->type) {
       case Working:
           board->clicked_working(this->id , gcard); break;
       case Single_Color:
           board->clicked_color(this->id); break;
       case Hidden:
           board->clicked_hidden(); break;
       default:
           board->clicked_visible();
    }
}
void G_Stack::process_command() {
    this->board->process_command();
}

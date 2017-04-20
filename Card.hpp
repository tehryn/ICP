#ifndef CARD
#define CARD
#include <iostream>
#include <string>
enum Color {
    ERR = 0,
    HEARTS,
    SPADES,
    DIAMONDS,
    CLUBS
};

class Card {
protected:
    int value       = 0;
    int color       = ERR;
    bool visibility = false;
public:
    Card(){}
    Card(int value, int color) { this->value = value; this->color = color; }
    int  get_value()           { return this->value; }
    int  get_color()           { return this->color; }
    bool is_visible()          { return this->visibility; }
    void make_visible()        { this->visibility = true; }
    void make_hidden()         { this->visibility = false; }
    bool is_similar(Card card) { return (card.color%2) == (this->color%2); }
    bool is_error_card() const {
        return color == ERR || value <= 0 || value > 13;
    }
    std::string to_string() const;

    friend bool operator == (const Card& card1, const Card card2) {
        return (card1.value == card2.value) && (card1.color == card2.color);
    }

    friend std::ostream& operator << (std::ostream& stream, const Card card) {
        if (card.is_error_card()) {
            stream << "--|EMPTY |";
        }
        else if(card.visibility) {
            switch(card.value) {
                case 13: stream << "--| K"; break;
                case 12: stream << "--| Q"; break;
                case 11: stream << "--| J"; break;
                case 10: stream << "--|10"; break;
                case  1: stream << "--| A"; break;
                default: stream << "--| " << card.value;
            }
            switch(card.color) {
                case HEARTS:   stream << "(H) |"; break;
                case SPADES:   stream << "(S) |"; break;
                case DIAMONDS: stream << "(D) |"; break;
                case CLUBS:    stream << "(C) |"; break;
                default:       stream << "(ERR) |";
            }
        }
        else {
            stream << "--|OOOOOO|";
        }
        return stream;
    }
};
#endif
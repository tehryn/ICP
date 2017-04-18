#ifndef CARD
#define CARD
#include <iostream>
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
    friend bool operator == (const Card& card1, const Card card2) {
        return (card1.value == card2.value) && (card1.color == card2.color);
    }
    friend std::ostream& operator << (std::ostream& stream, const Card card) {
        char color;
        switch(card.color) {
            case HEARTS:   color = 'H'; break;
            case SPADES:   color = 'S'; break;
            case DIAMONDS: color = 'D'; break;
            case CLUBS:    color = 'C'; break;
            default:       color = 'E';
        }
        char vis = 'F';
        if (card.visibility) {
            vis = 'T';
        }
        stream << card.value << "(" << color << ")" << vis;
        return stream;
    }
};
#endif
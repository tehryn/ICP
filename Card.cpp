#ifndef CARD
#define CARD
#include <iostream>
enum Color {
    ERR = 0,
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS
};

class Card {
protected:
    int value       = 0;
    int color       = ERR;
    bool visibility = false;
public:
    Card(int value, int color) { this->value = value; this->color = color; }
    int  get_value()    { return this->value; }
    int  get_color()    { return this->color; }
    bool is_visible()   { return this->visibility; }
    void make_visible() { this->visibility = true; }
    bool operator == (const Card& card) { return (this->value == card.value) && (this->color == card.color); }
};
#endif
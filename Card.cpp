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
    int value = 0;
    int color = ERR;
public:
    Card(int value, int color) { this->value = value; this->color = color; }
    int get_value() { return this->value; }
    int get_color() { return this->color; }
    bool operator == (const Card& card) { return (this->value == card.value) && (this->color == card.color); }
};
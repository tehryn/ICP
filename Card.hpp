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
    int  get_value()           { return this->value; }
    int  get_color()           { return this->color; }
    bool is_visible()          { return this->visibility; }
    void make_visible()        { this->visibility = true; }
    bool is_similar(Card card) { return (card.value%2) != (this->value%2); }
    friend bool operator == (const Card& card1, const Card card2) { return (card1.value == card2.value) && (card1.color == card2.color); }
    friend std::ostream& operator << (std::ostream& stream, const Card card) { stream << card.value << "(" << card.color << ")"; return stream; }
};
#endif
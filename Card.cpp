#include "Card.hpp"

std::string Card::to_string() const {
    std::string str = "";
    str += std::to_string(value);
    switch(color) {
        case HEARTS:   str += "(H)"; break;
        case SPADES:   str += "(S)"; break;
        case DIAMONDS: str += "(D)"; break;
        case CLUBS:    str += "(C)"; break;
        default:       str += "(ERR)";
    }
    if (this->visibility) {
        str += 'T';
    }
    else {
        str += 'F';
    }
    return str;
}
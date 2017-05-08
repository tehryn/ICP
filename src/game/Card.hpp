/** @file
 *  Header file for class Card.
 *  @author Matejka Jiri (xmatej52)
 */
#ifndef CARD
#define CARD
#include <iostream>
#include <string>

/**
 * Enum representing colours of cards.
 * @author Matejka Jiri (xmatej52)
 */
enum Color {
    ERR = 0,
    HEARTS,
    SPADES,
    DIAMONDS,
    CLUBS
};

/**
 * @brief Class representing Card.
 *
 * Class representing Card. Card has value, colour and visibility. <br>
 * Value is from 0 to 13, where 0 represents invalid card. <br>
 * Colours are ERR, CLUBS, DIAMONDS, HEARTS and SPADES, where ERR represents
 * invalid card. <br>
 * Visibility tells if card with its face up or not. Has values true and false. <br>
 * For checking validity of card, please use always colour and looks for value
 * ERR.
 * @author Matejka Jiri (xmatej52)
 */
class Card {
protected:
    /// @var Represents value of card.
    int value       = 0;

    /// @var Represents color of card.
    int color       = ERR;

    /// @var Represents visibility of card.
    bool visibility = false;

public:

    /**
    * Constructor of Card. Sets value to 0, color to ERR and visibility to false.
    * @return card with invalid values.
    */
    Card(){}

    /**
     * Constructor of Card. Sets visibility to false.
     * @param  value Value of new card.
     * @param  color Color of new card.
     * @return New card.
     */
    Card(int value, int color) { this->value = value; this->color = color; }

    /**
     * Retrieve value of card.
     * @return Value of card.
     */
    int  get_value()           { return this->value; }

    /**
     * Retrieve color of card.
     * @return color of card.
     */
    int  get_color()           { return this->color; }

    /**
     * Retrive visibility of card.
     * @return True if card is visible, otherwise false.
     */
    bool is_visible()          { return this->visibility; }

    /**
     * Sets visibility of card to true.
     */
    void make_visible()        { this->visibility = true; }

    /**
     * Sets visibility of card to false.
     */
    void make_hidden()         { this->visibility = false; }

    /**
     * Checks if cards has similar colors.
     * @param  card Second card.
     * @return      True of cards colors are similar, otherwise false.
     */
    bool is_similar(Card card) { return (card.color%2) == (this->color%2); }

    /**
     * Check if card has invalid color or value
     * @return True if card is invalid, otherwise false.
     */
    bool is_error_card() const {
        return color == ERR || value <= 0 || value > 13;
    }

    /**
     * Converts card to string. Value of 11, 12 and 13 is represented by J, Q
     * and K. Value 1 as A. Information about visibility of card is not included
     * in string.
     * @param card Card that will be converted.
     * @return     String representing card.
     */
    static std::string to_string(const Card card) {
        std::string str = "";
        switch(card.value) {
            case  1: str += "A"; break;
            case 11: str += "J"; break;
            case 12: str += "Q"; break;
            case 13: str += "K"; break;
            default: str += std::to_string(card.value);
        }
        switch(card.color) {
            case HEARTS:   str += "(H)"; break;
            case SPADES:   str += "(S)"; break;
            case DIAMONDS: str += "(D)"; break;
            case CLUBS:    str += "(C)"; break;
            default:       str += "(ERR)";
        }
        return str;
    }

    /**
     * Converts card to string. Value of 11, 12 and 13 is represented by J, Q
     * and K. Value 10 as L Information about visibility of card is included
     * in string.
     * @return String representing card.
     */
    std::string to_string() const {
        std::string str = "";
        switch(value) {
            case 10: str += "L"; break;
            case 11: str += "J"; break;
            case 12: str += "Q"; break;
            case 13: str += "K"; break;
            case  1: str += "A"; break;
            default: str += std::to_string(value);
        }
        switch(color) {
            case HEARTS:   str += "(H)"; break;
            case SPADES:   str += "(S)"; break;
            case DIAMONDS: str += "(D)"; break;
            case CLUBS:    str += "(C)"; break;
            default:       str += "(E)";
        }
        if (this->visibility) {
            str += 'T';
        }
        else {
            str += 'F';
        }
        return str;
    }

    /**
     * Converts string into card
     * @param  str String representing card.
     * @param  idx Index in string where function will expect card.
     * @return     Card that was represented by string. Error card when
     *             string was invalid.
     */
     static Card string_to_card(std::string str, unsigned idx=0) {
         unsigned size = str.size();
         Card card;
         if (idx < size) {
             int value = 0;
             int color = ERR;
             switch(str[idx]) {
                 case 'A': value = 1; break;
                 case 'K': value = 13; break;
                 case 'Q': value = 12; break;
                 case 'J': value = 11; break;
                 case '1': idx++; value = 10; break;
                 default : value = str[idx] - '0';
             }
             idx+=2;
             if (idx < size && value > 0 && value < 14) {
                 switch(str[idx]) {
                     case 'D': color = DIAMONDS; break;
                     case 'H': color = HEARTS; break;
                     case 'S': color = SPADES; break;
                     case 'C': color = CLUBS; break;
                     default : color = ERR;
                 }
                 card = Card(value, color);
             }
             card.visibility = true;
             return card;

         }
         else {
             return card;
         }
     }

    /**
     * Overloads operator ==
     */
    friend bool operator == (const Card& card1, const Card card2) {
        return (card1.value == card2.value) && (card1.color == card2.color);
    }

    /**
     * Converts color to string.
     * @param  color Color that will be converted.
     * @return       String representing given color.
     */
    static std::string color_to_string(int color) {
        switch(color) {
            case ERR:      return "E";
            case HEARTS:   return "H";
            case SPADES:   return "S";
            case DIAMONDS: return "D";
            case CLUBS:    return "C";
            default:       return "";
        }
    }

    /**
     * Overloads output stream operator.
     */
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
            }
        }
        else {
            stream << "--|OOOOOO|";
        }
        return stream;
    }
};
#endif
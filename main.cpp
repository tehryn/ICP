#include "Card.hpp"
#include "Card_stack.hpp"
#include "Single_color_stack.hpp"

using namespace std;
int main() {
    Card_stack card_pack = Card_stack::new_deck();
    Card card = card_pack.pop_random();
    while (card.get_color() != ERR) {
//        cout << card << endl;
        card = card_pack.pop_random();
    }
    Single_color_stack H_stack(HEARTS);
    for (int i = 1, j = 3; i < 5; i++, j++) {
        Card card1(i, HEARTS), card2(j, HEARTS), card3(i, SPADES);
        cout << H_stack.push(card1) << endl;
        cout << H_stack.push(card2) << endl;
        cout << H_stack.push(card3) << endl;
    }
}
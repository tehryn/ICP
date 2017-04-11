#include "Card.hpp"
#include "Card_stack.hpp"
#include "Single_color_stack.hpp"
#include "Working_stack.hpp"

using namespace std;
int main() {
    Card_stack card_pack = Card_stack::new_deck();
    Card card = card_pack.pop_random();
    while (card.get_color() != ERR) {
//        cout << card << endl;
        card = card_pack.pop_random();
    }
    Single_color_stack H_stack;
    for (int i = 1, j = 3; i < 5; i++, j++) {
        Card card1(i, HEARTS), card2(j, HEARTS), card3(i, SPADES);
//        cout << "should be 1: " << H_stack.push(card1) << endl;
//        cout << "should be 0: " << H_stack.push(card2) << endl;
//        cout << "should be 0: " << H_stack.push(card3) << endl;
    }
    while(H_stack.size()) {
//        cout << H_stack.pop() << " ";
    }
//    cout << endl;

    Card card1 = Card(13, HEARTS);
    Card card2 = Card(12, SPADES);
    Card card3 = Card(11, DIAMONDS);
    Card card4 = Card(10, CLUBS);
    Card card5 = Card(9, SPADES);
    Card card6 = Card(8, HEARTS);
    Working_stack W_stack1;
    W_stack1.push(card1);
    W_stack1.push(card2);
    W_stack1.push(card3);
    W_stack1.push(card4);
    W_stack1.push(card5);
    W_stack1.push(card6);
    cout << "should be 4: " << W_stack1.size() << endl;

}
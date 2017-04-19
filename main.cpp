#include "Card.hpp"
#include "Card_stack.hpp"
#include "Single_color_stack.hpp"
#include "Working_stack.hpp"
#include "Card_deck_hidden.hpp"
#include "Card_deck_visible.hpp"
#include "Board.hpp"

using namespace std;
void print(Board g) {
    cout << g;
}
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
    card1.make_visible();
    card2.make_visible();
    card3.make_visible();
    card4.make_visible();
    card5.make_visible();
    card6.make_visible();
    Working_stack W_stack1, W_stack2, W_stacktmp;
    W_stack1.push(card1);
    W_stack1.push(card2);
    W_stack1.push(card3);
    W_stack1.push(card4);
    W_stack1.push(card5);
    W_stack1.push(card6);
//    cout << "should be 4: " << W_stack1.size() << endl;
    W_stacktmp = W_stack1.pop_until(card1);
//    cout << "should be 04: " << W_stack1.size() << W_stacktmp.size() << endl;
    W_stack1 = W_stacktmp.pop_until(card3);
//    cout << "should be 22: " << W_stack1.size() << W_stacktmp.size() << endl;
    W_stacktmp.push(W_stack1.pop_until(card3));
//    cout << "should be 04: " << W_stack1.size() << W_stacktmp.size() << endl;
    Board game, game2;
//    game.new_game();
//    game.save_game("saved.txt");
//    cout << game;
    game2.load_game("saved.txt");
    cout << game2 << "-----------------" << endl;
    game2.fromH_toV();
    game2.fromH_toV();
    game2.fromV_toC(0);
    game2.fromC_toC(0, 2);
    game2.fromH_toV();
    game2.fromV_toC(0);
    game2.fromV_toC(0);

    cout << game2;

}
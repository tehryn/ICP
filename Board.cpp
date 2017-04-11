#include "Board.hpp"

void Board::new_game() {
    Card_stack pack_of_cards = Card_stack::new_deck();
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) {
            working_stacks[i].force_push(pack_of_cards.pop_random());
        }
        working_stacks[i].set_top_visible();
    }
    Card tmp = pack_of_cards.pop_random();
    while (tmp.get_color() != ERR) {
        hidden_deck.force_push(tmp);
        tmp = pack_of_cards.pop_random();
    }
}

bool Board::move_Wstack(unsigned from, unsigned to, Card card) {
    if (from > 7 || to > 7) {
        return false;
    }
    Working_stack tmp = working_stacks[from].pop_until(card);
    if (tmp.size() > 0) {
        if (!working_stacks[to].push(tmp)) {
            int size = tmp.size();
            for (int i = 0; i < size; i++) {
                working_stacks[from].force_push(tmp.pop_bottom());
            }
        }
    }
}
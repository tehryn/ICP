#include "Board.hpp"

void Board::new_game() {
    Card_stack pack_of_cards = Card_stack::new_deck();
    for (int i = 0; i < 7; i++) {
        working_stacks[i].clear();
        for (int j = 0; j < i + 1; j++) {
            working_stacks[i].force_push(pack_of_cards.pop_random());
        }
        working_stacks[i].set_top_visible();
    }
    hidden_deck.clear();
    visible_deck.clear();
    Card tmp = pack_of_cards.pop_random();
    while (tmp.get_color() != ERR) {
        hidden_deck.force_push(tmp);
        tmp = pack_of_cards.pop_random();
    }
    for (int i = 0; i < 4; i++) {
        color_stacks[i].clear();
    }
}

bool Board::fromW_toW(unsigned from, unsigned to, Card card) {
    if (from > 6 || to > 6) {
        return false;
    }
    Working_stack tmp = working_stacks[from].pop_until(card);
    if (tmp.size() > 0) {
        if (!working_stacks[to].push(tmp)) {
            int size = tmp.size();
            for (int i = 0; i < size; i++) {
                working_stacks[from].force_push(tmp.pop_bottom());
            }
            return false;
        }
        else {
            working_stacks[from].set_top_visible();
            return true;
        }
    }
    return true;
}

bool Board::fromC_toC(unsigned from, unsigned to) {
    if (color_stacks[to].size() != 0 || color_stacks[from].size() != 1 || to > 3 || from > 3) {
        return false;
    }
    else {
        return color_stacks[to].push(color_stacks[from].pop());
    }
}

bool Board::fromW_toC(unsigned from, unsigned to) {
    if (from >= 7 || to >= 4) {
        return false;
    }
    else {
        Card tmp = working_stacks[from].top();
        if (color_stacks[to].push(tmp)) {
            working_stacks[from].pop();
            working_stacks[from].set_top_visible();
            return true;
        }
        else {
            return false;
        }
    }
}

bool Board::fromC_toW(unsigned from, unsigned to) {
    if (from > 3 || to > 6) {
        return false;
    }
    else if (color_stacks[from].size() > 0) {
        Card tmp = color_stacks[from].pop();
        if (working_stacks[to].push(tmp)) {
            return true;
        }
        else {
            color_stacks[from].push(tmp);
            return false;
        }
    }
    else {
        return true;
    }
}

void Board::fromH_toV() {
    if (hidden_deck.size() == 0) {
        int size = hidden_deck.size();
        for (int i = 0; i < size; i++) {
            Card tmp = visible_deck.pop();
            tmp.make_hidden();
            hidden_deck.force_push(tmp);
        }
    }
    else {
        Card tmp = hidden_deck.pop();
        tmp.make_visible();
        visible_deck.force_push(tmp);
    }
}


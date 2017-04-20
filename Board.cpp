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

bool Board::save_game(std::string filename) {
    std::ofstream out(filename, std::ofstream::out);
    if (out.is_open()) {
        std:: string str = "";
        for (unsigned i = 0; i < 7 ; i++) {
            str += working_stacks[i].to_string() + "\n";
        }
        for (unsigned i = 0; i < 4 ; i++) {
            str += color_stacks[i].to_string() + "\n";
        }
        str += hidden_deck.to_string()  + "\n";
        str += visible_deck.to_string() + "\n";
        str += score                    + "\n";
        out << str;
        out.close();
        return true;
    }
    else {
        return false;
    }
}

bool Board::load_game(std::string filename) {
    std::fstream in(filename, std::fstream::in);
    if (!in.is_open()) {
        return false;
    }
    try {
        std::string line;
        int lines = 0;
        size_t size;
        while (!in.eof()) {
            getline(in, line);
            if (lines < 13) {
                size = line.size();
                std::string tmp = "";
                int value = 0;
                Card card;
                char c = 'E';
                for(unsigned i = 0; i < size; i++) {
                    if (line[i] == '\n') {
                        break;
                    }
                    else if (line[i] == '(') {
                        value = stoi(tmp);
                    }
                    else if (line[i] == ')') {
                        tmp = "";
                        if (c == 'C') {
                            card = Card(value, CLUBS);
                        }
                        else if (c == 'D') {
                            card = Card(value, DIAMONDS);
                        } else if (c == 'H') {
                            card = Card(value, HEARTS);
                        } else if (c == 'S') {
                            card = Card(value, SPADES);
                        }
                        else {
                            in.close();
                            return false;
                        }
                        i++;
                        if (line[i] == 'T') {
                            card.make_visible();
                        }
                        switch(lines) {
                            /*from 0 to 6 - reading working_stacks*/
                            case 0:
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                            case 5:
                            case 6:
                                this->working_stacks[lines].force_push(card);
                                break;
                            /* from 7 to 10 - reading color_stacks*/
                            case 7:
                            case 8:
                            case 9:
                            case 10:
                                this->color_stacks[lines-7].force_push(card);
                                break;
                            /* reading hidden_deck */
                            case 11:
                                this->hidden_deck.force_push(card);
                                break;
                            /* reading visible_deck */
                            case 12:
                                this->visible_deck.force_push(card);
                        }
                    }
                    else {
                        tmp += line[i];
                        c    = line[i];
                    }
                }
            }
            else {
                this->score = stoi(line);
                in.close();
                return true;
            }
            lines++;
        }
    } catch (std::exception& e) {
        ;;;
    }
    in.close();
    return false;
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

bool Board::fromV_toC(unsigned to) {
    if (color_stacks[to].push(visible_deck.top())) {
        visible_deck.pop();
        return true;
    }
    else {
        return false;
    }
}

bool Board::fromV_toW(unsigned to) {
    if (working_stacks[to].push(visible_deck.top())) {
        visible_deck.pop();
        return true;
    }
    else {
        return false;
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
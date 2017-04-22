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
        str += std::to_string(score)    + "\n";
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
                                this->color_stacks[lines-7].push(card);
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
    if (from > 6 || to > 6 || card.is_error_card()) {
        std::cerr << "Chybna karta\n";
        return false;
    }
    Working_stack tmp = working_stacks[from].pop_until(card);
    size_t size = tmp.size();
    if (size > 0) {
        if (!working_stacks[to].push(tmp)) {
            for (size_t i = 0; i < size; i++) {
                working_stacks[from].force_push(tmp.pop_bottom());
            }
            std::cerr << "selhal push";
            return false;
        }
        else {
            history.push(Move(WW, from, to, size, !working_stacks[from].top().is_visible()));
            working_stacks[from].set_top_visible();
            return true;
        }
    }
    std::cerr << "chyba v pop until\n";
    return false;
}

bool Board::fromC_toC(unsigned from, unsigned to) {
    if (color_stacks[to].push(color_stacks[from].top())) {
        color_stacks[from].pop();
        history.push(Move(CC, from, to, 1, false));
        return true;
    }
    else {
        return false;
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
            history.push(Move(WC, from, to, 1, !working_stacks[from].top().is_visible()));
            working_stacks[from].set_top_visible();
            score += 15;
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
        if (working_stacks[to].push(color_stacks[from].top())) {
            color_stacks[from].pop();
            history.push(Move(CW, from, to, 1, false));
            score = (score>15)?(score-15):0;
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Board::fromV_toC(unsigned to) {
    if (color_stacks[to].push(visible_deck.top())) {
        visible_deck.pop();
        history.push(Move(VC, 0, to, 1, false));
        score += 20;
        return true;
    }
    else {
        return false;
    }
}

bool Board::fromV_toW(unsigned to) {
    if (working_stacks[to].push(visible_deck.top())) {
        visible_deck.pop();
        history.push(Move(VW, 0, to, 1, false));
        score += 5;
        return true;
    }
    else {
        return false;
    }
}

void Board::fromH_toV() {
    if (hidden_deck.size() == 0) {
        int size = visible_deck.size();
        for (int i = 0; i < size; i++) {
            Card tmp = visible_deck.pop();
            tmp.make_hidden();
            hidden_deck.force_push(tmp);
        }
        score = (score>100)?(score-100):0;
        history.push(Move(H, 0, 0, size, true));
    }
    else {
        Card tmp = hidden_deck.pop();
        tmp.make_visible();
        visible_deck.force_push(tmp);
        history.push(Move(H, 0, 0, 1, true));
    }
}

Move Board::undo() {
    Move move = history.pop();
    Card tmp;
    Working_stack new_stack;
    switch(move.get_type()) {
        case INV: break;
        case WW:
            new_stack.clear();
            if (move.was_turned()) {
                working_stacks[move.get_from()].set_top_hidden();
            }
            for(int i = 0; i < move.get_count(); i++) {
                tmp = working_stacks[move.get_to()].pop();
                new_stack.insert_bottom(tmp);
            }
            for(int i = 0; i < move.get_count(); i++) {
                working_stacks[move.get_from()].force_push(new_stack.pop_bottom());
            }
            break;
        case WC:
            if (move.was_turned()) {
                working_stacks[move.get_from()].set_top_hidden();
            }
            tmp = color_stacks[move.get_to()].pop();
            working_stacks[move.get_from()].force_push(tmp);
            score -= 15;
            break;
        case CW:
            tmp = working_stacks[move.get_to()].pop();
            color_stacks[move.get_from()].force_push(tmp);
            score += 15;
            break;
        case CC:
            tmp = color_stacks[move.get_to()].pop();
            color_stacks[move.get_from()].force_push(tmp);
            break;
        case VW:
            tmp = working_stacks[move.get_to()].pop();
            visible_deck.force_push(tmp);
            score -= 5;
            break;
        case VC:
            tmp = color_stacks[move.get_to()].pop();
            visible_deck.force_push(tmp);
            score -= 20;
            break;
        case  H:
        if (move.get_count() > 1) {
            for(int i = 0; i < move.get_count(); i++) {
                tmp = hidden_deck.pop();
                tmp.make_visible();
                visible_deck.force_push(tmp);
            }
            score += 100;
        } else {
            tmp = visible_deck.pop();
            tmp.make_hidden();
            hidden_deck.force_push(tmp);
        }
    }
    return move;
}

std::vector<Move> Board::help() {
    std::vector<Move> possible_moves;
    Card card;
    size_t size = 0;
    for (int from = 0; from < 7; from++) {
        for (int to = 0; to < 7; to++) {
            size = working_stacks[from].size();
            for (size_t i = 0; i < size; i++) {
                card = working_stacks[from].get(i);
                if (fromW_toW(from, to, card)) {
                    possible_moves.push_back(undo());
                }
            }
        }
    }

    for (int from = 0; from < 7; from++) {
        for (int to = 0; to < 4; to++) {
            if (fromW_toC(from, to)) {
                possible_moves.push_back(undo());
            }
        }
    }    return possible_moves;
}
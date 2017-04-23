/*
 * Author: Matejka Jiri
 * login:  xmatej52
 * school: VUT FIT
 * date:   22. 4. 2017
 */
#include "Board.hpp"

void Board::new_game() {
    clear();
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
    clear();
    std::fstream in(filename, std::fstream::in);
    if (!in.is_open()) {
        return false;
    }
    std::string line;
    int lines = 0;
    size_t size;
    while (!in.eof()) {
        getline(in, line);
        if (lines == 13) {
            try {
                score = stoi(line);
                in.close();
                return true;
            } catch (std::invalid_argument &e) {
                in.close();
                clear();
                return false;
            }
        }
        if (line == "") {
            lines++;
            continue;
        }
        size = line.size();
        Card card;
        std::string c = "";
        for(unsigned i = 0; i < size; i++) {
            if ((i + 4) >= size || line[i+1] != '(' || line[i+3] != ')' || (line.c_str()[i+4] != 'F' && line.c_str()[i+4] != 'T')) {
                in.close();
                clear();
                return false;
            }
            if (line[i] == 'L') {
                c = "10" + line.substr(i+1, 3);
            }
            else {
                c = line.substr(i, 4);
            }
            card = Card::string_to_card(c);
            if (card.is_error_card()) {
                in.close();
                clear();
                return false;
            }
            if (line[i+4] == 'F') {
                card.make_hidden();
            }
            if (lines < 7) {
                this->working_stacks[lines].force_push(card);
            }
            else if (lines < 11 ) {
                this->color_stacks[lines-7].push(card);
            }
            else if (lines == 11) {
                this->hidden_deck.force_push(card);
            }
            else if (lines == 12) {
                this->visible_deck.force_push(card);
            }
            else {
                in.close();
                clear();
                return false;
            }
            i+=4;
        }
        lines++;
    }
    in.close();
    clear();
    return false;
}

bool Board::is_victory() {
    bool ret = true;
   for (int i = 0; i < 4; i++) {
       if (color_stacks[i].top().get_value() != 13) {
           ret = false;
       }
    }
    return ret;
}

bool Board::fromW_toW(unsigned from, unsigned to, Card card) {
    if (from > 6 || to > 6 || card.is_error_card()) {
        return false;
    }
    Working_stack tmp = working_stacks[from].pop_until(card);
    size_t size = tmp.size();
    if (size > 0) {
        if (!working_stacks[to].push(tmp)) {
            for (size_t i = 0; i < size; i++) {
                working_stacks[from].force_push(tmp.pop_bottom());
            }
            return false;
        }
        else {
            history.push(Move(WW, from, to, card, !working_stacks[from].top().is_visible()));
            working_stacks[from].set_top_visible();
            generate = true;
            return true;
        }
    }
    return false;
}

bool Board::fromC_toC(unsigned from, unsigned to) {
    if (color_stacks[to].push(color_stacks[from].top())) {
        history.push(Move(CC, from, to, color_stacks[from].pop(), false));
        generate = true;
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
            Card tmp = working_stacks[from].pop();
            history.push(Move(WC, from, to, tmp, !working_stacks[from].top().is_visible()));
            working_stacks[from].set_top_visible();
            score += 15;
            generate = true;
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
            history.push(Move(CW, from, to, color_stacks[from].pop(), false));
            score = (score>15)?(score-15):0;
            generate = true;
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
        history.push(Move(VC, 0, to, visible_deck.pop(), false));
        score += 20;
        generate = true;
        return true;
    }
    else {
        return false;
    }
}

bool Board::fromV_toW(unsigned to) {
    if (working_stacks[to].push(visible_deck.top())) {
        history.push(Move(VW, 0, to, visible_deck.pop(), false));
        score += 5;
        generate = true;
        return true;
    }
    else {
        return false;
    }
}

void Board::fromH_toV() {
    if (hidden_deck.size() == 0 && visible_deck.size() == 0) {
        return;
    }
    if (hidden_deck.size() == 0) {
        int size = visible_deck.size();
        for (int i = 0; i < size; i++) {
            Card tmp = visible_deck.pop();
            tmp.make_hidden();
            hidden_deck.force_push(tmp);
        }
        score = (score>100)?(score-100):0;
        history.push(Move(H, 0, 0, Card(0, ERR), true));
    }
    else {
        Card tmp = hidden_deck.pop();
        tmp.make_visible();
        visible_deck.force_push(tmp);
        history.push(Move(H, 0, 0, tmp, true));
    }
    generate = true;
}

Move Board::undo() {
    Move move = history.pop();
    Card tmp;
    Working_stack new_stack;
    size_t size;
    switch(move.get_type()) {
        case INV: return move;
        case WW:
            new_stack.clear();
            if (move.was_turned()) {
                working_stacks[move.get_from()].set_top_hidden();
            }
            new_stack = working_stacks[move.get_to()].pop_until(move.get_card());
            size = new_stack.size();
            for(unsigned i = 0; i < size; i++) {
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
        if (move.get_card().is_error_card()) {
            size = hidden_deck.size();
            for(unsigned i = 0; i < size; i++) {
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
    generate = true;
//    score = (score>5)?score-5:0;
    return move;
}

Move Board::help() {
    if (generate || possible_moves.size() == 0) {
        generate = false;
        generate_moves();
    }
    return possible_moves.pop();
}

void Board::generate_moves() {
    possible_moves.clear();
    Card card;
    size_t size = 0;
    for (int from = 0; from < 7; from++) {
        for (int to = 0; to < 7; to++) {
            if (from == to) {
                continue;
            }
            size = working_stacks[from].size();
            for (size_t i = 0; i < size; i++) {
                card = working_stacks[from].get(i);
                if (fromW_toW(from, to, card)) {
                    possible_moves.push(undo());
                }
            }
        }
    }
    for (int from = 0; from < 7; from++) {
        for (int to = 0; to < 4; to++) {
            if (fromW_toC(from, to)) {
                possible_moves.push(undo());
            }
        }
    }
    for (int to = 0; to < 7; to++) {
        if (fromV_toW(to)) {
            possible_moves.push(undo());
        }
    }
    for (int to = 0; to < 4; to++) {
        if (fromV_toC(to)) {
            possible_moves.push(undo());
        }
    }
    generate = false;
}
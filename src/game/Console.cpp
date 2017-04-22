#include "Console.hpp"

bool Console::string_to_command(std::string str) {
    size_t size = str.size();
    std::string cmd1, cmd2, cmd3, tmp;
    int to = 10, from = 10;
    Card card;
    int arg_id = 0;
    for (size_t i = 0; i < size; i++) {
        switch(arg_id) {
            case 0:
                if (str[i] == ' ') {
                    arg_id++;
                }
                else {
                    cmd1 += str[i];
                }
                break;
            case 1:
                if (str[i] == ' ') {
                    arg_id++;
                }
                else {
                    cmd2 += str[i];
                }
                break;
            case 2:
                if (isdigit(str[i])) {
                    from = str[i++] - '0';
                    arg_id++;
                }
                else {
                    i--;
                    arg_id++;
                }
                break;
            case 3:
                if (str[i] == ' ') {
                    arg_id++;
                }
                else {
                    cmd3 += str[i];
                }
                break;
            case 4:
                to = str[i++] - '0';
                arg_id++;
                break;
            case 5: tmp += str[i];
        }
    }
    card = string_to_card(tmp, 0);
    return command(cmd1, cmd2, from, cmd3, to, card);
}

Card Console::string_to_card(std::string str, unsigned idx=0) {
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
        return card;

    }
    else {
        return card;
    }
}

void Console::help() {
    std::cout << "Use: Command [FILENAME] [ [ [ [ [ Card_stack1 ] FROM ] Card_stack2 TO ] CARD ] ]\n\n";
    std::cout << "Command1 is one of following strings:\n";
    std::cout << "print - prints game on stdout\n";
    std::cout << "move  - moves card(s) from Card_stack1 with index FROM to Card_stack2 with index TO until CARD is reached\n";
    std::cout << "load  - loads game that is saved in file FILENAME\n";
    std::cout << "save  - saves game into file FILENAME\n";
    std::cout << "new   - creates new game\n";
    std::cout << "help  - prints this message to stdout\n";
    std::cout << "\n";
    std::cout << "FILENAME is string representing path to file.\n";
    std::cout << "Card_stacks represent working (W), color (C), hidden (H) or visible (V) deck.\n";
    std::cout << "Card_stack1 represents deck from which card(s) will be taken\n";
    std::cout << "Card_stack2 represents deck to which card(s) will be added\n";
    std::cout << "FROM is ID of Card_stack1 (0-6 when Card_stack1 is working, 0-3 when Card_stack1 is color)";
    std::cout << "TO is ID of same values as FROM, but represents ID of Card_stack2";
    std::cout << "CARD is only used when moving card(s) between 2 working stacks";
    std::cout << "and all cards until CARD is reached will be moved between them\n";
}

bool Console::command(std::string cmd1, std::string cmd2="", unsigned from=10, std::string cmd3="", unsigned to=10, Card card=err) {
    bool ret = false;
    if (cmd1 == "print") {
        ret = true;
    }
    else if (cmd1 == "move") {
        if (cmd2 == "H" || cmd2 == "hidden") {
            game.fromH_toV();
            ret = true;
        }
        else if (cmd2 == "V" || cmd2 == "visible") {
            if (cmd3 == "W" || cmd3 == "working") {
                ret = game.fromV_toW(to);
            }
            else if (cmd3 == "C" || cmd3 == "color") {
                ret = game.fromV_toC(to);
            }
        }
        else if (cmd2 == "W" || cmd2 == "working") {
            if(cmd3 == "W" || cmd3 == "working") {
                ret = game.fromW_toW(from, to, card);
            }
            else if (cmd3 == "C" || cmd3 == "color") {
                ret = game.fromW_toC(from, to);
            }
        }
        else if (cmd2 == "C" || cmd2 == "color") {
            if (cmd3 == "C" || cmd3 == "color") {
                ret = game.fromC_toC(from, to);
            }
            else if (cmd3 == "W" || cmd3 == "working") {
                ret = game.fromC_toW(from, to);
            }
        }
    }
    else if (cmd1 == "undo") {
        game.undo();
        ret = true;
    }
    else if (cmd1 == "load") {
        ret = game.load_game(cmd2);
    }
    else if (cmd1 == "save") {
        ret = game.save_game(cmd2);
    } else if (cmd1 == "new") {
        game.new_game();
        ret = true;
    }
    else if (cmd1 == "help") {
        help();
        return true;
    }
    if (ret) {
        std::cout << game;
    }
    return ret;
}

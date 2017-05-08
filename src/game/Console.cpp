/*
 * Author: Matejka Jiri
 * login:  xmatej52
 * school: VUT FIT
 * date:   23. 4. 2017
 */
#include "Console.hpp"

bool Console::string_to_command(std::string str) {
    size_t size = str.size();
    std::string cmd1, cmd2, cmd3, tmp;
    int to = 10, from = 10;
    Card card;
    int arg_id = 0;
    for (size_t i = 0; i < size; i++) {
        switch(arg_id) {
            case 0: // cmd 1
                if (str[i] == ' ') {
                    arg_id++;
                }
                else {
                    cmd1 += str[i];
                }
                break;
            case 1: // cmd 2
                if (str[i] == ' ') {
                    arg_id++;
                }
                else {
                    cmd2 += str[i];
                }
                break;
            case 2: // id
                if (isdigit(str[i])) {
                    from = str[i++] - '0';
                    arg_id++;
                }
                else {
                    i--;
                    arg_id++;
                }
                break;
            case 3: // cmd3
                if (str[i] == ' ') {
                    arg_id++;
                }
                else {
                    cmd3 += str[i];
                }
                break;
            case 4: // card
                to = str[i++] - '0';
                arg_id++;
                break;
            case 5: tmp += str[i];
        }
    }
    card = Card::string_to_card(tmp, 0);
    return command(cmd1, cmd2, from, cmd3, to, card);
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
    std::cout << "hint  - display one possible move\n";
    std::cout << "undo  - undo one move\n";
    std::cout << "\n";
    std::cout << "FILENAME is string representing path to file.\n";
    std::cout << "Card_stacks represent working (W), color (C), hidden (H) or visible (V) deck.\n";
    std::cout << "Card_stack1 represents deck from which card(s) will be taken\n";
    std::cout << "Card_stack2 represents deck to which card(s) will be added\n";
    std::cout << "FROM is ID of Card_stack1 (0-6 when Card_stack1 is working, 0-3 when Card_stack1 is color)\n";
    std::cout << "TO is ID of same values as FROM, but represents ID of Card_stack2\n";
    std::cout << "CARD is only used when moving card(s) between 2 working stacks\n";
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
    else if (cmd1 == "hint") {
        Move tmp = game.help();
        if (!tmp.is_move_invalid()) {
            std::cout << "move " << tmp;
        }
        return true;
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
    }
    else if (cmd1 == "new") {
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
    if (game.is_victory()) {
        std::cout << "You won the game!" << std::endl;
        std::cout << "But you can continue playing..." << std::endl;
    }
    return ret;
}

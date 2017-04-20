#include "Board.hpp"
#include "Card.hpp"
#include <string>


class Console {
private:
    Board game;
    static Card err;
public:
    Console()       {}
    bool command(std::string cmd1, std::string cmd2="", unsigned from=10, std::string cmd3="", unsigned to=10, Card card=err) {
        if (cmd1 == "print") {
            std::cout << game;
            return true;
        }
        else if (cmd1 == "move") {
            if (cmd2 == "H" || cmd2 == "hidden") {
                game.fromH_toV();
                return true;
            }
            else if (cmd2 == "V" || cmd2 == "visible") {
                if (cmd3 == "W" || cmd3 == "working") {
                    return game.fromV_toW(to);
                }
                else if (cmd3 == "C" || cmd3 == "color") {
                    return game.fromV_toC(to);
                }
            }
            else if (cmd2 == "W" || cmd2 == "working") {
                if(cmd3 == "W" || cmd3 == "working") {
                    return game.fromW_toW(from, to, card);
                }
                else if (cmd3 == "C" || cmd3 == "color") {
                    return game.fromW_toC(from, to);
                }
            }
        }
        else if (cmd1 == "load") {
            return game.load_game(cmd2);
        }
        else if (cmd1 == "save") {
            return game.save_game(cmd2);
        } else if (cmd1 == "new") {
            game.new_game();
            return true;
        }
    }

    friend std::ostream& operator << (std::ostream& stream, const Console) {
        stream << "Use: Command [FILENAME] [ [ [ [ [ Card_stack1 ] FROM ] Card_stack2 TO ] CARD ] ]\n\n";
        stream << "Command1 is one of following strings:\n";
        stream << "print - prints game on stdout\n";
        stream << "move  - moves card(s) from Card_stack1 with index FROM to Card_stack2 with index TO until CARD is reached\n";
        stream << "load  - loads game that is saved in file FILENAME\n";
        stream << "save  - saves game into file FILENAME\n";
        stream << "new   - creates new game\n";
        stream << "\n";
        stream << "FILENAME is string representing path to file.\n";
        stream << "Card_stacks represent working (W), color (C), hidden (H) or visible (V) deck.\n";
        stream << "Card_stack1 represents deck from which card will be taken\n";
        stream << "Card_stack2 represents ";
        stream << "";
        stream << "";
        stream << "";
        stream << "";
        return stream;
    }
};
#ifndef CONSOLE
#define CONSOLE
#include "Board.hpp"
#include "Card.hpp"
#include <string>
#include <iostream>


class Console {
private:
    Board game;
    static Card err;
    bool command(std::string cmd1, std::string cmd2, unsigned from, std::string cmd3, unsigned to, Card card);
    bool string_to_command(std::string str);
    static Card string_to_card(std::string str, unsigned idx);
public:
    Console() {}
    void help();
    friend std::ostream& operator << (std::ostream& stream, const Console& console) {
        stream << console.game;
        return stream;
    }

    friend std::istream& operator >> (std::istream& stream, Console& console) {
        std::string line;
        while(!stream.eof()) {
            getline(stream, line);
            if (!console.string_to_command(line)) {
                if (line != "") {
                    std::cerr << "Invalid move or command '" << line << "'\n";
                }
            }
        }
        return stream;
    }

};
#endif
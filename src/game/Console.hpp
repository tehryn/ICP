/** @file
 *  Header file for class Console.
 *  @author Matejka Jiri (xmatej52)
 */
#ifndef CONSOLE
#define CONSOLE
#include "Board.hpp"
#include "Card.hpp"
#include <string>
#include <iostream>

/**
 * @brief Class representing text enviroment of game.
 *
 * Class representing text enviroment of game. All commands can be entered by
 * input stream operator. Class will load all commands until eof is reached. <br>
 * Usage of this class: <br>
 * Command [FILENAME] [ [ [ [ [ Card_stack1 ] FROM ] Card_stack2 TO ] CARD ] ]<br>
 * Command1 is one of following strings:<br>
 * print - prints game on stdout<br>
 * move  - moves card(s) from Card_stack1 with index FROM to Card_stack2 with index TO until CARD is reached<br>
 * load  - loads game that is saved in file FILENAME<br>
 * save  - saves game into file FILENAME<br>
 * new   - creates new game<br>
 * hint  - display one possible move<br>
 * help  - prints help on stdout<br>
 * FILENAME is string representing path to file.<br>
 * Card_stacks represent working (W), color (C), hidden (H) or visible (V) deck.<br>
 * Card_stack1 represents deck from which card(s) will be taken<br>
 * Card_stack2 represents deck to which card(s) will be added<br>
 * FROM is ID of Card_stack1 (0-6 when Card_stack1 is working, 0-3 when Card_stack1 is color)<br>
 * TO is ID of same values as FROM, but represents ID of Card_stack2<br>
 * CARD is only used when moving card(s) between 2 working stacks<br>
 * and all cards until CARD is reached will be moved between them<br>
 * @author Matejka Jiri (xmatej52)
 */
class Console {
private:
    /// @var Variable representing game.
    Board game;

    /// @var Variable representing invalid card.
    static Card err;

    /**
     * Procces command and return, if command was valide. Most of parametrs
     * are optional. If function can decide what to move, function will do it.
     * Function only reads parametrs that are usefull, for example it only reads
     * card parametr whe user wants to move between two working stacks.
     * @param  cmd1 definition of command (move, print, help, ...).
     * @param  cmd2 filename or source stack.
     * @param  from id of source stack
     * @param  cmd3 destination stack
     * @param  to   id of destination stak
     * @param  card Card that will be moved (only used when moving between 2 stacks)
     * @return      True on succes otherwise returns false.
     */
    bool command(std::string cmd1, std::string cmd2, unsigned from, std::string cmd3, unsigned to, Card card);

    /**
     * Parse string and call command function.
     * @param  str String representing command.
     * @return     Retrun value of command function.
     */
    bool string_to_command(std::string str);

public:

    /**
     * Creates new console application. Prints welcome message.
     */
    Console() {
        std::cout << "Dear user, welcome to Solitaire console game." << std::endl;
        std::cout << "For list of commands, please type \"help\"" << std::endl;
    }

    /**
     * Prints help on stdout.
     */
    void help();

    /**
     * Overloads output stream operator.
     */
    friend std::ostream& operator << (std::ostream& stream, const Console& console) {
        stream << console.game;
        return stream;
    }

    /**
     * Overloads input stream operator.
     */
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
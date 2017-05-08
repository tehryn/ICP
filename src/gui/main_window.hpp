/** @file
 *  Header file for class G_Board.
 *  @author Matejka Jiri (xmatej52)
 */
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QGridLayout>
#include <QActionGroup>
#include <QObject>
#include <QKeySequence>
#include <QMessageBox>
#include <QFileDialog>

#include "../gui/g_board.hpp"
constexpr int WINDOW_WIDTH = GAME_WIDTH*2+20;
constexpr int WINDOW_HEIGHT = GAME_HEIGHT*2+20;

/**
 * @brief Main windows of application.
 *
 * Class representing main windows of application. Holds implementation of menus
 * a control of maximum 4 games.
 *
 * @author Matejka Jiri (xmatej52)
 */
class Main_Window : public QMainWindow
{
    Q_OBJECT
private:

    G_Board * game[4];     ///< Instances of 4 games.
    bool plays[4];         ///< Tells which games are currently played.
    QWidget * app;         ///< Central widget of window
    QGridLayout * layout;  ///< Layout of central widget.

    QMenu * game_menu;       ///< Main menu
    QMenu * new_game_menu;   ///< Submenu with 4 items, each for one game. Creates new game.
    QMenu * save_game_menu;  ///< Submenu with 4 items, each for one game. Saves game.
    QMenu * open_game_menu;  ///< Submenu with 4 items, each for one game. Opens game.
    QMenu * undo_game_menu;  ///< Submenu with 4 items, each for one game. Undoes move.
    QMenu * hint_game_menu;  ///< Submenu with 4 items, each for one game. Whispers possible move.
    QMenu * leave_game_menu; ///< Submenu with 4 items, each for one game. Hides game.

    QActionGroup * New;   ///< Group of 4 actions creating new game.
    QActionGroup * Save;  ///< Group of 4 actions saving game.
    QActionGroup * Open;  ///< Group of 4 actions loading game.
    QActionGroup * Undo;  ///< Group of 4 actions undoing one move.
    QActionGroup * Hint;  ///< Group of 4 actions whispering possible move.
    QActionGroup * Leave; ///< Group of 4 actions leaving game.
    QAction      * Exit;  ///< Action that triggres closing of windows.

    QAction      * new1; ///< Action creating 1st game.
    QAction      * new2; ///< Action creating 2nd game.
    QAction      * new3; ///< Action creating 3rd game.
    QAction      * new4; ///< Action creating 4th game.

    QAction      * open1; ///< Action loading file into 1st game.
    QAction      * open2; ///< Action loading file into 2nd game.
    QAction      * open3; ///< Action loading file into 3rd game.
    QAction      * open4; ///< Action loading file into 4th game.

    QAction      * save1; ///< Action saving 1st game.
    QAction      * save2; ///< Action saving 2nd game.
    QAction      * save3; ///< Action saving 3rd game.
    QAction      * save4; ///< Action saving 4th game.

    QAction      * undo1; ///< Action undoing move in 1st game.
    QAction      * undo2; ///< Action undoing move in 2nd game.
    QAction      * undo3; ///< Action undoing move in 3rd game.
    QAction      * undo4; ///< Action undoing move in 4th game.

    QAction      * leave1; ///< Action leaving 1st game.
    QAction      * leave2; ///< Action leaving 2nd game.
    QAction      * leave3; ///< Action leaving 3rd game.
    QAction      * leave4; ///< Action leaving 4th game.

    QAction      * hint1; ///< Action displaying possible move in 1st game.
    QAction      * hint2; ///< Action displaying possible move in 2nd game.
    QAction      * hint3; ///< Action displaying possible move in 3rd game.
    QAction      * hint4; ///< Action displaying possible move in 4th game.

    /**
     * Initialize all actions and actions groups.
     */
    void createActions();

    /**
     * Initialize main menu and all submenus.
     */
    void createMenus();

    /**
     * Saves game.
     * @param id ID of game that will be saved.
     */
    void store_progress(int id);

    /**
     * Loads game.
     * @param id ID of game that will be loaded.
     */
    void load_game(int id);

    /**
     * Sets size of window and display/hide games.
     */
    void set_window();
public:

    /**
     * Constructor of class.
     * @param  parent Parent widget of window.
     * @return        Window that holds menus and 4 games.
     */
    explicit Main_Window(QWidget *parent = 0);

    /**
     * Destructor of class.
     */
    ~Main_Window();

signals:

private slots:
    /**
     * Creates new game in first slot.
     */
    void new_game1();

    /**
     * Creates new game in second slot.
     */
    void new_game2();

    /**
     * Creates new game in third slot.
     */
    void new_game3();

    /**
     * Creates new game in forth slot.
     */
    void new_game4();

    /**
     * Loads game in first slot.
     */
    void open_game1();

    /**
     * Loads game in second slot.
     */
    void open_game2();

    /**
     * Loads game in third slot.
     */
    void open_game3();

    /**
     * Loads game in forth slot.
     */
    void open_game4();

    /**
     * Saves game in first slot.
     */
    void save_game1();

    /**
     * Saves game in second slot.
     */
    void save_game2();

    /**
     * Saves game in third slot.
     */
    void save_game3();

    /**
     * Saves game in forth slot.
     */
    void save_game4();

    /**
     * Displays possible move in first slot.
     */
    void hint_game1();

    /**
     * Displays possible move in second slot.
     */
    void hint_game2();

    /**
     * Displays possible move in third slot.
     */
    void hint_game3();

    /**
     * Displays possible move in forth slot.
     */
    void hint_game4();

    /**
     * Undoes last move in first slot.
     */
    void undo_game1();

    /**
     * Undoes last move in second slot.
     */
    void undo_game2();

    /**
     * Undoes last move in third slot.
     */
    void undo_game3();

    /**
     * Undoes last move in forth slot.
     */
    void undo_game4();

    /**
     * Hides game in first slot.
     */
    void leave_game1();

    /**
     * Hides game in second slot.
     */
    void leave_game2();

    /**
     * Hides game in third slot.
     */
    void leave_game3();

    /**
     * Hides game in forth slot.
     */
    void leave_game4();

    /**
     * Closes window.
     */
    void exit_game();
};

#endif // MAIN_WINDOW_H

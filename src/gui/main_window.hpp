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
#include "g_board.hpp"
constexpr int WINDOW_WIDTH = GAME_WIDTH*2+20;
constexpr int WINDOW_HEIGHT = GAME_HEIGHT*2+20;

class Main_Window : public QMainWindow
{
    Q_OBJECT
private:
    G_Board * game[4];
    bool plays[4];
    QWidget * app;
    QGridLayout * layout;

    QMenu * game_menu;
    QMenu * new_game_menu;
    QMenu * save_game_menu;
    QMenu * open_game_menu;
    QMenu * undo_game_menu;
    QMenu * hint_game_menu;
    QMenu * leave_game_menu;
    QActionGroup * New;
    QActionGroup * Save;
    QActionGroup * Open;
    QActionGroup * Undo;
    QActionGroup * Hint;
    QActionGroup * Leave;
    QAction      * Exit;

    QAction      * new1;
    QAction      * new2;
    QAction      * new3;
    QAction      * new4;

    QAction      * open1;
    QAction      * open2;
    QAction      * open3;
    QAction      * open4;

    QAction      * save1;
    QAction      * save2;
    QAction      * save3;
    QAction      * save4;

    QAction      * undo1;
    QAction      * undo2;
    QAction      * undo3;
    QAction      * undo4;

    QAction      * leave1;
    QAction      * leave2;
    QAction      * leave3;
    QAction      * leave4;

    QAction      * hint1;
    QAction      * hint2;
    QAction      * hint3;
    QAction      * hint4;

    void createActions();
    void createMenus();
    void store_progress(int id);
    void load_game(int id);
    void set_window();
public:
    explicit Main_Window(QWidget *parent = 0);

signals:

private slots:
    void new_game1();
    void new_game2();
    void new_game3();
    void new_game4();
    void open_game1();
    void open_game2();
    void open_game3();
    void open_game4();
    void save_game1();
    void save_game2();
    void save_game3();
    void save_game4();
    void hint_game1();
    void hint_game2();
    void hint_game3();
    void hint_game4();
    void undo_game1();
    void undo_game2();
    void undo_game3();
    void undo_game4();
    void leave_game1();
    void leave_game2();
    void leave_game3();
    void leave_game4();
    void exit_game();
};

#endif // MAIN_WINDOW_H

#include "main_window.hpp"

Main_Window::Main_Window(QWidget *parent) : QMainWindow(parent)
{
    app = new QWidget(this);
    app->setMinimumSize(GAME_WIDTH+20, GAME_HEIGHT+20);
    layout = new QGridLayout(app);
    game[0] = new G_Board(app);
    game[1] = new G_Board(app);
    game[1]->setVisible(false);
    plays[1] = true;
    plays[1] = false;
    game[2] = new G_Board(app);
    game[2]->setVisible(false);
    plays[2] = false;
    game[3] = new G_Board(app);
    game[3]->setVisible(false);
    plays[3] = false;
    layout->addWidget(game[0], 0, 0);
    layout->addWidget(game[1], 0, 1);
    layout->addWidget(game[2], 1, 0);
    layout->addWidget(game[3], 1, 1);
    app->setLayout(layout);
    app->setStyleSheet("background: #228B22;");
    setMaximumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setMinimumSize(GAME_WIDTH+20, GAME_HEIGHT+20);
    createActions();
    createMenus();
}

Main_Window::~Main_Window() {
    delete game_menu;
}

void Main_Window::createActions() {
    new1 = new QAction(tr("&Game slot 1"), this);
    new1->setShortcuts(QKeySequence::New);
    connect(new1, &QAction::triggered, this, &Main_Window::new_game1);
    new2 = new QAction(tr("&Game slot 2"), this);
    connect(new2, &QAction::triggered, this, &Main_Window::new_game2);
    new3 = new QAction(tr("&Game slot 3"), this);
    connect(new3, &QAction::triggered, this, &Main_Window::new_game3);
    new4 = new QAction(tr("&Game slot 4"), this);
    connect(new4, &QAction::triggered, this, &Main_Window::new_game4);
    New = new QActionGroup(this);
    New->addAction(new1);
    New->addAction(new2);
    New->addAction(new3);
    New->addAction(new4);

    open1 = new QAction(tr("&Game slot 1"), this);
    open1->setShortcuts(QKeySequence::Open);
    connect(open1, &QAction::triggered, this, &Main_Window::open_game1);
    open2 = new QAction(tr("&Game slot 2"), this);
    connect(open2, &QAction::triggered, this, &Main_Window::open_game2);
    open3 = new QAction(tr("&Game slot 3"), this);
    connect(open3, &QAction::triggered, this, &Main_Window::open_game3);
    open4 = new QAction(tr("&Game slot 4"), this);
    connect(open4, &QAction::triggered, this, &Main_Window::open_game4);
    Open = new QActionGroup(this);
    Open->addAction(open1);
    Open->addAction(open2);
    Open->addAction(open3);
    Open->addAction(open4);

    save1 = new QAction(tr("&Game slot 1"), this);
    save1->setShortcuts(QKeySequence::Save);
    connect(save1, &QAction::triggered, this, &Main_Window::save_game1);
    save2 = new QAction(tr("&Game slot 2"), this);
    connect(save2, &QAction::triggered, this, &Main_Window::save_game2);
    save3 = new QAction(tr("&Game slot 3"), this);
    connect(save3, &QAction::triggered, this, &Main_Window::save_game3);
    save4 = new QAction(tr("&Game slot 4"), this);
    connect(save4, &QAction::triggered, this, &Main_Window::save_game4);
    Save = new QActionGroup(this);
    Save->addAction(save1);
    Save->addAction(save2);
    Save->addAction(save3);
    Save->addAction(save4);

    undo1 = new QAction(tr("&Game slot 1"), this);
    undo1->setShortcuts(QKeySequence::Undo);
    connect(undo1, &QAction::triggered, this, &Main_Window::undo_game1);
    undo2 = new QAction(tr("&Game slot 2"), this);
    connect(undo2, &QAction::triggered, this, &Main_Window::undo_game2);
    undo3 = new QAction(tr("&Game slot 3"), this);
    connect(undo3, &QAction::triggered, this, &Main_Window::undo_game3);
    undo4 = new QAction(tr("&Game slot 4"), this);
    connect(undo4, &QAction::triggered, this, &Main_Window::undo_game4);
    Undo = new QActionGroup(this);
    Undo->addAction(undo1);
    Undo->addAction(undo2);
    Undo->addAction(undo3);
    Undo->addAction(undo4);

    hint1 = new QAction(tr("&Game slot 1"), this);
    hint1->setShortcuts(QKeySequence::Replace);
    connect(hint1, &QAction::triggered, this, &Main_Window::hint_game1);
    hint2 = new QAction(tr("&Game slot 2"), this);
    connect(hint2, &QAction::triggered, this, &Main_Window::hint_game2);
    hint3 = new QAction(tr("&Game slot 3"), this);
    connect(hint3, &QAction::triggered, this, &Main_Window::hint_game3);
    hint4 = new QAction(tr("&Game slot 4"), this);
    connect(hint4, &QAction::triggered, this, &Main_Window::hint_game4);
    Hint = new QActionGroup(this);
    Hint->addAction(hint1);
    Hint->addAction(hint2);
    Hint->addAction(hint3);
    Hint->addAction(hint4);

    leave1 = new QAction(tr("&Game slot 1"), this);
    leave1->setShortcuts(QKeySequence::Quit);
    connect(leave1, &QAction::triggered, this, &Main_Window::leave_game1);
    leave2 = new QAction(tr("&Game slot 2"), this);
    connect(leave2, &QAction::triggered, this, &Main_Window::leave_game2);
    leave3 = new QAction(tr("&Game slot 3"), this);
    connect(leave3, &QAction::triggered, this, &Main_Window::leave_game3);
    leave4 = new QAction(tr("&Game slot 4"), this);
    connect(leave4, &QAction::triggered, this, &Main_Window::leave_game4);
    Leave = new QActionGroup(this);
    Leave->addAction(leave1);
    Leave->addAction(leave2);
    Leave->addAction(leave3);
    Leave->addAction(leave4);

    Exit = new QAction(tr("&Exit"), this);
    Exit->setShortcut(QKeySequence::Copy);
    connect(Exit, &QAction::triggered, this, &Main_Window::exit_game);
}

void Main_Window::createMenus() {
    game_menu = menuBar()->addMenu(tr("&Menu"));
    new_game_menu = game_menu->addMenu(tr("&New game"));
    new_game_menu->addAction(new1);
    new_game_menu->addAction(new2);
    new_game_menu->addAction(new3);
    new_game_menu->addAction(new4);

    save_game_menu = game_menu->addMenu(tr("&Save game"));
    save_game_menu->addAction(save1);
    save_game_menu->addAction(save2);
    save_game_menu->addAction(save3);
    save_game_menu->addAction(save4);

    open_game_menu = game_menu->addMenu(tr("&Load game"));
    open_game_menu->addAction(open1);
    open_game_menu->addAction(open2);
    open_game_menu->addAction(open3);
    open_game_menu->addAction(open4);

    undo_game_menu = game_menu->addMenu(tr("&Undo"));
    undo_game_menu->addAction(undo1);
    undo_game_menu->addAction(undo2);
    undo_game_menu->addAction(undo3);
    undo_game_menu->addAction(undo4);

    hint_game_menu = game_menu->addMenu(tr("&Hint"));
    hint_game_menu->addAction(hint1);
    hint_game_menu->addAction(hint2);
    hint_game_menu->addAction(hint3);
    hint_game_menu->addAction(hint4);

    leave_game_menu = game_menu->addMenu(tr("&Leave game"));
    leave_game_menu->addAction(leave1);
    leave_game_menu->addAction(leave2);
    leave_game_menu->addAction(leave3);
    leave_game_menu->addAction(leave4);

    game_menu->addAction(Exit);
    menuBar()->setNativeMenuBar(false);
}

void Main_Window::new_game1() {
    game[0]->new_game();
    plays[0] = true;
    game[0]->setVisible(true);
    set_window();
}
void Main_Window::new_game2() {
    game[1]->new_game();
    plays[1] = true;
    game[1]->setVisible(true);
    set_window();
}
void Main_Window::new_game3() {
    game[2]->new_game();
    plays[2] = true;
    game[2]->setVisible(true);
    set_window();
}
void Main_Window::new_game4() {
    game[3]->new_game();
    plays[3] = true;
    game[3]->setVisible(true);
    set_window();
}

void Main_Window::open_game1() {
    load_game(0);
    plays[0] = true;
    game[0]->setVisible(true);
    set_window();
}

void Main_Window::open_game2() {
    load_game(1);
    plays[1] = true;
    game[1]->setVisible(true);
    set_window();
}
void Main_Window::open_game3() {
    load_game(2);
    plays[2] = true;
    game[2]->setVisible(true);
    set_window();
}
void Main_Window::open_game4() {
    load_game(3);
    plays[3] = true;
    game[3]->setVisible(true);
    set_window();
}

void Main_Window::save_game1() {
    if (game[0]->isVisible()) {
        store_progress(0);
    }
}

void Main_Window::save_game2() {
    if (game[1]->isVisible()) {
        store_progress(1);
    }
}

void Main_Window::save_game3() {
    if (game[2]->isVisible()) {
        store_progress(2);
    }
}
void Main_Window::save_game4() {
    if (game[3]->isVisible()) {
        store_progress(3);
    }
}
void Main_Window::hint_game1() {
    if (game[0]->isVisible()) {
        game[0]->hint();
    }
}
void Main_Window::hint_game2() {
    if (game[1]->isVisible()) {
        game[1]->hint();
    }
}
void Main_Window::hint_game3() {
    if (game[2]->isVisible()) {
        game[2]->hint();
    }
}
void Main_Window::hint_game4() {
    if (game[3]->isVisible()) {
        game[3]->hint();
    }
}
void Main_Window::undo_game1() {
    if (game[0]->isVisible()) {
        game[0]->undo();
    }
}
void Main_Window::undo_game2() {
    if (game[1]->isVisible()) {
        game[1]->undo();
    }
}
void Main_Window::undo_game3() {
    if (game[2]->isVisible()) {
        game[2]->undo();
    }
}
void Main_Window::undo_game4() {
    if (game[3]->isVisible()) {
        game[3]->undo();
    }
}

void Main_Window::leave_game1() {
    game[0]->setVisible(false);
    plays[0] = false;
}

void Main_Window::leave_game2() {
    game[1]->setVisible(false);
    plays[1] = false;
    set_window();
}

void Main_Window::leave_game3() {
    game[2]->setVisible(false);
    plays[2] = false;
    set_window();
}

void Main_Window::leave_game4() {
    game[3]->setVisible(false);
    plays[3] = false;
    set_window();
}

void Main_Window::exit_game() {
    close();
}

void Main_Window::set_window() {
    if (plays[1] || plays[2] || plays[3]) {
        setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        app->setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    }
    else {
        setMinimumSize(GAME_WIDTH+20, GAME_HEIGHT+20);
        app->setMinimumSize(GAME_WIDTH+20, GAME_HEIGHT+20);
    }
    for(int i = 0; i < 4; i++) {
        if (plays[i]) {
            game[i]->setVisible(true);
        }
        else {
            game[i]->setVisible(false);
        }
    }
}

void Main_Window::store_progress(int id) {
    QString filename = QFileDialog::getSaveFileName(this, tr("Save game"), "", tr("All Files (*)"));
    if (filename.isEmpty()) {
        return;
    }
    else {
        if (!game[id]->save_game(filename.toUtf8().constData())) {
            QMessageBox::information(this, tr("Unable to open file"), tr("Unknown error"));
        }
    }
}

void Main_Window::load_game(int id) {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("All Files (*)"));
    if (filename.isEmpty()) {
        return;
    }
    else {
        if (!game[id]->load_game(filename.toUtf8().constData())) {
            QMessageBox::information(this, tr("Unable to open file"), tr("Unknown error"));
        }
    }
}

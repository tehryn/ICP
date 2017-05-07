#ifndef G_STACK_H
#define G_STACK_H

#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include "globals.hpp"

class G_Board;

class G_Stack : public QWidget
{
    Q_OBJECT

private:
    std::vector<G_Card*> stack;
    int positionY = 0;
    G_Board * board = nullptr;
    Stacks type = ErrStack;
    int id = 0;
    G_Card* find_card(int y);
    void process_command();

public:
    explicit G_Stack(QWidget *parent = 0);
    void set_positionY(int positionY);
    void set_board(G_Board* board);
    void set_id(int id);
    void set_type(Stacks type);
    void set_border(const char * style, G_Card * gcard);
    void set_border(const char * style, Card card);
    std::string stack_identifier_to_str(Stacks type, int id) const;

    int size();
    G_Card* top();
    void push(Card card);
    G_Card* pop();
    G_Card* get(int index);
    void clean();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // G_STACK_H

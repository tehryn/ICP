#ifndef G_CARD_H
#define G_CARD_H

#include "Card.hpp"
#include <QLabel>

#define get_height(height_before, width_before, width_new) (((height_before) * (width_new)) / (width_before))

#define CARD_WIDTH_ORIGIN 120
#define CARD_HEIGHT_ORIGIN 174

constexpr int CARD_WIDTH = CARD_WIDTH_ORIGIN/2;
constexpr int CARD_HEIGHT = CARD_HEIGHT_ORIGIN/2;


#define CARD_HEIGHT get_height(CARD_HEIGHT_ORIGIN, CARD_WIDTH_ORIGIN, CARD_WIDTH)


class G_Card : public QLabel
{
private:
    QWidget * parent_widget;
public:
    Card card;
    QPixmap picture;
    G_Card(Card card, QWidget *parent=0);
};

#endif // G_CARD_H

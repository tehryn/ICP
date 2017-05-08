#ifndef G_CARD_H
#define G_CARD_H

#include <QLabel>
#include "../game/Card.hpp"

constexpr int CARD_WIDTH_ORIGIN = 120
constexpr int CARD_HEIGHT_ORIGIN = 174

constexpr int CARD_WIDTH = CARD_WIDTH_ORIGIN/2;
constexpr int CARD_HEIGHT = ((CARD_HEIGHT_ORIGIN) * (CARD_WIDTH)) / (CARD_WIDTH_ORIGIN);


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

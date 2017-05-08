/** @file
 *  Header file for class G_Card.
 *  @author Misova Miroslava (xmisov00), Matejka Jiri (xmatej52)
 */

#ifndef G_CARD_H
#define G_CARD_H

#include <QLabel>
#include "../game/Card.hpp"

/// @var Width of original cards
constexpr int CARD_WIDTH_ORIGIN = 120;
/// @var Height of original cards
constexpr int CARD_HEIGHT_ORIGIN = 174;

/// @var Width of card to be used. You could change it and CARD_HEIGHT will change automatically.
constexpr int CARD_WIDTH = CARD_WIDTH_ORIGIN/2;
/// @var Height of card to be used. Do NOT change. Please change CARD_WIDTH if you want.
constexpr int CARD_HEIGHT = ((CARD_HEIGHT_ORIGIN) * (CARD_WIDTH)) / (CARD_WIDTH_ORIGIN);

/**
 * @brief Class representing graphical view of cards.
 *
 * @author Misova Miroslava (xmisov00)
 */
class G_Card : public QLabel
{
private:
    /// @var Parent pointer
    QWidget * parent_widget;
public:
    /// @var Logical card
    Card card;
    /// @var Picture of card
    QPixmap picture;

    /**
     * Constructor.
     * @param card Logical card
     */
    G_Card(Card card, QWidget *parent=0);
};

#endif // G_CARD_H

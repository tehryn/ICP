/** @file
 *  Header file for class G_Card.
 *  @author Misova Miroslava (xmisov00), Matejka Jiri (xmatej52)
 */

#ifndef G_CARD_H
#define G_CARD_H

#include <QLabel>
#include "../game/Card.hpp"


constexpr int CARD_WIDTH_ORIGIN = 120; ///< Width of original cards
constexpr int CARD_HEIGHT_ORIGIN = 174; ///< Height of original cards


constexpr int CARD_WIDTH = CARD_WIDTH_ORIGIN/2; ///< Width of card to be used. You could change it and CARD_HEIGHT will change automatically.
constexpr int CARD_HEIGHT = ((CARD_HEIGHT_ORIGIN) * (CARD_WIDTH)) / (CARD_WIDTH_ORIGIN); ///< Height of card to be used. Do NOT change. Please change CARD_WIDTH if you want.


/**
 * @brief Class representing graphical view of cards.
 *
 * @author Misova Miroslava (xmisov00)
 */
class G_Card : public QLabel
{
private:
    QWidget * parent_widget; ///< Parent pointer

public:
   
    Card card; ///< Logical card
    QPixmap picture; ///< Picture of card

    /**
     * Constructor.
     * @param card Logical card
     */
    G_Card(Card card, QWidget *parent=0);
};

#endif // G_CARD_H

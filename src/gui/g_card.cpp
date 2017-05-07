#include "g_card.hpp"

#include <sys/stat.h>
#include <fstream>
#include <string>

bool does_file_exist(const std::string& filename)
{
    std::ifstream ifile(filename.c_str());
    return ifile.good();
}

G_Card::G_Card(Card card, QWidget *parent)
{
    this->parent_widget = parent;
    this->card = card;

    std::string localpath = "./cards120px/";

    if (card.is_error_card())
        localpath += "empty.png";
    else if (!card.is_visible())
        localpath += "back.png";
    else
    {
        localpath += Card::color_to_string(card.get_color());
        localpath += std::to_string(card.get_value());
        localpath += ".png";
    }

    if (!does_file_exist(localpath))
        std::cout << "Image with card does not exist." << std::endl;
    picture.load(localpath.c_str());
    setParent(parent);
    setPixmap(picture.scaledToHeight(CARD_HEIGHT, Qt::SmoothTransformation));
    setFixedHeight(CARD_HEIGHT);
}

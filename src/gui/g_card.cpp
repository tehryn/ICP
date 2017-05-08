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

    std::string localpath = "../lib/cards/";
    std::string localpath2 = "./lib/cards/";

    if (card.is_error_card())
    {
        localpath += "empty.png";
        localpath2 += "empty.png";
    }
    else if (!card.is_visible())
    {
        localpath += "back.png";
        localpath2 += "back.png";
    }
    else
    {
        localpath += Card::color_to_string(card.get_color());
        localpath += std::to_string(card.get_value());
        localpath += ".png";
        localpath2 += Card::color_to_string(card.get_color());
        localpath2 += std::to_string(card.get_value());
        localpath2 += ".png";
    }
    if (!does_file_exist(localpath))
    {
        localpath = localpath2;
        if (!does_file_exist(localpath))
            std::cerr << "Pictrues of cards not found!!!" << std::endl;
    }

    picture.load(localpath.c_str());
    setParent(parent);
    setPixmap(picture.scaledToHeight(CARD_HEIGHT, Qt::SmoothTransformation));
    setFixedHeight(CARD_HEIGHT);
}

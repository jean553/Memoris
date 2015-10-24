/**
 * Memoris
 * Copyright (C) 2015  Jean LELIEVRE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file ItemsListWidget.hpp
 * @brief list of textual items, one can be selected
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_ITEMS_LIST_WIDGET
#define DEF_ITEMS_LIST_WIDGET

#include <SFML/Graphics.hpp>

#include "../utils/Context.hpp"

namespace widgets {
class ItemsListWidget {

public:

    static constexpr int ITEMS_LIST_BORDER_SIZE = 1;
    static constexpr int ITEMS_LIST_ITEM_HEIGHT = 40;
    static constexpr int ITEMS_LIST_ARROW_DIM = 40;

    ItemsListWidget();

    /**
     * @brief set the size and position of the widget
     *
     * @param widgetHorizontalPosition       horizontal position
     * @param widgetVerticalPosition         integer vertical position
     * @param widgetWidth                    width
     * @param verticalTextContainers         vertical text containers
     */
    void setLayout(
        int widgetHorizontalPosition,
        int widgetVerticalPosition,
        int widgetWidth,
        unsigned char verticalTextContainers
    );

    /**
     * @param textItem   add text item to display in the list
     */
    void addTextItem(std::string textItem);

    /**
     * @brief display the items list widget
     *
     * @param context  current context pointer
     */
    void display(utils::Context* context);

protected:

    static const std::string PATH_IMAGE_ARROW_UP;
    static const std::string PATH_IMAGE_ARROW_DOWN;

    sf::Font textItemFont;

    sf::Color color;

    sf::RectangleShape boxTop;
    sf::RectangleShape boxBottom;
    sf::RectangleShape boxLeft;
    sf::RectangleShape boxRight;

    sf::Texture textureUp;
    sf::Texture textureDown;

    sf::Sprite spriteUp;
    sf::Sprite spriteDown;

    int horizontalPosition;
    int verticalPosition;
    int width;
    unsigned char verticalContainers;

    std::vector<std::string> stringsList;
};
}

#endif

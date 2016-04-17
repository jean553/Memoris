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
 * Frame widget
 *
 * @file FrameWidget.hpp
 * @brief simple rectangle frame with an unique color border
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_FRAME_WIDGET
#define DEF_FRAME_WIDGET

#include "Widget.hpp"
#include "Context.hpp"

namespace widgets
{
class FrameWidget : public Widget
{

    static const unsigned short BORDER_WIDTH;

public:

    FrameWidget();

    /**
     * @brief displays the button and manage
     * button colors according to the current
     * cursor position on screen
     *
     * @param pContext       current context pointer
     */
    void display(utils::Context* pContext);

    /**
     * @brief update the size of the frame
     *
     * @param hSize horizontalSize
     * @param vSize verticalSize
     */
    void setSize(
        float hSize,
        float vSize
    );

    /**
     * @brief update the color of the border
     *
     * @param red quantity
     * @param green quantity
     * @param blue quantity
     */
    void setColor(
        sf::Uint8 red,
        sf::Uint8 green,
        sf::Uint8 blue
    );

    /**
     * @brief overwrite the setPosition function to
     * set the position of each frame border
     *
     * @param hPosition horizontal position
     * @param vPosition vertical position
     */
    void setPosition(
        float hPosition,
        float vPosition
    );

private:

    sf::Color borderColor;

    sf::RectangleShape leftLine;
    sf::RectangleShape rightLine;
    sf::RectangleShape topLine;
    sf::RectangleShape bottomLine;

    float horizontalSize;
    float verticalSize;
};
}

#endif

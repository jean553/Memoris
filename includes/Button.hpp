/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file Button.hpp
 * @brief graphical button with icon inside
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_WIDGETS_H_
#define MEMORIS_WIDGETS_H_

#include "Context.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace widgets
{

class Button
{

public:

    /**
     * @brief constructor, creates the SFML surfaces at the given position
     *
     * @param context reference to the current context
     * @param hPosition horizontal position of the button
     * @param vPosition vertical position of the button
     * @param texture constant reference to the SFML texture of the icon
     */
    Button(
        const utils::Context& context,
        const float& hPosition,
        const float& vPosition,
        const sf::Texture& texture
    );

    /**
     * @brief display the button
     *
     * @param context reference to the current context to use
     *
     * NOTE: usually, display() functions are const; not this one because the
     * attributes of the button are modified inside this function if the mouse
     * is hover the widget
     */
    void display(const utils::Context& context);

    /**
     * @brief boolean that indicates if the mouse is hover the button or not
     *
     * @return bool
     */
    bool isMouseHover() const;

private:

    static constexpr float BUTTON_DIMENSION {70.f};
    static constexpr float ICON_POSITION_OFFSET {3.f};

    /**
     * @brief private method to set the color of the borders surfaces; we use
     * a specific function because the color of the borders change when the
     * mouse is hover or not
     *
     * @param color constant reference to the color to apply
     */
    void setBordersColor(const sf::Color& color);

    /* SFML surface of the button background */
    sf::RectangleShape back;

    /* SFML surfaces of the button borders */
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape bottom;
    sf::RectangleShape top;

    /* unique pointer to the icon to display */
    sf::Sprite icon;

    /* store integer for the position (and not float), because we use these
       positions to check if the mouse is hover the widget, the returned
       type of SFML is sf::Vector2<int> and not sf::Vector<float>; we improve
       performances because we only perform a static cast one time (init) and
       not everytime */
    int horizontalPosition;
    int verticalPosition;

    /* boolean used to switch the color and not continually set the color
       when the mouse stays hover the button or outside of the button */
    bool mouseHover {false};
};

}
}

#endif

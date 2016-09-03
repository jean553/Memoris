/*
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
     * @param context shared pointer to the current context
     * @param hPosition horizontal position of the button
     * @param vPosition vertical position of the button
     * @param texture constant reference to the SFML texture of the icon
     */
    Button(
        const std::shared_ptr<utils::Context>& context,
        const float& hPosition,
        const float& vPosition,
        const sf::Texture& texture
    );

    /**
     * @brief display the button
     *
     * @param context shared pointer to the current context to use
     */
    void display(const std::shared_ptr<utils::Context>& context) const;

private:

    static constexpr float BUTTON_DIMENSION {70.f};
    static constexpr float ICON_POSITION_OFFSET {3.f};

    /* SFML surface of the button background */
    sf::RectangleShape back;

    /* SFML surfaces of the button borders */
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape bottom;
    sf::RectangleShape top;

    /* unique pointer to the icon to display */
    sf::Sprite icon;
};

}
}

#endif

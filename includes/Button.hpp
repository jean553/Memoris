/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @brief handles button widget
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
     * @brief constructor
     *
     * @param context the current context
     * @param hPosition horizontal position of the button
     * @param vPosition vertical position of the button
     * @param texture reference to the SFML texture of the icon
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    Button(
        const utils::Context& context,
        const float& hPosition,
        const float& vPosition,
        const sf::Texture& texture
    );

    Button(const Button&) = delete;

    Button& operator=(const Button&) = delete;

    /**
     * @brief default destructor
     */
    ~Button();

    /**
     * @brief display the button
     *
     * @param cursorPosition the current position of the cursor
     *
     * NOTE: usually, display() functions are const; not this one because the
     * attributes of the button are modified inside this function if the mouse
     * is hover the widget
     */
    void display(const sf::Vector2<float>& cursorPosition) &;

    /**
     * @brief boolean that indicates if the mouse is hover the button or not
     *
     * @return bool
     */
    bool isMouseHover() const;

private:

    /**
     * TODO
     */
    void setBordersColor(const sf::Color& color);

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif

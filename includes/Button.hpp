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

#include <memory>

namespace sf
{
class Texture;
class Color;

template<typename T>
class Vector2;

/* 'typedef Vector2<float> Vector2f' in Vector2.hpp, we declare exactly
   the same type here in order to both use declaration forwarding and
   prevent conflicting declaration */
typedef Vector2<float> Vector2f;
}

namespace memoris
{

namespace utils
{
class Context;
}

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
     * not const because the attributes of the button may be modified
     * by the method when the mouse goes hover and unhover
     *
     * not noexcept because it calls SFML draw() method that is not noexcept
     */
    void display(const sf::Vector2f& cursorPosition) &;

    /**
     * @brief indicates if the mouse is currently hover the button
     *
     * @return const bool
     */
    const bool isMouseHover() const & noexcept;

private:

    /**
     * @brief updates the colors of the four button borders surfaces
     *
     * @param color the SFML color to use
     *
     * not const because it modifies the color of the four SFML border surfaces
     *
     * not noexcept because it calls SFML setFillColor method (not noexcept)
     */
    void setBordersColor(const sf::Color& color) &;

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif

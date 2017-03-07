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
 * @file MenuGradient.hpp
 * @brief renders the two gradient surfaces at both sides of the main menu
 * @package others
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MENUGARDIENT_H_
#define MEMORIS_MENUGARDIENT_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace others
{

class MenuGradient
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     */
    MenuGradient(const utils::Context& context);

    MenuGradient(const MenuGradient&) = delete;

    MenuGradient& operator=(const MenuGradient&) = delete;

    /**
     * @brief default constructor
     */
    ~MenuGradient();

    /**
     * @brief displays surfaces of the menu gradient
     *
     * sf::RenderWindow::draw() method is not noexcept
     */
    void display() const &;

private:

    /**
     * @brief initialize the surfaces that create the gradient effect
     *
     * sf::RectangleShape setPosition(), setSize()
     * and constructor are not noexcept
     */
    void initializeGradientRectangles() const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif

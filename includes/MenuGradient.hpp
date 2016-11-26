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
 * @file MenuGradient.hpp
 * @brief this class manages the rendering of color gradients displayed on
 * both of the two menu sides
 * @package others
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MENUGARDIENT_H_
#define MEMORIS_MENUGARDIENT_H_

#include "NotCopiable.hpp"

#include <SFML/Config.hpp>

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace others
{

class MenuGradient : public utils::NotCopiable
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    MenuGradient(const utils::Context& context);

    /**
     * @brief default constructor, empty, only declared in order to use the
     * forwarding declarations
     */
    ~MenuGradient() noexcept;

    /**
     * @brief displays all the surfaces of the menu gradient
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void display(const utils::Context& context) const &;

private:

    static constexpr unsigned short SURFACES_AMOUNT {1020};
    static constexpr unsigned short SIDE_SURFACES_AMOUNT {510};

    static constexpr float LEFT_SIDE_HORIZONTAL_POSITION {479.f};
    static constexpr float RIGHT_SIDE_HORIZONTAL_POSITION {1099.f};
    static constexpr float BACKGROUND_WIDTH {620.f};
    static constexpr float BACKGROUND_HORIZONTAL_POSITION {480.f};

    static constexpr sf::Uint8 DEFAULT_EFFECT_COLOR_ALPHA {255};

    /**
     * @brief private method called by the constructor only to create the
     * background sides lines with the gradient effect
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    void initializeGradientRectangles(const utils::Context& context) &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif

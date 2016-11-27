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
 * @file HorizontalGradient.hpp
 * @package others
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

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

class HorizontalGradient : public utils::NotCopiable
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    HorizontalGradient(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~HorizontalGradient() noexcept;

    /**
     * @brief renders the gradient background
     *
     * @param context constant reference to the current context to use
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void render(const utils::Context& context) const &;

private:

    /**
     * @brief refactored method (for organization purposes), generates the
     * top and bottom sides surfaces
     *
     * @param context constant reference to the current context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void initializeGradientRectangles(const utils::Context& context) const &; 

    static constexpr float BACKGROUND_VERTICAL_POSITION {250.f};
    static constexpr float BACKGROUND_HEIGHT {300.f};

    static constexpr unsigned short SURFACES_AMOUNT {1020};
    static constexpr unsigned short SIDE_SURFACES_AMOUNT {510};

    static constexpr sf::Uint8 DEFAULT_EFFECT_COLOR_ALPHA {255};

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

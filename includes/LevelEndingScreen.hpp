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
 * @file LevelEndingScreen.hpp
 * @brief abstract class for level ending screens (win and lose)
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVELENDINGSCREEN_H_
#define MEMORIS_LEVELENDINGSCREEN_H_

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>

namespace memoris
{
namespace utils
{

class Context;

class LevelEndingScreen
{

public:

    /**
     * @brief default destructor
     */
    virtual ~LevelEndingScreen();

    /**
     * @brief defines how the win or lose screen has to be displayed
     *
     * @param context constant reference to the current context
     *
     * public because it has to be accessed by the game controller
     *
     * not 'const' because the function cannot be const inside the win screen
     * definition as there is an animation there and the attributes of the
     * object are updated continuously in order to render the animation
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    virtual void render(const Context& context) &;

protected:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the context to use
     *
     * protected because the class is abstract, so the constructor is only
     * called by child objects
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    LevelEndingScreen(const Context& context);

    /* not in the implementation, must be accessible in protected scope */

    sf::Text text;

    sf::RectangleShape filter;
};

}
}

#endif

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
     * not const because the object is updated continusouly for animations
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    virtual void render() &;

protected:

    /**
     * @brief constructor
     *
     * @param context the context to use
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    LevelEndingScreen(const Context& context);

    /**
     * @brief used context getter
     *
     * @return const utils::Context&
     */
    const utils::Context& getContext() const & noexcept;

    /* not in the implementation, must be accessible in protected scope */

    sf::Text text;

    sf::RectangleShape filter;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif

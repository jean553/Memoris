/**
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
 * @file GameDashboard.hpp
 * @brief the displayed dashboard inside the game controller
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAMEDASHBOARD_H_
#define MEMORIS_GAMEDASHBOARD_H_

#include <memory>

namespace sf
{
class Text;
}

namespace memoris
{

namespace widgets
{
class TimerWidget;
}

namespace utils
{

class Context;
class WatchingPeriodTimer;

class GameDashboard
{

public:

    /**
     * @brief constructor
     *
     * @param context the current context
     * @param totalStarsAmount the total stars amount to display
     */
    GameDashboard(
        const utils::Context& context,
        const unsigned short& totalStarsAmount
    );

    GameDashboard(const GameDashboard&) = delete;

    GameDashboard& operator=(const GameDashboard) = delete;

    /**
     * @brief default destructor 
     */
    ~GameDashboard();

    /**
     * @brief displays the dashboard
     *
     * not noexcept as it calls SFML methods that are not noexcept
     */
    void display() const &;

    /**
     * @brief returns the current amount of lifes
     *
     * @return const unsigned short&
     */
    const unsigned short& getLifes() const & noexcept;

    /**
     * @brief returns the current watching time amount
     *
     * @return const unsigned short&
     */
    const unsigned short& getWatchingTime() const & noexcept;

    /**
     * @brief getter of the found star(s) amount
     *
     * @return const unsigned short&
     */
    const unsigned short& getFoundStarsAmount() const & noexcept;

    /**
     * @brief increments the found stars amount and update the SFML surface
     *
     * call SFML functions that are not noexcept
     */
    void incrementFoundStars() const &;

    /**
     * @brief increments the lifes amount and update the SFML surface
     *
     * call SFML functions that are not noexcept
     */
    void incrementLifes() const &;

    /**
     * @brief decrement the lifes amount and update the SFML surface
     *
     * call SFML functions that are not noexcept
     */
    void decrementLifes() const &;

    /**
     * @brief increase the watching time seconds by 3
     *
     * call SFML functions that are not noexcept
     */
    void increaseWatchingTime() const &;

    /**
     * @brief decrease the amount of seconds of the watching time by 3 seconds
     *
     * call SFML functions that are not noexcept
     */
    void decreaseWatchingTime() const &;

    /**
     * @brief updates the SFML surface that displays the current floor index
     *
     * @param amount the amount to display in the dashboard
     *
     * call SFML functions that are not noexcept
     */
    void updateCurrentFloor(const unsigned short& floorIndex) const &;

private:

    /**
     * @brief returns the horizontal position minus the surface width;
     * this method is used by the game dashboard numeric items
     * to get a correct horizontal position according to their width
     *
     * @param rightSideHorizontalPosition horizontal position of the surface
     * @param sfmlSurface SFML texture
     *
     * @return const float
     *
     * call sf::Rect::getLocalBounds() method which is not noexcept
     */
    const float getHorizontalPositionMinusWidth(
        const float& rightSideHorizontalPosition,
        const sf::Text& sfmlSurface
    ) const &;

    /**
     * @brief replace SFML text surface content by numeric content;
     * this is a common requirement from public methods that update
     * the displayed values of the dashboard, so we simply refactor
     * the std::to_string(number) into the function
     *
     * @param sfmlText SFML text surface to update
     * @param numericValue the numeric value
     *
     * call SFML functions that are not noexcept
     */
    void updateSfmlTextByNumericValue(
        sf::Text& sfmlText,
        const unsigned short& numericValue
    ) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif

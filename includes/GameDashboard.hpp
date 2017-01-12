/**
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
 * @file GameDashboard.hpp
 * @brief the displayed dashboard inside the game controller, containing the
 * countdown and all the information labels
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
     * @brief constructor, initialize the timer widget, all the dashboard
     * informations labels and all the labels images
     *
     * @param context the current context
     */
    GameDashboard(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~GameDashboard();

    /**
     * @brief overwritte the method to display the dashboard
     */
    void display() const &;

    /**
     * @brief returns the current amount of lifes; this is used by the game
     * controller to know if the lifes amount is equal to 0 before
     * decrementing the value
     *
     * @return const unsigned short&
     */
    const unsigned short& getLifes() const & noexcept;

    /**
     * @brief returns the current watching time amount; this is used by the
     * game controller to know the current watching time before decrementing
     * it by 3
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
     */
    void incrementFoundStars() const &;

    /**
     * @brief increments the lifes amount and update the SFML surface
     */
    void incrementLifes() const &;

    /**
     * @brief decrement the lifes amount and update the SFML surface
     */
    void decrementLifes() const &;

    /**
     * @brief increase the watching time seconds by 3
     */
    void increaseWatchingTime() const &;

    /**
     * @brief decrease the amount of seconds of the watching time by 3 seconds
     */
    void decreaseWatchingTime() const &;

    /**
     * @brief updates the SFML surface that displays the total amount of cells
     * on the level; this method is called directly after the end of the level
     * loading process;
     *
     * @param amount the amount to display in the dashboard
     */
    void updateTotalStarsAmountSurface(const unsigned short& amount) const &;

    /**
     * @brief update the displayed floor index
     *
     * @param floor the current floor index, the method will automatically
     * increment it to make it human readable
     */
    void updateCurrentFloor(const unsigned short& floorIndex) const &;

    /**
     * @brief getter for the timer widget
     *
     * @return widgets::TimerWidget&
     *
     * the returned reference is not constant because the caller (game
     * controller) directly updates the object
     */
    widgets::TimerWidget& getTimerWidget() const & noexcept;

    /**
     * @brief getter of the watching period timer
     *
     * @return utils::WatchingPeriodTimer&
     *
     * the returned reference is not constant because the caller (game
     * controller) directly updates the object
     */
    utils::WatchingPeriodTimer& getWatchingPeriodTimer() const & noexcept;

private:

    static constexpr unsigned short WATCHING_TIME_UPDATE_STEP {3};

    /**
     * @brief returns the horizontal position less the surface width
     *
     * @param rightSideHorizontalPosition horizontal position of the surface
     * @param sfmlSurface SFML texture
     *
     * @return const float
     *
     * call sf::Rect::getLocalBounds() method which is not noexcept
     */
    const float getHorizontalPositionLessWidth(
        const float& rightSideHorizontalPosition,
        const sf::Text& sfmlSurface
    ) const &;

    /**
     * @brief replace SFML text surface content by numeric content
     *
     * @param sfmlText SFML text surface to update
     * @param numericValue the numeric value
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

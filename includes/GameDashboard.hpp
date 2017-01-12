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
     * @param context reference to the current context
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
     * @brief increments the found stars amount and updates the displayed found
     * stars amount text; this function is called by the game controller when
     * one new star is found by the player
     */
    void incrementFoundStars();

    /**
     * @brief increments the found lifes amount and updates the displayed found
     * lifes amount text; this action is called by the game controller
     */
    void incrementLifes();

    /**
     * @brief decrements the amount of lifes and update the displayed lifes
     * amount; this action is called by the game controller
     */
    void decrementLifes();

    /**
     * @brief increase the amount of seconds of the watching time by 3 seconds
     */
    void increaseWatchingTime();

    /**
     * @brief decrease the amount of seconds of the watching time by 3 seconds
     */
    void decreaseWatchingTime();

    /**
     * @brief getter of the found star(s) amount
     *
     * @return const unsigned short&
     */
    const unsigned short& getFoundStarsAmount();

    /**
     * @brief updates the SFML surface that displays the total amount of cells
     * on the level; this method is called directly after the end of the level
     * loading process;
     *
     * @param amount the amount to display in the dashboard
     */
    void updateTotalStarsAmountSurface(const unsigned short& amount);

    /**
     * @brief getter for the lifes amount (the amount of lifes the user has)
     *
     * @return const unsigned short&
     */
    const unsigned short& getLifesAmount() const & noexcept;

    /**
     * @brief update the displayed floor index
     *
     * @param floor the current floor index, the method will automatically
     * increment it to make it human readable
     */
    void updateCurrentFloor(const unsigned short& floorIndex);

    /**
     * @brief getter for the watching time in the current level; this is used
     * by the game controller to get the modification of the previous
     * watching time and update it inside the current playing serie context
     *
     * @return const unsigned short&
     */
    const unsigned short& getWatchingTime() const;

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

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif

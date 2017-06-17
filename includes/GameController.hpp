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
 * @file GameController.hpp
 * @brief main game controller, renders the map and let the user play
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAMECONTROLLER_H_
#define MEMORIS_GAMECONTROLLER_H_

#include "Controller.hpp"

#include <memory>

namespace memoris
{

namespace entities
{
class Level;
}

namespace animations
{
class LevelAnimation;
}

namespace controllers
{

class GameController : public Controller
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param level the level object to load
     * @param enableWatchingPeriod set if there is a watching period or not
     * (there is this period during the game, not the test of the editor )
     * @param the default watching time to display when the game starts
     *
     * @throw std::invalid_argument the level file cannot be opened
     * this exception is caught by the controllers factory
     * in order to display an error message
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    GameController(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& displayedWatchingTime = 0
    );

    /**
     * @brief default destructor
     */
    ~GameController();

    /**
     * @brief renders the game main screen
     *
     * @return const ControllerId&
     */
    virtual const ControllerId& render() const & override;

private:

    /**
     * @brief starts the game (eventually right after the watching period)
     * hides all the cells except the departure, set the current floor,
     * start the playing period, ends the watching period, start the timer
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void startGame() const &;

    /**
     * @brief moves the player (it is mandatory to check first if the player
     * can actually move to its expected destination)
     *
     * @param event the current event, contains the expected movement
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void handlePlayerMovement(const sf::Event& event) const &;

    /**
     * @brief applies the action of the new player cell; this method is called
     * immediately after the player moved
     */
    void executePlayerCellAction() const &;

    /**
     * @brief this method is called during the watching mode by the main
     * display method to jump to the next floor if the next floor is a playable
     * floor or to stop the watching period if there is no playable floor
     * anymore; this function is called at each 'watching time interval'
     */
    void watchNextFloorOrHideLevel() const &;

    /**
     * @brief this method ends the level, it displays the win or lose screen
     * according if the player has just won or lost the current level
     */
    void endLevel() const &;

    /**
     * @brief creates a level animation pointer; the animations
     * are dynamically created and destroyed during the game
     *
     * @param cellType the cell type for the animation selection
     *
     * @return std::unique_ptr<animations::LevelAnimation>
     *
     * @throw std::bad_alloc the pointer cannot be initialized;
     * the exception is never caught and the program stops
     */
    std::unique_ptr<animations::LevelAnimation> getAnimationByCell(
        const char& cellType
    ) const &;

    /**
     * @brief starts the watching period (when start a level during the game)
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void startWatchingPeriod() const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif

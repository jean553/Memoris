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
     * @brief renders the current animation, resets it if finished
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void handleAnimation() const &;

    /**
     * @brief renders the animation of the player cell
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void handlePlayerCellAnimation() const &;

    /**
     * @brief displays and dynamically deletes the running pickup effects
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void handlePickupEffects() const &;

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
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void executePlayerCellAction() const &;

    /**
     * @brief this method ends the level, it displays the win or lose screen
     * according if the player has just won or lost the current level
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void endGame() const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
